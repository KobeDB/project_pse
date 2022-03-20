//
// Created by kobedb on 17.03.22.
//

#include "Voertuig.h"
#include <cmath>

#include "DesignByContract.h"

#include "Baan.h"

using namespace std;

Voertuig::Voertuig(const std::string &baanNaam, int positie): baanNaam(baanNaam), positie(positie), snelheid(0), versnelling(10), snelheid_max(16.6)
{
    REQUIRE(positie >= 0, "positie mag niet negatief zijn");
    REQUIRE(snelheid >= 0, "snelheid mag niet negatief zijn");
    REQUIRE(!baanNaam.empty(), "baanNaam mag niet leeg zijn");

    _initCheck = this;
    ENSURE(this->properlyInitialized(), "constructor must end in properly initialized state");
}

void Voertuig::update(float deltaTime_s, const Verkeerslicht* licht, const Voertuig* voorligger)
{
    REQUIRE(properlyInitialized(), "class not properly initialized");
    REQUIRE(deltaTime_s >= 0, "deltaTime_s mag niet negatief zijn");

    float nieuweSnelheid = snelheid + deltaTime_s * versnelling;
    if(nieuweSnelheid < 0 ) {
        positie = (int)((float)positie - pow(snelheid, 2) / (2 * versnelling));
        snelheid = 0;
    }
    else {
        snelheid = nieuweSnelheid;
        positie += (int)(snelheid * deltaTime_s);
    }

    float delta = 0;
    if(voorligger) {
        int dPositie = voorligger->getPositie() - positie - VOERTUIG_LENGTE;
        float dSnelheid = snelheid - voorligger->getSnelheid();
        delta = (MINIMALE_VOLGAFSTAND + std::max((float)0, snelheid + (snelheid * dSnelheid)/(2 * sqrt(VERSNELLING_MAX * REMFACTOR_MAX)))) / (float)dPositie;
    }
    versnelling = VERSNELLING_MAX * (1 - pow((snelheid / snelheid_max), 4) - pow(delta, 2));

    if(licht && licht->getIsRood()) {
        if((licht->getPositie() - positie) < STOPAFSTAND) {
            versnelling = -REMFACTOR_MAX * snelheid / snelheid_max;
        }
        else if((licht->getPositie() - positie) < VERTRAAGAFSTAND) {
            snelheid_max = VERTRAAGFACTOR * V_MAX;
        }
    }
    else {
        snelheid_max = V_MAX;
    }
}

bool Voertuig::properlyInitialized() const {
    return _initCheck == this;
}


std::ostream& operator<<(std::ostream& os, const Voertuig& tuig) {
    REQUIRE(tuig.properlyInitialized(), "class not properly initialized");

    os << "\t\t-> baan: " << tuig.getBaanNaam() << "\n";
    os << "\t\t-> positie: " << tuig.getPositie() << "\n";
    os << "\t\t-> snelheid: " << tuig.getSnelheid();
    return os;
}