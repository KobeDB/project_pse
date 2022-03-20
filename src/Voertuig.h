//
// Created by kobedb on 17.03.22.
//

#ifndef PROJECT_PSE_VOERTUIG_H
#define PROJECT_PSE_VOERTUIG_H

#include <string>
#include <iostream>
#include <map>
#include "DesignByContract.h"

#include "Baan.h"

// Walgelijke macros omdat c++98 (alleszins mijn compiler) geen const members wil initializen :(
#define V_MAX 16.6f
#define VERTRAAGFACTOR 0.4f
#define REMFACTOR_MAX 4.61f
#define VERSNELLING_MAX 1.44f
#define VERTRAAGAFSTAND 50
#define STOPAFSTAND 15
#define MINIMALE_VOLGAFSTAND 4
#define VOERTUIG_LENGTE 4

class Voertuig {
private:
    Voertuig* _initCheck;
public:
    bool properlyInitialized() const;
private:
    std::string baanNaam;
    int positie;
    float snelheid;
    float versnelling;
    float snelheid_max; // Dit is niet constant omdat dit wordt herberekend bij het vertragen

public:
    /*
     * REQUIRE(positie >= 0, "positie mag niet negatief zijn");
     * REQUIRE(snelheid >= 0, "snelheid mag niet negatief zijn");
     * REQUIRE(!baanNaam.empty(), "baanNaam mag niet leeg zijn");
     */
    Voertuig(const std::string &baanNaam, int positie);

    /*
     * REQUIRE(properlyInitialized(), "class not properly initialized");
     */
    const std::string& getBaanNaam() const {
        REQUIRE(properlyInitialized(), "class not properly initialized");
        return baanNaam;
    }

    /*
     * REQUIRE(properlyInitialized(), "class not properly initialized");
     */
    int getPositie() const {
        REQUIRE(properlyInitialized(), "class not properly initialized");
        return positie;
    }

    /*
     * REQUIRE(properlyInitialized(), "class not properly initialized");
     */
    float getSnelheid() const {
        REQUIRE(properlyInitialized(), "class not properly initialized");
        return snelheid;
    }

    /*
     * REQUIRE(properlyInitialized(), "class not properly initialized");
     */
    float getVersnelling() const {
        REQUIRE(properlyInitialized(), "class not properly initialized");
        return versnelling;
    }

    /*
     *  REQUIRE(properlyInitialized(), "class not properly initialized");
     *  REQUIRE(deltaTime_s >= 0, "deltaTime_s mag niet negatief zijn");
     */
    void update(float deltaTime_s, const Verkeerslicht* licht, const Voertuig* voorligger);
};

/*
* REQUIRE(tuig.properlyInitialized(), "class not properly initialized");
*/
std::ostream& operator<<(std::ostream& os, const Voertuig& tuig);


#endif //PROJECT_PSE_VOERTUIG_H
