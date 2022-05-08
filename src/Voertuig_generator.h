//
// Created by emiel on 4/17/2022.
//

#ifndef PROJECT_PSE_VOERTUIG_GENERATOR_H
#define PROJECT_PSE_VOERTUIG_GENERATOR_H

#include <iostream>
#include "Baan.h"

class Voertuig_generator {
private:
    std::string baanNaam;
    std::string type;
    int cyclus;
    float timer_s;

public:
    Voertuig_generator(const std::string &baan, const std::string &type, int cyclus);

    const std::string& getBaan() const;

    const std::string &getType() const;

    int getCyclus() const;

    void update(float deltaTime_s, Baan* baan);
};


#endif //PROJECT_PSE_VOERTUIG_GENERATOR_H
