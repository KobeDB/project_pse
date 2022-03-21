//
// Created by kobedb on 19.03.22.
//

#include "VerkeerssituatieReader.h"

#include "tinyxml.h"
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
    map<string, Baan> baanAcc;
    for(int j = 0; j < (int) banen.size(); j++){
        baanNaam.push_back(banen[j].getNaam());
        pair<string, Baan> baanInsert (banen[j].getNaam(), banen[j]);
        baanAcc.insert(baanInsert);
    }
    //Elk voertuig staat op een bestaande baan.
    //De positie van elk voertuig is kleiner dan de lengte van de baan.
    for(unsigned i = 0; i < voertuigen.size(); i++){
        const Voertuig* currVoertuig = &voertuigen[i];
        string baan = currVoertuig->getBaanNaam();
        int baanpos = currVoertuig->getPositie();
        if((count(baanNaam.begin(), baanNaam.end(), baan)) != 0){
            int baanlengte = baanAcc[baan].getLengte();
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
        const Verkeerslicht& currVerkeer = verkeerslichten[i];
        int x = i;
        if(i != 0){
            x = i-1;
        }
        const Verkeerslicht& prevVerkeer = verkeerslichten[x];
        string baan = currVerkeer.getBaanNaam();
        int baanpos = currVerkeer.getPositie();
        if((count(baanNaam.begin(), baanNaam.end(), baan)) != 0){
            int baanlengte = baanAcc[baan].getLengte();
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
            if (currVerkeer.getPositie() - 50 <= prevVerkeer.getPositie()){
                errstr << "Verkeerslicht " << i << " too close to Verkeerslicht " << i-1 << "\n";
            }
        }
    }


}

void VerkeerssituatieReader::read(std::string situatieFile, std::ostream &errstr)
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

            Baan baan(naam, lengte);
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

            Verkeerslicht licht(naam, lengte, cyclus);
            verkeerslichten.push_back(licht);

            continue;
        }
        if(verkeersElementNaam == "VOERTUIG") {
            TiXmlElement* baanNaamNode = NULL;
            TiXmlElement* positieNode = NULL;
            // Deze nodes zijn niet per se in een vaste volgorde, we moeten dus met een for loop de componenten aflopen
            for(TiXmlElement* voertuigComponent = verkeersElement->FirstChildElement(); voertuigComponent != NULL;
                voertuigComponent = voertuigComponent->NextSiblingElement())
            {
                if(std::string(voertuigComponent->Value()) == "baan") // cast de Value naar string, anders werkt dit niet
                    baanNaamNode = voertuigComponent;
                if(std::string(voertuigComponent->Value()) == "positie")
                    positieNode = voertuigComponent;
            }
            if(!baanNaamNode || !positieNode) {
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

            Voertuig voertuig(baanNaam, positie);
            voertuigen.push_back(voertuig);

            continue;
        }
        errstr << "Onherkenbaar element: " << verkeersElementNaam << "\n";
    }
}
