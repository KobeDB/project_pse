//
// Created by kobedb on 16.04.22.
//

#include "Brandweerwagen.h"

void Brandweerwagen::update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger, Bushalte* bushalte)
{
    Prioriteitsvoertuig::update(deltaTime_s, licht, voorligger, bushalte);
}
