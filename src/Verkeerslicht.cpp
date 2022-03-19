//
// Created by kobedb on 17.03.22.
//

#include "Verkeerslicht.h"

#include <string>
#include <iostream>

using namespace std;

void Verkeerslicht::update(float deltaTime_s)
{
    timer_s += deltaTime_s;
    if(timer_s >= (float)cyclus) {
        timer_s = (int) (timer_s + deltaTime_s) % cyclus;
        isRood = !isRood;
    }
    string kleur = isRood? "rood" : "groen";
    cout << "Licht: " << kleur << "\n"; // Tijdelijke debug print
}
