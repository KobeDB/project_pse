//
// Created by kobedb on 16.04.22.
//

#include "Politiecombi.h"

void Politiecombi::update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger) {
    Prioriteitsvoertuig::update(deltaTime_s, licht, voorligger);
}
