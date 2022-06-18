//
// Created by kobedb on 19.03.22.
//

#include "VerkeerssituatieReader.h"

#include "tinyxml/tinyxml.h"
#include "VoertuigFactory.h"
#include <sstream>
#include <algorithm>

int tryParseInt(const std::string& s, bool& success)
{
    std::stringstream iss(s);
    int val;
    iss >> val;
    if(!iss) {
        success = false;
        return 0;
    }
    success = true;
    return val;
}

VerkeerssituatieReader::VerkeerssituatieReader(std::string situatieFile, std::ostream &errstr)
{
    read(situatieFile, errstr);
    checkConsistency(errstr);
}

void VerkeerssituatieReader::checkConsistency(std::ostream &errstr)
{
    using namespace std;
    /*
     * Een verkeerssituatie is consistent als:
        • Elk voertuig staat op een bestaande baan. (done)
        • Elk verkeerslicht staat op een bestaande baan. (done)
        • Elke voertuiggenerator staat op een bestaande baan. NOG NIET
        • De positie van elk voertuig is kleiner dan de lengte van de baan. (done)
        • De positie van elk verkeerslicht is kleiner dan de lengte van de baan. (done)
        • Er is maximaal  ́een voertuiggenerator op elke baan. NOG NIET
        • Een verkeerslicht mag zich niet in de vertraagafstand van een ander
        verkeerslicht bevinden (zie Appendix B). (done)
        Opmerkingen:
        • Lengte, positie, cyclus, en frequentie moet altijd positief zijn. (positie done)
        • De naam wordt gebruikt als unieke identificatie van een baan.
     */


    vector<string> baanNaam;
    map<string, BaanInfo> baanAcc;
    for(int j = 0; j < (int) banen.size(); j++){
        baanNaam.push_back(banen[j].naam);
        pair<string, BaanInfo> baanInsert (banen[j].naam, banen[j]);
        baanAcc.insert(baanInsert);
    }
    //Elk voertuig staat op een bestaande baan.
    //De positie van elk voertuig is kleiner dan de lengte van de baan.
    for(unsigned i = 0; i < voertuigen.size(); i++){
        const VoertuigInfo& currVoertuig = voertuigen[i];
        string baan = currVoertuig.baanNaam;
        int baanpos = currVoertuig.positie;
        if((count(baanNaam.begin(), baanNaam.end(), baan)) != 0){
            int baanlengte = baanAcc[baan].lengte;
            if(baanpos > baanlengte){
                errstr << "car " << i << " outside of length of " << baan << "\n";
            }
        }
        else{
            errstr << baan <<" does not exitst\n";
        }
        if(baanpos < 0){
            errstr << "car " << i << " is not on the road";
        }
    }

    //Elk verkeerslicht staat op een bestaande baan.
    //De positie van elk verkeerslicht is kleiner dan de lengte van de baan.
    for(int i = 0; i < (int) verkeerslichten.size(); i++){
        const VerkeerslichtInfo& currVerkeer = verkeerslichten[i];
        int x = i;
        if(i != 0){
            x = i-1;
        }
        const VerkeerslichtInfo& prevVerkeer = verkeerslichten[x];
        string baan = currVerkeer.baanNaam;
        int baanpos = currVerkeer.positie;
        if((count(baanNaam.begin(), baanNaam.end(), baan)) != 0){
            int baanlengte = baanAcc[baan].lengte;
            if(baanpos > baanlengte){
                errstr << "verkeerslicht " << i << " outside of length of " << baan << "\n";
            }
        }
        else{
            errstr << baan <<" does not exitst\n";
        }
        if(baanpos < 0){
            errstr << "verkeerslicht " << i << " is not on the road";
        }
        if(i != 0){
            if (currVerkeer.positie - 50 <= prevVerkeer.positie){
                errstr << "Verkeerslicht " << i << " too close to Verkeerslicht " << i-1 << "\n";
            }
        }

        if(verkeerslichten[i].positie < 0) errstr << "Verkeerslicht not on road\n";
        if(verkeerslichten[i].cyclus <= 0) errstr << "Verkeerslicht cannot have cyclus <= 0\n";
    }

    for(int i = 0; i < (int) Generatoren.size(); i++){
        const VoertuiggeneratorInfo& generatorInfo = Generatoren[i];

        if(generatorInfo.frequentie <= 0) {
            errstr << "Voertuiggenerator: frequentie mag niet 0 of negatief zijn\n";
        }

        if(!VoertuigFactory::getInstance()->isValidType(generatorInfo.type)) {
            errstr << "Voertuiggenerator: type is niet valid\n";
        }

        bool baanExists = false;
        for(int j = 0; j < (int) banen.size(); j++) {
            if(banen[j].naam == generatorInfo.baanNaam)
                baanExists = true;
        }
        if(!baanExists) {
            errstr << "Voertuiggenerator: baan van generator bestaat niet\n";
        }
    }

    // Bushaltes consistency checks
    for(vector<BushalteInfo>::size_type i = 0; i < bushaltes.size(); i++) {
        bool bushalteOpBestaandeBaan = false;
        const BaanInfo* baanVanBushalte = NULL;
        for(vector<BaanInfo>::size_type j = 0; j < banen.size(); j++) {
            if(banen[j].naam == bushaltes[i].baanNaam) {
                bushalteOpBestaandeBaan = true;
                baanVanBushalte = &banen[j];
                break;
            }
        }
        if(!bushalteOpBestaandeBaan) { errstr << "Bushalte not on existing road\n"; return; } // RETURNEN, anders dikke pech met een nullpointer dereference

        if(bushaltes[i].positie < 0 || bushaltes[i].positie > baanVanBushalte->lengte) errstr << "Bushalte not on road\n";

        if(bushaltes[i].wachttijd <= 0) errstr << "Bushalte cannot have wachttijd <= 0\n";
    }


}

void VerkeerssituatieReader::read(const std::string& situatieFile, std::ostream &errstr)
{
    using namespace std;
    TiXmlDocument doc;
    if(!doc.LoadFile(situatieFile.c_str())) {
        errstr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL) {
        errstr << "Couldn't read root\n";
        return;
    }

    for(TiXmlElement* verkeersElement = root->FirstChildElement(); verkeersElement != NULL;
        verkeersElement = verkeersElement->NextSiblingElement())
    {
        string verkeersElementNaam = verkeersElement->Value();
        if(verkeersElementNaam == "BAAN") {
            TiXmlElement* naamNode = NULL;
            TiXmlElement* lengteNode = NULL;
            for(TiXmlElement* baanComponent = verkeersElement->FirstChildElement(); baanComponent != NULL;
                baanComponent = baanComponent->NextSiblingElement())
            {
                if(std::string(baanComponent->Value()) == "naam")
                    naamNode = baanComponent;
                if(std::string(baanComponent->Value()) == "lengte")
                    lengteNode = baanComponent;
            }
            if(!naamNode || !lengteNode) {
                errstr << "Ontbrekende child node in BAAN\n";
                continue;
            }
            std::string naam = naamNode->GetText();

            bool success;
            int lengte = tryParseInt(lengteNode->GetText(), success);
            if(!success) {
                errstr << "BAAN:LENGTE is geen getal\n";
                continue;
            }

            BaanInfo baan(naam, lengte);
            banen.push_back(baan);

            continue;
        }
        if(verkeersElementNaam == "VERKEERSLICHT") {
            TiXmlElement* naamNode = NULL;
            TiXmlElement* positieNode = NULL;
            TiXmlElement* cyclusNode = NULL;
            // Deze nodes zijn niet per se in een vaste volgorde, we moeten dus met een for loop de componenten aflopen
            for(TiXmlElement* verkeerslichtComponent = verkeersElement->FirstChildElement(); verkeerslichtComponent != NULL;
                verkeerslichtComponent = verkeerslichtComponent->NextSiblingElement())
            {
                if(std::string(verkeerslichtComponent->Value()) == "baan") // cast de Value naar string, anders werkt dit niet
                    naamNode = verkeerslichtComponent;
                if(std::string(verkeerslichtComponent->Value()) == "positie")
                    positieNode = verkeerslichtComponent;
                if(std::string(verkeerslichtComponent->Value()) == "cyclus")
                    cyclusNode = verkeerslichtComponent;
            }
            if(!naamNode || !positieNode || !cyclusNode) {
                errstr << "Ontbrekende child node in VERKEERSLICHT\n";
                continue;
            }

            std::string naam = naamNode->GetText();

            bool success;
            int lengte = tryParseInt(positieNode->GetText(), success);
            if(!success) {
                errstr << "VERKEERSLICHT:LENGTE is geen getal\n";
                continue;
            }

            int cyclus = tryParseInt(cyclusNode->GetText(), success);
            if(!success) {
                errstr << "VERKEERSLICHT:CYCLUS is geen getal\n";
                continue;
            }

            VerkeerslichtInfo licht(naam, lengte, cyclus);
            verkeerslichten.push_back(licht);

            continue;
        }
        if(verkeersElementNaam == "VOERTUIG") {
            TiXmlElement* baanNaamNode = NULL;
            TiXmlElement* positieNode = NULL;
            TiXmlElement* typeNode = NULL;
            // Deze nodes zijn niet per se in een vaste volgorde, we moeten dus met een for loop de componenten aflopen
            for(TiXmlElement* voertuigComponent = verkeersElement->FirstChildElement(); voertuigComponent != NULL;
                voertuigComponent = voertuigComponent->NextSiblingElement())
            {
                if(std::string(voertuigComponent->Value()) == "baan") // cast de Value naar string, anders werkt dit niet
                    baanNaamNode = voertuigComponent;
                if(std::string(voertuigComponent->Value()) == "positie")
                    positieNode = voertuigComponent;
                if(std::string(voertuigComponent->Value()) == "type")
                    typeNode = voertuigComponent;
            }
            if(!baanNaamNode || !positieNode || !typeNode) {
                errstr << "ERROR: Ontbrekende child node in VOERTUIG\n";
                continue;
            }

            std::string baanNaam = baanNaamNode->GetText();

            bool success;
            int positie = tryParseInt(positieNode->GetText(),success);
            if(!success) {
                errstr << "ERROR: VOERTUIG:POSITIE is geen getal\n";
                continue;
            }

            std::string Type = typeNode->GetText();
            if(Type != "auto" && Type != "bus" && Type != "brandweerwagen" && Type != "ziekenwagen" && Type != "politiecombi") {
                errstr << "ERROR: VOERTUIG:TYPE is geen valide type\n";
                continue;
            }


            VoertuigInfo voertuig(baanNaam, Type, positie);
            voertuigen.push_back(voertuig);

            continue;
        }
        if(verkeersElementNaam == "VOERTUIGGENERATOR") {
            TiXmlElement* naamNode = NULL;
            TiXmlElement* frequentieNode = NULL;
            TiXmlElement* typeNode = NULL;
            // Deze nodes zijn niet per se in een vaste volgorde, we moeten dus met een for loop de componenten aflopen
            for(TiXmlElement* verkeerslichtComponent = verkeersElement->FirstChildElement(); verkeerslichtComponent != NULL;
                verkeerslichtComponent = verkeerslichtComponent->NextSiblingElement())
            {
                if(std::string(verkeerslichtComponent->Value()) == "baan") // cast de Value naar string, anders werkt dit niet
                    naamNode = verkeerslichtComponent;
                if(std::string(verkeerslichtComponent->Value()) == "type")
                    typeNode = verkeerslichtComponent;
                if(std::string(verkeerslichtComponent->Value()) == "frequentie")
                    frequentieNode = verkeerslichtComponent;
            }
            if(!naamNode || !typeNode || !frequentieNode) {
                errstr << "Ontbrekende child node in VOERTUIGGENERATOR\n";
                continue;
            }

            std::string naam = naamNode->GetText();

            bool success;
            int frequentie = tryParseInt(frequentieNode->GetText(), success);
            if(!success) {
                errstr << "VOERTUIGGENERATOR:FREQUENTIE is geen getal\n";
                continue;
            }

            std::string Type = typeNode->GetText();
            if(Type != "auto" && Type != "bus" && Type != "brandweerwagen" && Type != "ziekenwagen" && Type != "politiecombi") {
                errstr << "ERROR: VOERTUIG:TYPE is geen valide type\n";
                continue;
            }

            VoertuiggeneratorInfo voertuiggenerator(naam, Type, frequentie);
            Generatoren.push_back(voertuiggenerator);
            continue;
        }

        if(verkeersElementNaam == "BUSHALTE") {
            TiXmlElement* baanNaamNode = NULL;
            TiXmlElement* positieNode = NULL;
            TiXmlElement* wachttijdNode = NULL;
            // Deze nodes zijn niet per se in een vaste volgorde, we moeten dus met een for loop de componenten aflopen
            for(TiXmlElement* bushalteComponent = verkeersElement->FirstChildElement(); bushalteComponent != NULL;
                bushalteComponent = bushalteComponent->NextSiblingElement())
            {
                if(std::string(bushalteComponent->Value()) == "baan") // cast de Value naar string, anders werkt dit niet
                    baanNaamNode = bushalteComponent;
                if(std::string(bushalteComponent->Value()) == "positie")
                    positieNode = bushalteComponent;
                if(std::string(bushalteComponent->Value()) == "wachttijd")
                    wachttijdNode  = bushalteComponent;
            }
            if(!baanNaamNode || !positieNode || !wachttijdNode ) {
                errstr << "ERROR: Ontbrekende child node in BUSHALTE\n";
                continue;
            }

            std::string baanNaam = baanNaamNode->GetText();

            bool success;
            int positie = tryParseInt(positieNode->GetText(),success);
            if(!success) {
                errstr << "ERROR: BUSHALTE:POSITIE is geen getal\n";
                continue;
            }

            int wachttijd = tryParseInt(wachttijdNode->GetText(), success);
            if(!success) {
                errstr << "ERROR: BUSHALTE:WACHTTIJD is geen getal\n";
                continue;
            }

            bushaltes.push_back(BushalteInfo(baanNaam, positie, wachttijd));

            continue;
        }

        errstr << "Onherkenbaar element: " << verkeersElementNaam << "\n";
    }



}
