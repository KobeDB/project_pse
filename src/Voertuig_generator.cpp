//
// Created by emiel on 4/17/2022.
//

#include "Voertuig_generator.h"
#include "Verkeerssimulatie.h"
#include "VoertuigFactory.h"

#include <string>
#include <iostream>
#include "test_utils/DesignByContract.h"

using namespace std;

Voertuig_generator::Voertuig_generator(const std::string &baan, const std::string &type, int cyclus) : baan(baan),
                                                                                                       type(type),
                                                                                                       cyclus(cyclus) {
}


 const std::string& Voertuig_generator::getBaan() const {
    return baan;
}

const std::string &Voertuig_generator::getType() const {
    return type;
}

int Voertuig_generator::getCyclus() const {
    return cyclus;
}

void Voertuig_generator::update(float deltaTime_s, Baan* nugget) {
    REQUIRE(deltaTime_s >= 0, "deltaTime_S mag niet negatief zijn");
    REQUIRE(nugget != NULL, "nugget mag niet null zijn");

    timer_s += deltaTime_s;
    if (timer_s >= (float) cyclus) {
        timer_s = (int) (timer_s + deltaTime_s + 0.5f) % cyclus;
        const Voertuig* chicken = nugget->getVoorligger(0);
        int cPos = chicken->getPositie();
        if(cPos >= (chicken->get_VOERTUIG_LENGTE() * 2)) {
            Voertuig* V = VoertuigFactory::getInstance()->create(this->type, this->baan, 0);
            nugget->addVoertuig(V);
        }
    }
}