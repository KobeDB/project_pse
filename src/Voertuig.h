//
// Created by kobedb on 17.03.22.
//

#ifndef PROJECT_PSE_VOERTUIG_H
#define PROJECT_PSE_VOERTUIG_H

#include <string>
#include <iostream>

#include "Baan.h"

// Walgelijke macros omdat c++98 (alleszins mijn compiler) geen const members wil initializen :(
#define V_MAX 16.6f
#define VERTRAAGFACTOR 0.4f
#define REMFACTOR_MAX 4.61f
#define VERSNELLING_MAX 1.44f
#define VERTRAAGAFSTAND 50
#define STOPAFSTAND 15

class Voertuig {
private:
    std::string baanNaam;
    int positie;
    float snelheid;
    float versnelling;
    float snelheid_max; // Dit is niet constant omdat dit wordt herberekend bij het vertragen

public:
    Voertuig(const std::string &baanNaam, int positie)
        : baanNaam(baanNaam), positie(positie), snelheid(0), versnelling(10), snelheid_max(16.6) {}

    const std::string& getBaanNaam() const {return baanNaam;}
    int getPositie() const {return positie;}
    int getSnelheid() const {return snelheid;}
    int getVersnelling() const {return versnelling;}

    void update(float deltaTime_s, const Baan& baan);
};

std::ostream& operator<<(std::ostream& os, const Voertuig& tuig);


#endif //PROJECT_PSE_VOERTUIG_H
