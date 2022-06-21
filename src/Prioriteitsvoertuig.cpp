//
// Created by kobedb on 11.04.22.
//

#include "Prioriteitsvoertuig.h"


void Prioriteitsvoertuig::update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger, Bushalte* bushalte) {
    REQUIRE(deltaTime_s >= 0, "deltaTime_s mag niet negatief zijn");

    float old_positie = (float)getPositie();

    updatePositieEnSnelheid(deltaTime_s);

    updateVersnelling(voorligger);

    ENSURE(getSnelheid() >= 0, "Voertuig heeft negatieve snelheid!");
    ENSURE(old_positie <= getPositie(), "Voertuig mag niet achteruit rijden!");
}
