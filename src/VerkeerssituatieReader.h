//
// Created by kobedb on 19.03.22.
//

#ifndef PROJECT_PSE_VERKEERSSITUATIEREADER_H
#define PROJECT_PSE_VERKEERSSITUATIEREADER_H

#include <iostream>
#include <string>
#include <vector>

#include "Baan.h"
#include "Verkeerslicht.h"
#include "Voertuig.h"


/// Hulp data structuren nodig om de xml file informatie om te zetten in concrete c++ data structuren
/// Deze datastructuren bewaren geen invarianten, omdat deze worden gebruikt voor het
/// nakijken van de verkeers-consistentie. Deze structs worden absoluut niet intern gebruikt in de simulatie!

struct BaanInfo {
    std::string naam;
    int lengte;

    // Default constructor nodig om BaanInfo te kunnen gebruiken in een map
    BaanInfo() : naam(), lengte() {}
    BaanInfo(const std::string& naam, int lengte) : naam(naam), lengte(lengte) {}
};

struct VoertuigInfo {
    std::string baanNaam;
    int positie;

    // Het definieren van een constructor DWINGT de user om alle velden te initialiseren !
    VoertuigInfo(const std::string& baanNaam, int positie) : baanNaam(baanNaam), positie(positie) {}
};

struct VerkeerslichtInfo {
    std::string baanNaam;
    int positie;
    int cyclus;

    VerkeerslichtInfo(const std::string& baanNaam, int positie, int cyclus) : baanNaam(baanNaam), positie(positie), cyclus(cyclus) {}
};

class VerkeerssituatieReader {
    std::vector<BaanInfo> banen;
    std::vector<VerkeerslichtInfo> verkeerslichten;
    std::vector<VoertuigInfo> voertuigen;
public:
    VerkeerssituatieReader(std::string situatieFile, std::ostream& errstr);

private:
    void read(std::string situatieFile, std::ostream &errstr);
    void checkConsistency(std::ostream& errstr);

public:
    const std::vector<BaanInfo>& getBanen() {return banen;}
    const std::vector<VerkeerslichtInfo>& getVerkeerslichten() {return verkeerslichten;}
    const std::vector<VoertuigInfo>& getVoertuigen() {return voertuigen;}
};


#endif //PROJECT_PSE_VERKEERSSITUATIEREADER_H
