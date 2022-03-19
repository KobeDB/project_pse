//
// Created by kobedb on 17.03.22.
//

#include "Verkeerssimulatie.h"
#include "tinyxml.h"

#include <algorithm>
#include <sstream>

void Verkeerssimulatie::addVerkeerslicht(const Verkeerslicht& licht)
{
    verkeerslichten.push_back(licht);
}

void Verkeerssimulatie::addBaan(const Baan &baan)
{
    banen[baan.getNaam()] = baan;
}

std::ostream &operator<<(std::ostream &os, const Verkeerssimulatie &sim)
{

//    for(int i = 0; i < sim.voertuigen.size(); i++) {
//        os << "\tVoertuig " << (i+1) << "\n";
//        os << "\t\t-> baan: " << sim.voertuigen[i].getBaanNaam() << "\n";
//        os << "\t\t-> positie: " << sim.voertuigen[i].getPositie() << "\n";
//        os << "\t\t-> snelheid: " << sim.voertuigen[i].getSnelheid() << "\n";
//    }

    for(unsigned i = 0; i < sim.voertuigen.size(); i++) {
        os << "\tVoertuig " << (i+1) << "\n";
        os << sim.voertuigen[i] << "\n";
    }

    return os;
}

Verkeerssimulatie::Verkeerssimulatie(const std::vector<Baan> &pBanen, const std::vector<Verkeerslicht> &pLichten,
                                     const std::vector<Voertuig> &pVoertuigen)
                                     : banen(), verkeerslichten(pLichten), voertuigen(pVoertuigen)
                                     {
    for(unsigned b = 0; b < pBanen.size(); b++) {
        const Baan& baan = pBanen[b];
        banen[baan.getNaam()] = baan;
        for(unsigned l = 0; l < verkeerslichten.size(); l++) {
            Verkeerslicht& licht = verkeerslichten[l];
            if(licht.getBaanNaam() != baan.getNaam())
                continue;
            banen[baan.getNaam()].addVerkeerslicht(licht);
        }
    }
    std::cout << "";

}

void Verkeerssimulatie::update(float deltaTime_s)
{
    for(unsigned i = 0; i < verkeerslichten.size(); i++) {
        Verkeerslicht& licht = verkeerslichten[i];
        licht.update(deltaTime_s);
    }

    // We lopen de lijst van achter naar voren af, omdat we de lijst ondertussen bewerken
    for(int i = voertuigen.size()-1; i >= 0; i--) {
        Voertuig& tuig = voertuigen[i];
        const Baan& baanVanTuig = banen[tuig.getBaanNaam()];
        tuig.update(deltaTime_s, baanVanTuig);
        if(tuig.getPositie() > baanVanTuig.getLengte()) {
            voertuigen.erase(voertuigen.begin() + i);
        }
    }

}

//int tryParseInt(const std::string& s, bool& success)
//{
//    std::stringstream iss(s);
//    int val;
//    iss >> val;
//    if(!iss) {
//        success = false;
//        return 0;
//    }
//    success = true;
//    return val;
//}
//
//void readVerkeerssituatieFromXml(const std::string& xmlFile, std::vector<Baan>& banen, std::vector<Verkeerslicht>& verkeerslichten, std::vector<Voertuig>& voertuigen)
//{
//    using namespace std;
//    TiXmlDocument doc;
//    if(!doc.LoadFile(xmlFile.c_str())) {
//        std::cerr << doc.ErrorDesc() << std::endl;
//        return;
//    }
//
//    TiXmlElement* root = doc.FirstChildElement();
//    if(root == NULL) {
//        cerr << "Couldn't read root\n";
//    }
//
//    //TODO: Het inlezen van de xml file moet misschien in de simulatie class gestoken worden, ipv het hier in de main te zetten
//    for(TiXmlElement* verkeersElement = root->FirstChildElement(); verkeersElement != NULL;
//        verkeersElement = verkeersElement->NextSiblingElement())
//    {
//        string verkeersElementNaam = verkeersElement->Value();
//        if(verkeersElementNaam == "BAAN") {
//            TiXmlElement* naamNode = NULL;
//            TiXmlElement* lengteNode = NULL;
//            for(TiXmlElement* baanComponent = verkeersElement->FirstChildElement(); baanComponent != NULL;
//                baanComponent = baanComponent->NextSiblingElement())
//            {
//                if(std::string(baanComponent->Value()) == "naam")
//                    naamNode = baanComponent;
//                if(std::string(baanComponent->Value()) == "lengte")
//                    lengteNode = baanComponent;
//            }
//            if(!naamNode || !lengteNode) {
//                std::cerr << "Ontbrekende child node in BAAN\n";
//            }
//            std::string naam = naamNode->GetText();
//
//            bool success;
//            int lengte = tryParseInt(lengteNode->GetText(), success);
//            if(!success) {
//                std::cerr << "BAAN:LENGTE is geen getal\n";
//                continue;
//            }
//
//            Baan baan(naam, lengte);
//            banen.push_back(baan);
//
//            continue;
//        }
//        if(verkeersElementNaam == "VERKEERSLICHT") {
//            TiXmlElement* naamNode = NULL;
//            TiXmlElement* positieNode = NULL;
//            TiXmlElement* cyclusNode = NULL;
//            // Deze nodes zijn niet per se in een vaste volgorde, we moeten dus met een for loop de componenten aflopen
//            for(TiXmlElement* verkeerslichtComponent = verkeersElement->FirstChildElement(); verkeerslichtComponent != NULL;
//                verkeerslichtComponent = verkeerslichtComponent->NextSiblingElement())
//            {
//                if(std::string(verkeerslichtComponent->Value()) == "baan") // cast de Value naar string, anders werkt dit niet
//                    naamNode = verkeerslichtComponent;
//                if(std::string(verkeerslichtComponent->Value()) == "positie")
//                    positieNode = verkeerslichtComponent;
//                if(std::string(verkeerslichtComponent->Value()) == "cyclus")
//                    cyclusNode = verkeerslichtComponent;
//            }
//            if(!naamNode || !positieNode || !cyclusNode) {
//                std::cerr << "Ontbrekende child node in VERKEERSLICHT\n";
//                continue;
//            }
//
//            std::string naam = naamNode->GetText();
//
//            bool success;
//            int lengte = tryParseInt(positieNode->GetText(), success);
//            if(!success) {
//                std::cerr << "VERKEERSLICHT:LENGTE is geen getal\n";
//                continue;
//            }
//
//            int cyclus = tryParseInt(cyclusNode->GetText(), success);
//            if(!success) {
//                std::cerr << "VERKEERSLICHT:CYCLUS is geen getal\n";
//                continue;
//            }
//
//            Verkeerslicht licht(naam, lengte, cyclus);
//            verkeerslichten.push_back(licht);
//
//            continue;
//        }
//        if(verkeersElementNaam == "VOERTUIG") {
//            TiXmlElement* baanNaamNode = NULL;
//            TiXmlElement* positieNode = NULL;
//            // Deze nodes zijn niet per se in een vaste volgorde, we moeten dus met een for loop de componenten aflopen
//            for(TiXmlElement* voertuigComponent = verkeersElement->FirstChildElement(); voertuigComponent != NULL;
//                voertuigComponent = voertuigComponent->NextSiblingElement())
//            {
//                if(std::string(voertuigComponent->Value()) == "baan") // cast de Value naar string, anders werkt dit niet
//                    baanNaamNode = voertuigComponent;
//                if(std::string(voertuigComponent->Value()) == "positie")
//                    positieNode = voertuigComponent;
//            }
//            if(!baanNaamNode || !positieNode) {
//                std::cerr << "ERROR: Ontbrekende child node in VOERTUIG\n";
//                continue;
//            }
//
//            std::string baanNaam = baanNaamNode->GetText();
//
//            bool success;
//            int positie = tryParseInt(positieNode->GetText(),success);
//            if(!success) {
//                std::cerr << "ERROR: VOERTUIG:POSITIE is geen getal\n";
//                continue;
//            }
//
//            Voertuig voertuig(baanNaam, positie);
//            voertuigen.push_back(voertuig);
//
//            continue;
//        }
//        cerr << "Onherkenbaar element: " << verkeersElementNaam << "\n";
//    }
//}

