//
// Created by kobedb on 17.03.22.
//

#include "Verkeerslicht.h"

#include <string>
#include <iostream>
#include "test_utils/DesignByContract.h"

using namespace std;

Verkeerslicht::Verkeerslicht(const std::string& baan, int positie, int cyclus): baanNaam(baan), positie(positie), cyclus(cyclus), timer_s(0), b_isRood(false)
{
    REQUIRE(positie >= 0, "positie mag niet negatief zijn");
    REQUIRE(cyclus > 0, "cyclus mag niet 0 of negatief zijn");
    REQUIRE(timer_s == 0, "timer niet geinitialiseerd op 0");
    REQUIRE(!baan.empty(), "baanNaam mag niet leeg zijn");
}

void Verkeerslicht::update(float deltaTime_s)
{
    float old_timer = timer_s;
    bool old_isRood = b_isRood;
    REQUIRE(deltaTime_s >= 0, "deltaTime_S mag niet negatief zijn");

    timer_s += deltaTime_s;
    if(timer_s >= (float)cyclus) {
        timer_s = (int) (timer_s + 0.5f) % cyclus;
        b_isRood = !b_isRood;
    }
//    string kleur = b_isRood? "rood" : "groen";
//    cout << "Licht: " << kleur << "\n"; // Tijdelijke debug print

    ENSURE((old_timer + deltaTime_s < (float)cyclus)?
                b_isRood == old_isRood
                :
                b_isRood == !old_isRood,
                "Verkeerslicht is niet correct van kleur veranderd!");
    ENSURE((old_timer + deltaTime_s < (float)cyclus)? timer_s == old_timer + deltaTime_s : timer_s == ((int) (old_timer + deltaTime_s + 0.5f)) % cyclus, "timer_s niet correct geupdatet" );
}
