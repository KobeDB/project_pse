//
// Created by kobedb on 17.03.22.
//

#include "Voertuig.h"
#include <cmath>
#include <sstream>

#include "../test_utils/DesignByContract.h"

#include "../Baan.h"

using namespace std;

Voertuig::Voertuig(const std::string &baanNaam, int positie): baanNaam(baanNaam), positie(positie), snelheid(0), versnelling(0), snelheid_max(get_V_MAX())
{
    REQUIRE(positie >= 0, "positie mag niet negatief zijn");
    REQUIRE(snelheid >= 0, "snelheid mag niet negatief zijn");
    REQUIRE(!baanNaam.empty(), "baanNaam mag niet leeg zijn");

    _initCheck = this;
    ENSURE(this->properlyInitialized(), "constructor must end in properly initialized state");
}

void Voertuig::update(float deltaTime_s, const Verkeerslicht* licht, const Voertuig* voorligger)
{
    float old_positie = positie;
    REQUIRE(properlyInitialized(), "class not properly initialized");
    REQUIRE(deltaTime_s >= 0, "deltaTime_s mag niet negatief zijn");

    // Als voorligger zich bevindt achter stopafstand voor het rode verkeerslicht, is hij geen voorligger meer
    if(licht && voorligger && licht->isRood() && (licht->getPositie() - get_STOPAFSTAND() / 2) < voorligger->getPositie()) {
        voorligger = NULL;
    }

    updatePositieEnSnelheid(deltaTime_s);

    updateVersnelling(voorligger);

    if(licht && licht->isRood()) {
        if(!voorligger) {
            if((licht->getPositie() - positie) < get_STOPAFSTAND()) {
                stop();
            }
            else if((licht->getPositie() - positie) < get_VERTRAAGAFSTAND()) {
                vertraag();
            }
            else {
                versnel();
            }
        }
    }

    ENSURE(snelheid >= 0, "Voertuig heeft negatieve snelheid!");
    ENSURE(old_positie <= positie, "Voertuig mag niet achteruit rijden!");
}

std::string to_string(float a)
{
    std::stringstream ss;
    ss << a;
    return ss.str();
}

void Voertuig::updatePositieEnSnelheid(float deltaTime_s)
{
    Voertuig old_this = *this;
    float old_positie = positie;
    REQUIRE(deltaTime_s >= 0, "deltaTime_s mag niet negatief zijn");

    float nieuweSnelheid = snelheid + deltaTime_s * versnelling;
    if(nieuweSnelheid < 0 ) {
        positie = ((float)positie - pow(snelheid, 2) / (2 * versnelling));
        snelheid = 0;
    }
    else {
        snelheid = nieuweSnelheid;
        positie += (snelheid * deltaTime_s);
    }

    // Foutmarge ingebouwd om de overshoot te tolereren
    ENSURE(snelheid <= get_V_MAX() + 2.0f, "snelheid over de limiet!");

    ENSURE(snelheid >= 0, "Voertuig heeft negatieve snelheid!");
    ENSURE(old_positie <= positie, "Voertuig mag niet achteruit rijden!");
    // Kijk na of er voor de rest niets veranderd is
    ENSURE(baanNaam == old_this.baanNaam, "");
    ENSURE(versnelling == old_this.versnelling, "");
    ENSURE(snelheid_max == old_this.snelheid_max, "");
}

void Voertuig::updateVersnelling(const Voertuig* voorligger)
{
    Voertuig old_this = *this;
    REQUIRE(properlyInitialized(), "class not properly initialized");

    float delta = 0;
    if(voorligger) {
        int dPositie = voorligger->getPositie() - positie - get_VOERTUIG_LENGTE();
        float dSnelheid = snelheid - voorligger->getSnelheid();
        delta = ((float)get_MINIMALE_VOLGAFSTAND() + std::max((float)0, snelheid + (snelheid * dSnelheid)/(2 * sqrt(get_VERSNELLING_MAX() * get_REMFACTOR_MAX())))) / (float)dPositie;
    }
    versnelling = get_VERSNELLING_MAX() * (1 - pow((snelheid / snelheid_max), 4) - pow(delta, 2));

    ENSURE(versnelling <= get_VERSNELLING_MAX(), "versnelling over de limiet!");

    // Kijk na of er voor de rest niets veranderd is
    ENSURE(baanNaam == old_this.baanNaam, "");
    ENSURE(positie == old_this.positie, "");
    ENSURE(snelheid == old_this.snelheid, "");
    ENSURE(snelheid_max == old_this.snelheid_max, "");
}

void Voertuig::stop()
{
    Voertuig old_this = *this;
    REQUIRE(properlyInitialized(), "class not properly initialized");

    versnelling = -get_REMFACTOR_MAX() * snelheid / snelheid_max;

    ENSURE(versnelling == -get_REMFACTOR_MAX() * old_this.snelheid / old_this.snelheid_max, "stop(): versnelling niet correct aangepast!");

    // Kijk na of er voor de rest niets veranderd is
    ENSURE(baanNaam == old_this.baanNaam, "");
    ENSURE(positie == old_this.positie, "");
    ENSURE(snelheid == old_this.snelheid, "");
    ENSURE(snelheid_max == old_this.snelheid_max, "");
}

void Voertuig::vertraag()
{
    Voertuig old_this = *this;
    REQUIRE(properlyInitialized(), "class not properly initialized");

    snelheid_max = get_VERTRAAGFACTOR() * get_V_MAX();

    ENSURE(snelheid_max == get_VERTRAAGFACTOR() * get_V_MAX(), "vertraag(): snelheid_max niet correct aangepast!");

    // Kijk na of er voor de rest niets veranderd is
    ENSURE(baanNaam == old_this.baanNaam, "");
    ENSURE(positie == old_this.positie, "");
    ENSURE(snelheid == old_this.snelheid, "");
    ENSURE(versnelling == old_this.versnelling, "");
}

void Voertuig::versnel()
{
    Voertuig old_this = *this;
    REQUIRE(properlyInitialized(), "class not properly initialized");

    snelheid_max = get_V_MAX();

    ENSURE(snelheid_max == get_V_MAX(), "versnel(): snelheid_max != get_V_max()");

    // Kijk na of er voor de rest niets veranderd is
    ENSURE(baanNaam == old_this.baanNaam, "");
    ENSURE(positie == old_this.positie, "");
    ENSURE(snelheid == old_this.snelheid, "");
    ENSURE(versnelling == old_this.versnelling, "");
}

bool Voertuig::properlyInitialized() const {
    return _initCheck == this; // Dit geeft dikke schijt als Voertuig in een of andere vector zit
    //return true;
}


std::ostream& operator<<(std::ostream& os, const Voertuig& tuig) {
    REQUIRE(tuig.properlyInitialized(), "class not properly initialized");

    os << "\t\t-> baan: " << tuig.getBaanNaam() << "\n";
    os << "\t\t-> type: " << tuig.getType() << "\n";
    os << "\t\t-> positie: " << tuig.getPositie() << "\n";
    os << "\t\t-> snelheid: " << tuig.getSnelheid();
    return os;
}