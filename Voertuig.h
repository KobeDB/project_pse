//
// Created by kobedb on 17.03.22.
//

#ifndef PROJECT_PSE_VOERTUIG_H
#define PROJECT_PSE_VOERTUIG_H

#include <string>
#include <iostream>

#include "Baan.h"


class Voertuig {
private:
    std::string baanNaam;
    int positie;
    float snelheid;
    float versnelling;
public:
    Voertuig(const std::string& baanNaam, int positie)
        : baanNaam(baanNaam), positie(positie), snelheid(0), versnelling(10) {}

    const std::string& getBaanNaam() const {return baanNaam;}
    int getPositie() const {return positie;}
    int getSnelheid() const {return snelheid;}
    int getVersnelling() const {return versnelling;}

    void update(float deltaTime_s, const Baan& baan);
};

std::ostream& operator<<(std::ostream& os, const Voertuig& tuig);


#endif //PROJECT_PSE_VOERTUIG_H
