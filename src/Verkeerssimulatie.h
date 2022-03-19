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
#include "Voertuig.h"

class Verkeerssimulatie {
private:

    std::map<std::string, Baan> banen; // Hiermee kunnen we aan de Baan objecten met hun namen als key
    std::vector<Verkeerslicht> verkeerslichten;

    std::vector<Voertuig> voertuigen;
public:
    Verkeerssimulatie(const std::vector<Baan>& banen, const std::vector<Verkeerslicht>& lichten, const std::vector<Voertuig>& voertuigen);
    void addVerkeerslicht(const Verkeerslicht& licht);
    void addBaan(const Baan& baan);

    void update(float deltaTime_s);
    bool done() const;

    friend std::ostream& operator<<(std::ostream& os, const Verkeerssimulatie& sim);
};

void readVerkeerssituatieFromXml(const std::string& xmlFile, std::vector<Baan>& banen, std::vector<Verkeerslicht>& verkeerslichten, std::vector<Voertuig>& voertuigen);



#endif //PROJECT_PSE_VERKEERSSIMULATIE_H
