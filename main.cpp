#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <unistd.h>
#include "tinyxml.h"

#include "Verkeerslicht.h"
#include "Baan.h"
#include "Vekeerssimulatie.h"
#include "Voertuig.h"


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

int main() {
    using namespace std;

    TiXmlDocument doc;
    if(!doc.LoadFile("test.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL) {
        cerr << "Couldn't read root\n";
    }

    std::vector<Verkeerslicht> verkeerslichten;
    std::vector<Baan> banen;
    std::vector<Voertuig> voertuigen;

    //TODO: Het inlezen van de xml file moet misschien in de simulatie class gestoken worden, ipv het hier in de main te zetten
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
                std::cerr << "Ontbrekende child node in BAAN\n";
            }
            std::string naam = naamNode->GetText();

            bool success;
            int lengte = tryParseInt(lengteNode->GetText(), success);
            if(!success) {
                std::cerr << "BAAN:LENGTE is geen getal\n";
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
                std::cerr << "Ontbrekende child node in VERKEERSLICHT\n";
                continue;
            }

            std::string naam = naamNode->GetText();

            bool success;
            int lengte = tryParseInt(positieNode->GetText(), success);
            if(!success) {
                std::cerr << "VERKEERSLICHT:LENGTE is geen getal\n";
                continue;
            }

            int cyclus = tryParseInt(cyclusNode->GetText(), success);
            if(!success) {
                std::cerr << "VERKEERSLICHT:CYCLUS is geen getal\n";
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
                std::cerr << "ERROR: Ontbrekende child node in VOERTUIG\n";
                continue;
            }

            std::string baanNaam = baanNaamNode->GetText();

            bool success;
            int positie = tryParseInt(positieNode->GetText(),success);
            if(!success) {
                std::cerr << "ERROR: VOERTUIG:POSITIE is geen getal\n";
                continue;
            }

            Voertuig voertuig(baanNaam, positie);
            voertuigen.push_back(voertuig);

            continue;
        }
        cerr << "Onherkenbaar element: " << verkeersElementNaam << "\n";
    }

    Verkeerssimulatie simulatie(banen, verkeerslichten, voertuigen);
    std::cout << "SIMULATIE: \n";
    std::cout << simulatie << "\n";
    float time = 0;
    for(int i = 0; i < 15; i++) {
        float deltaTime_s = 1;
        usleep((int)(deltaTime_s * 1000000));
        time += deltaTime_s;
        simulatie.update(deltaTime_s);
        std::cout << "\tTijd: " << time << "\n";
        std::cout << simulatie << "\n";
    }

    return 0;
}
