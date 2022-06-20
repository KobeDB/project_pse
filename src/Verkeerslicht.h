//
// Created by kobedb on 17.03.22.
//

#ifndef PROJECT_PSE_VERKEERSLICHT_H
#define PROJECT_PSE_VERKEERSLICHT_H

#include <iostream>

class Verkeerslicht {
private:
    std::string baanNaam; // const
    int positie; // const
    int cyclus; // const
    float timer_s;
    bool b_isRood;

public:
    // REQUIRE(positie >= 0, "positie mag niet negatief zijn");
    // REQUIRE(cyclus > 0, "cyclus mag niet 0 of negatief zijn");
    // REQUIRE(!baan.empty(), "baanNaam mag niet leeg zijn");
    // ENSURE(getTimer_s() == 0, "timer moet geinitialiseerd staan op 0");
    Verkeerslicht(const std::string& baan, int positie, int cyclus);

    const std::string& getBaanNaam() const {return baanNaam;}
    int getPositie() const {return positie;}
    bool isRood() const {return b_isRood;}

    int getCyclus() const {return cyclus;}
    float getTimer_s() const {return timer_s;}

    // REQUIRE(deltaTime_s >= 0, "deltaTime_S mag niet negatief zijn");
    // ENSURE((old(getTimer_s()) + deltaTime_s < (float)getCyclus())?
    //                isRood() == old(isRood())
    //                :
    //                isRood() == !old(isRood()),
    //                "Verkeerslicht is niet correct van kleur veranderd!");
    // ENSURE((old(getTimer_s) + deltaTime_s < (float)getCyclus())? getTimer_s() == old(getTimer_s()) + deltaTime_s : getTimer_s() == ((int) (old(getTimer_s()) + deltaTime_s + 0.5f)) % getCyclus(), "getTimer_s() niet correct geupdatet" );
    void update(float deltaTime_s);

};


#endif //PROJECT_PSE_VERKEERSLICHT_H
