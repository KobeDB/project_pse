//
// Created by kobedb on 17.03.22.
//

#include "Voertuig.h"
#include <cmath>

using namespace std;

void Voertuig::update(float deltaTime_s, const Baan& baan)
{
    const Verkeerslicht* licht = baan.getVolgendeLicht(positie);

    float nieuweSnelheid = snelheid + deltaTime_s * versnelling;
    if(nieuweSnelheid < 0 ) {
        positie = (int)((float)positie - pow(snelheid, 2) / (2 * versnelling));
        snelheid = 0;
    }
    else {
        snelheid = nieuweSnelheid;
        positie += (int)(snelheid * deltaTime_s);
    }

    float delta = 0;
    versnelling = VERSNELLING_MAX * (1 - pow((snelheid / snelheid_max), 4) - pow(delta, 2));

    if(licht && licht->getIsRood()) {
        if((licht->getPositie() - positie) < STOPAFSTAND) {
            versnelling = -REMFACTOR_MAX * snelheid / snelheid_max;
        }
        else if((licht->getPositie() - positie) < VERTRAAGAFSTAND) {
            snelheid_max = VERTRAAGFACTOR * V_MAX;
        }
    }
    else {
        snelheid_max = V_MAX;
    }



}



std::ostream& operator<<(std::ostream& os, const Voertuig& tuig)
{
os << "\t\t-> baan: " << tuig.getBaanNaam() << "\n";
os << "\t\t-> positie: " << tuig.getPositie() << "\n";
os << "\t\t-> snelheid: " << tuig.getSnelheid();

return os;
}