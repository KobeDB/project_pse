//
// Created by kobedb on 17.03.22.
//

#ifndef PROJECT_PSE_VERKEERSSIMULATIE_H
#define PROJECT_PSE_VERKEERSSIMULATIE_H

#include <map>
#include <vector>
#include <iostream>

#include "Baan.h"
#include "Verkeerslicht.h"
#include "voertuigen/Voertuig.h"

#include "VerkeerssituatieReader.h"

#include "Voertuig_generator.h"

class Verkeerssimulatie {
private:
    std::map<std::string, Baan> banen; // Hiermee kunnen we aan de Baan objecten met hun namen als key
    std::vector<Voertuig_generator> generatoren;
public:
    Verkeerssimulatie(const std::vector<BaanInfo>& banen,
                      const std::vector<VerkeerslichtInfo>& lichten,
                      const std::vector<VoertuigInfo>& voertuigen,
                      const std::vector<VoertuiggeneratorInfo>& pGeneratoren,
                      const std::vector<BushalteInfo>& pBushaltes);

    void update(float deltaTime_s);
    bool done() const;

    void teken(std::ostream& os);
    friend std::ostream& operator<<(std::ostream& os, const Verkeerssimulatie& sim);
};


#endif //PROJECT_PSE_VERKEERSSIMULATIE_H
