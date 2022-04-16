//
// Created by kobedb on 15.04.22.
//

#ifndef PROJECT_PSE_VOERTUIGFACTORY_H
#define PROJECT_PSE_VOERTUIGFACTORY_H

#include <map>
#include <string>
#include <algorithm>

#include "voertuigen/Auto.h"


//Een VoertuigFactory om zeer gemakkelijk van een voertuig-type(in string formaat) de juiste afgeleide klasse van Voertuig te instantieren.
//Bv. create("auto", "Middelheimlaan", 123) creeert een Auto instantie met de juiste parameters voor de constructor.
//
//Deze Factory kan overal in het project gebruikt worden en zal zeer belangrijk zijn in de Voertuiggenerator.

class VoertuigFactory {
    static VoertuigFactory* factory;
public:
    static VoertuigFactory* getInstance();
private:
    std::vector<std::string> voertuigTypes;
    VoertuigFactory();

public:
    bool isValidType(const std::string& voertuigType) const;

    Voertuig* create(const std::string& voertuigType, const std::string& baanNaam, int positie);

};


#endif //PROJECT_PSE_VOERTUIGFACTORY_H
