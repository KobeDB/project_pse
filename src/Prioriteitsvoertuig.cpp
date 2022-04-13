//
// Created by kobedb on 11.04.22.
//

#include "Prioriteitsvoertuig.h"


void Prioriteitsvoertuig::update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger) {

    updatePositieEnSnelheid(deltaTime_s);

    updateVersnelling(voorligger);

}
