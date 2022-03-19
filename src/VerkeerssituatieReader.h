//
// Created by kobedb on 19.03.22.
//

#ifndef PROJECT_PSE_VERKEERSSITUATIEREADER_H
#define PROJECT_PSE_VERKEERSSITUATIEREADER_H

#include <iostream>
#include <string>
#include <vector>

#include "Baan.h"
#include "Verkeerslicht.h"
#include "Voertuig.h"

class VerkeerssituatieReader {
    std::vector<Baan> banen;
    std::vector<Verkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
public:
    VerkeerssituatieReader(std::string situatieFile, std::ostream& errstr);

private:
    void read(std::string situatieFile, std::ostream &errstr);
    void checkConsistency(std::ostream& errstr);

public:
    const std::vector<Baan>& getBanen() {return banen;}
    const std::vector<Verkeerslicht>& getVerkeerslichten() {return verkeerslichten;}
    const std::vector<Voertuig>& getVoertuigen() {return voertuigen;}
};


#endif //PROJECT_PSE_VERKEERSSITUATIEREADER_H
