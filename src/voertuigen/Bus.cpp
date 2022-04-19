//
// Created by kobedb on 16.04.22.
//

#include "Bus.h"

void Bus::update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger) {
    //TODO: Bus heeft ander gedrag dan auto. Hoe komt dit??
    Voertuig::update(deltaTime_s, licht, voorligger);
}
