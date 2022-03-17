//
// Created by kobedb on 17.03.22.
//

#include "Voertuig.h"

void Voertuig::update(float deltaTime_s, const Baan& baan)
{
    snelheid = snelheid + deltaTime_s * versnelling;
    positie += (int)(snelheid * deltaTime_s);
}

std::ostream& operator<<(std::ostream& os, const Voertuig& tuig)
{
os << "\t\t-> baan: " << tuig.getBaanNaam() << "\n";
os << "\t\t-> positie: " << tuig.getPositie() << "\n";
os << "\t\t-> snelheid: " << tuig.getSnelheid();

return os;
}