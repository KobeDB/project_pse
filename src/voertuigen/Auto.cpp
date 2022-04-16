//
// Created by kobedb on 15.04.22.
//

#include "Auto.h"

void Auto::update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger) {
    Voertuig::update(deltaTime_s, licht, voorligger);
}
