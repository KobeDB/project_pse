//
// Created by kobedb on 17.03.22.
//

#include "Baan.h"
#include "Voertuig.h"

std::ostream& operator<<(std::ostream& os, const Baan& baan)
{
    for(unsigned i = 0; i < baan.voertuigen.size(); i++) {
        os << "\tVoertuig " << (i+1) << "\n";
        os << baan.voertuigen[i] << "\n";
    }
    return os;
}

void Baan::addVerkeerslicht(Verkeerslicht &licht)
{
    // De verkeerslichten zijn gesorteerd op positie, van klein naar groot
    for(unsigned i = 0; i < verkeerslichten.size(); i++) {
        if(verkeerslichten[i]->getPositie() > licht.getPositie()) {
            std::vector<Verkeerslicht*>::iterator it = verkeerslichten.begin() + i;
            verkeerslichten.insert(it, &licht);
            return;
        }
    }
    verkeerslichten.push_back(&licht);
}



const Verkeerslicht *Baan::getVolgendeLicht(int pos) const {
    for(unsigned i = 0; i < verkeerslichten.size(); i++) {
        Verkeerslicht* licht = verkeerslichten[i];
        if(pos < licht->getPositie()) // We nemen meteen dit licht omdat onze verkeerslichten volgens afstand gesorteerd zijn
            return licht;
    }
    return NULL;
}


void Baan::addVoertuig(const Voertuig &voertuig)
{
    // De verkeerslichten zijn gesorteerd op positie, van klein naar groot
    for(unsigned i = 0; i < voertuigen.size(); i++) {
        if(voertuigen[i].getPositie() > voertuig.getPositie()) {
            std::vector<Voertuig>::iterator it = voertuigen.begin() + i;
            voertuigen.insert(it, voertuig);
            return;
        }
    }
    voertuigen.push_back(voertuig);
}

const Voertuig* Baan::getVoorligger(int pos) const {
    for(unsigned i = 0; i < voertuigen.size(); i++) {
        const Voertuig& voertuig = voertuigen[i];
        if(pos < voertuig.getPositie()) // We nemen meteen dit voertuig omdat onze verkeerslichten volgens afstand gesorteerd zijn
            return &voertuig;
    }
    return NULL;
}

void Baan::update(float deltaTime_s)
{
    for(unsigned i = 0; i < verkeerslichten.size(); i++) {
        Verkeerslicht* licht = verkeerslichten[i];
        licht->update(deltaTime_s);
    }

    // We lopen de lijst van achter naar voren af, omdat we de lijst ondertussen bewerken
    for(int i = voertuigen.size()-1; i >= 0; i--) {
        Voertuig& tuig = voertuigen[i];
        tuig.update(deltaTime_s, *this);
        if(tuig.getPositie() > getLengte()) {
            voertuigen.erase(voertuigen.begin() + i);
        }
    }
}

bool Baan::done() const {
    return voertuigen.empty();
}

