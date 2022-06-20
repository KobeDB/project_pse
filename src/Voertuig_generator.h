//
// Created by emiel on 4/17/2022.
//

#ifndef PROJECT_PSE_VOERTUIG_GENERATOR_H
#define PROJECT_PSE_VOERTUIG_GENERATOR_H

#include <iostream>
#include "Baan.h"

class Voertuig_generator {
private:
    std::string baanNaam;// const
    std::string type; // const
    int cyclus; // const
    float timer_s;

public:
    // REQUIRE(cyclus > 0, "cyclus mag niet 0 of negatief zijn");
    // REQUIRE(!baan.empty(), "baanNaam mag niet leeg zijn");
    // REQUIRE(!type.empty(), "type mag niet leeg zijn");
    // ENSURE(getCyclus() == cyclus, "cyclus is goed geinitialiseerd");
    // ENSURE(getTimer_s() == 0, "getTimer_s() staat op 0");
    Voertuig_generator(const std::string &baan, const std::string &type, int cyclus);

    const std::string& getBaan() const;

    const std::string &getType() const;

    int getCyclus() const;
    float getTimer_s() const;

    // ENSURE(((old(getTimer_s) + deltaTime_s < (float)getCyclus())?
    //                    (old(baan).getVoertuigenAmt() == baan->getVoertuigenAmt())
    //                    :
    //                    (old(baan).getAchtersteVoertuig()?
    //                        (old(achterste)->getPositie() >= old(achterste)->get_VOERTUIG_LENGTE()*2 && old(voertuigen_amt) + 1 == baan->getVoertuigenAmt()) ||
    //                        (old(achterste)->getPositie()  < old(achterste)->get_VOERTUIG_LENGTE()*2 && old(voertuigen_amt) == baan->getVoertuigenAmt())
    //                        :
    //                        (baan->getVoertuigenAmt() == 1))),
    //           "Verkeerd aantal voertuigen na afloop Voertuiggenerator::update()!");
    // ENSURE((old(getTimer_s) + deltaTime_s < (float)getCyclus())? getTimer_s() == old(getTimer_s()) + deltaTime_s : getTimer_s() == ((int) (old(getTimer_s()) + deltaTime_s + 0.5f)) % getCyclus(), "getTimer_s() niet correct geupdatet" );
    void update(float deltaTime_s, Baan* baan);
};


#endif //PROJECT_PSE_VOERTUIG_GENERATOR_H
