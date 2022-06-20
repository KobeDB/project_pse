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
#include "voertuigen/Voertuig.h"


/// Hulp data structuren nodig om de xml file informatie om te zetten in concrete c++ data structuren
/// Deze datastructuren bewaren geen invarianten, omdat deze worden gebruikt voor het
/// nakijken van de verkeers-consistentie. Deze structs worden absoluut niet intern gebruikt in de simulatie!

// Immutable struct, dus geen immutability check nodig
struct BaanInfo {
    const std::string naam;
    const int lengte;

    // Default constructor nodig om BaanInfo te kunnen gebruiken in een map
    BaanInfo() : naam(), lengte() {}
    BaanInfo(const std::string& naam, int lengte) : naam(naam), lengte(lengte) {}
};

// Immutable struct
struct VoertuigInfo {
    const std::string baanNaam;
    const int positie;
    const std::string type; //TEST: dit nog uitlezen en invullen

    // Het definieren van een constructor DWINGT de user om alle velden te initialiseren !
    // TEST: Hier nog string type parameter binnen nemen en invullen
    VoertuigInfo(const std::string& baanNaam, const std::string& Type, int positie) : baanNaam(baanNaam), positie(positie), type(Type) {}
};

// Immutable struct
struct VerkeerslichtInfo {
    const std::string baanNaam;
    const int positie;
    const int cyclus;

    VerkeerslichtInfo(const std::string& baanNaam, int positie, int cyclus) : baanNaam(baanNaam), positie(positie), cyclus(cyclus) {}
};

struct VoertuiggeneratorInfo {
    const std::string baanNaam;
    const std::string type;
    const int frequentie;

    VoertuiggeneratorInfo(const std::string& baanNaam, const std::string& type, int frequentie) : baanNaam(baanNaam), type(type), frequentie(frequentie) {}
};

struct BushalteInfo {
    const std::string baanNaam;
    const int positie;
    const int wachttijd;

    BushalteInfo(const std::string& baanNaam, int positie, int wachttijd) : baanNaam(baanNaam), positie(positie), wachttijd(wachttijd) {}
};

class VerkeerssituatieReader {
    std::vector<BaanInfo> banen;
    std::vector<VerkeerslichtInfo> verkeerslichten;
    std::vector<VoertuigInfo> voertuigen;
    std::vector<VoertuiggeneratorInfo> Generatoren;
    std::vector<BushalteInfo> bushaltes;
public:
    VerkeerssituatieReader(std::string situatieFile, std::ostream& errstr);

private:
    void read(const std::string& situatieFile, std::ostream &errstr);
    void checkConsistency(std::ostream& errstr);

public:
    const std::vector<BaanInfo>& getBanen() const {return banen;}
    const std::vector<VerkeerslichtInfo>& getVerkeerslichten() const {return verkeerslichten;}
    const std::vector<VoertuigInfo>& getVoertuigen() const {return voertuigen;}
    const std::vector<VoertuiggeneratorInfo>& getVoertuiggeneratoren() const {return Generatoren;}
    const std::vector<BushalteInfo>& getBushaltes() const {return bushaltes;}
};


#endif //PROJECT_PSE_VERKEERSSITUATIEREADER_H
