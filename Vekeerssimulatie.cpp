//
// Created by kobedb on 17.03.22.
//

#include "Vekeerssimulatie.h"

void Verkeerssimulatie::addVerkeerslicht(const Verkeerslicht& licht)
{
    verkeerslichten.push_back(licht);
}

void Verkeerssimulatie::addBaan(const Baan &baan) {
    banen[baan.getNaam()] = baan;
}

std::ostream &operator<<(std::ostream &os, const Verkeerssimulatie &sim) {
    os << "SIMULATIE: \n";
    os << "\tTijd: " << "0" << "\n";

    for(int i = 0; i < sim.voertuigen.size(); i++) {
        os << "\tVoertuig " << (i+1) << "\n";
        os << "\t\t-> baan: " << sim.voertuigen[i].getBaanNaam() << "\n";
        os << "\t\t-> positie: " << sim.voertuigen[i].getPositie() << "\n";
        os << "\t\t-> snelheid: " << sim.voertuigen[i].getSnelheid() << "\n";
    }
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
