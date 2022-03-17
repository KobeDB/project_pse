//
// Created by kobedb on 17.03.22.
//

#ifndef PROJECT_PSE_BAAN_H
#define PROJECT_PSE_BAAN_H

#include <iostream>
#include <string>
#include <vector>

#include "Verkeerslicht.h"

class Baan {
private:
    std::string naam;
    int lengte;
    std::vector<Verkeerslicht*> lichten;
public:
    Baan() : naam(), lengte() {}
    Baan(const std::string& naam, int lengte) : naam(naam), lengte(lengte) {}

    const std::string& getNaam() const {return naam;}
    int getLengte() const {return lengte;}

    void addVerkeerslicht(Verkeerslicht& licht);
};

/// functie om een Baan mooi af te printen
std::ostream& operator<<(std::ostream& os, const Baan& baan);



#endif //PROJECT_PSE_BAAN_H
