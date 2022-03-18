//
// Created by kobedb on 17.03.22.
//

#include "Vekeerssimulatie.h"

#include <algorithm>

void Verkeerssimulatie::addVerkeerslicht(const Verkeerslicht& licht)
{
    verkeerslichten.push_back(licht);
}

void Verkeerssimulatie::addBaan(const Baan &baan)
{
    banen[baan.getNaam()] = baan;
}

std::ostream &operator<<(std::ostream &os, const Verkeerssimulatie &sim)
{

//    for(int i = 0; i < sim.voertuigen.size(); i++) {
//        os << "\tVoertuig " << (i+1) << "\n";
//        os << "\t\t-> baan: " << sim.voertuigen[i].getBaanNaam() << "\n";
//        os << "\t\t-> positie: " << sim.voertuigen[i].getPositie() << "\n";
//        os << "\t\t-> snelheid: " << sim.voertuigen[i].getSnelheid() << "\n";
//    }

    for(int i = 0; i < sim.voertuigen.size(); i++) {
        os << "\tVoertuig " << (i+1) << "\n";
        os << sim.voertuigen[i] << "\n";
    }

    return os;
}

Verkeerssimulatie::Verkeerssimulatie(const std::vector<Baan> &pBanen, const std::vector<Verkeerslicht> &pLichten,
                                     const std::vector<Voertuig> &pVoertuigen)
                                     : banen(), verkeerslichten(pLichten), voertuigen(pVoertuigen)
                                     {
    for(int b = 0; b < pBanen.size(); b++) {
        const Baan& baan = pBanen[b];
        banen[baan.getNaam()] = baan;
        for(int l = 0; l < verkeerslichten.size(); l++) {
            Verkeerslicht& licht = verkeerslichten[l];
            if(licht.getBaanNaam() != baan.getNaam())
                continue;
            banen[baan.getNaam()].addVerkeerslicht(licht);
        }
    }
    std::cout << "";

}

void Verkeerssimulatie::update(float deltaTime_s)
{
    for(int i = 0; i < verkeerslichten.size(); i++) {
        Verkeerslicht& licht = verkeerslichten[i];
        licht.update(deltaTime_s);
    }

    // We lopen de lijst van achter naar voren af, omdat we de lijst ondertussen bewerken
    for(int i = voertuigen.size()-1; i >= 0; i--) {
        Voertuig& tuig = voertuigen[i];
        const Baan& baanVanTuig = banen[tuig.getBaanNaam()];
        tuig.update(deltaTime_s, baanVanTuig);
        if(tuig.getPositie() > baanVanTuig.getLengte()) {
            voertuigen.erase(voertuigen.begin() + i);
        }
    }

}
