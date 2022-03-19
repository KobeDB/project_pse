//
// Created by kobedb on 19.03.22.
//

#include "VerkeerssituatieReader.h"

#include "tinyxml.h"
#include <sstream>

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
    /*
     * Een verkeerssituatie is consistent als:
        • Elk voertuig staat op een bestaande baan.
        • Elk verkeerslicht staat op een bestaande baan.
        • Elke voertuiggenerator staat op een bestaande baan.
        • De positie van elk voertuig is kleiner dan de lengte van de baan.
        • De positie van elk verkeerslicht is kleiner dan de lengte van de baan.
        • Er is maximaal  ́een voertuiggenerator op elke baan. NOG NIET
        • Een verkeerslicht mag zich niet in de vertraagafstand van een ander
        verkeerslicht bevinden (zie Appendix B).
        Opmerkingen:
        • Lengte, positie, cyclus, en frequentie moet altijd positief zijn.
        • De naam wordt gebruikt als unieke identificatie van een baan.
     */

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
