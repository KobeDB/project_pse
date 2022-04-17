//
// Created by kobedb on 16.04.22.
//

#include "Bus.h"

void Bus::update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger) {
    Voertuig::update(deltaTime_s, licht, voorligger);
}
