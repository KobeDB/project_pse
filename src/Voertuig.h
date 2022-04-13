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

// -Niet meer nodig- Walgelijke macros omdat c++98 (alleszins mijn compiler) geen const members wil initializen :(
//#define V_MAX 16.6f
//#define VERTRAAGFACTOR 0.4f
//#define REMFACTOR_MAX 4.61f
//#define VERSNELLING_MAX 1.44f
//#define VERTRAAGAFSTAND 50
//#define STOPAFSTAND 15
//#define MINIMALE_VOLGAFSTAND 4
//#define VOERTUIG_LENGTE 4

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
    virtual float get_V_MAX() const { return 16.6f; }
    virtual float get_VERTRAAGFACTOR() const { return 0.4f; }
    virtual float get_REMFACTOR_MAX() const {return 4.61f;}
    virtual float get_VERSNELLING_MAX() const {return 1.44f;}
    virtual int get_VERTRAAGAFSTAND() const {return 50;}
    virtual int get_STOPAFSTAND() const {return 15;}
    virtual int get_MINIMALE_VOLGAFSTAND() const {return 4;}
    virtual int get_VOERTUIG_LENGTE() const {return 4;}

public:
    /*
     * REQUIRE(positie >= 0, "positie mag niet negatief zijn");
     * REQUIRE(snelheid >= 0, "snelheid mag niet negatief zijn");
     * REQUIRE(!baanNaam.empty(), "baanNaam mag niet leeg zijn");
     */
    Voertuig(const std::string &baanNaam, int positie);

    // Copy constructor nodig om initCheck op het JUISTE adres te zetten van dit NIEUWE object
    Voertuig(const Voertuig& other)
        : baanNaam(other.baanNaam), positie(other.positie), snelheid(other.snelheid), versnelling(other.versnelling), snelheid_max(other.snelheid_max) {
        _initCheck = this;
    }

    // destructor virtual maken zodat de juiste destructor van de derived classes opgeroepen wordt
    virtual ~Voertuig() { }

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
    virtual void update(float deltaTime_s, const Verkeerslicht* licht, const Voertuig* voorligger);

    void updatePositieEnSnelheid(float deltaTime_s);

    void updateVersnelling(const Voertuig *voorligger);

    void vertraag();

    void stop();

    void versnel();
};

/*
* REQUIRE(tuig.properlyInitialized(), "class not properly initialized");
*/
std::ostream& operator<<(std::ostream& os, const Voertuig& tuig);


#endif //PROJECT_PSE_VOERTUIG_H
