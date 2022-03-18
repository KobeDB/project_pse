//
// Created by kobedb on 17.03.22.
//

#include "Baan.h"

std::ostream& operator<<(std::ostream& os, const Baan& baan)
{
    os << "BAAN: \n";
    os << "\t naam: " << baan.getNaam() << "\n";
    os << "\t lengte: " << baan.getLengte();
    return os;
}

void Baan::addVerkeerslicht(Verkeerslicht &licht)
{
    // De lichten zijn gesorteerd op positie, van klein naar groot
    for(int i = 0; i < lichten.size(); i++) {
        if(lichten[i]->getPositie() > licht.getPositie()) {
            std::vector<Verkeerslicht*>::iterator it = lichten.begin() + i;
            lichten.insert(it, &licht);
            return;
        }
    }
    lichten.push_back(&licht);
}

const Verkeerslicht *Baan::getVolgendeLicht(int pos) const {
    for(int i = 0; i < lichten.size(); i++) {
        Verkeerslicht* licht = lichten[i];
        if(pos < licht->getPositie()) // We nemen meteen dit licht omdat onze lichten volgens afstand gesorteerd zijn
            return licht;
    }
    return NULL;
}
