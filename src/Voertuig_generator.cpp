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

Voertuig_generator::Voertuig_generator(const std::string &baan, const std::string &type, int cyclus) : baanNaam(baan),
                                                                                                       type(type),
                                                                                                       cyclus(cyclus) {
    REQUIRE(cyclus > 0, "cyclus mag niet 0 of negatief zijn");
    REQUIRE(!baan.empty(), "baanNaam mag niet leeg zijn");
    REQUIRE(!type.empty(), "type mag niet leeg zijn");
}


 const std::string& Voertuig_generator::getBaan() const {
    return baanNaam;
}

const std::string &Voertuig_generator::getType() const {
    return type;
}

int Voertuig_generator::getCyclus() const {
    return cyclus;
}

void Voertuig_generator::update(float deltaTime_s, Baan* baan) {
    // Variabelen voor de ENSURE
    float old_timer_s = timer_s;
    int old_voertuigen_amt = baan->getVoertuigenAmt();
    Baan old_baan = Baan(*baan);
    const Voertuig* old_achterste = old_baan.getAchtersteVoertuig();

    REQUIRE(deltaTime_s >= 0, "deltaTime_S mag niet negatief zijn");
    REQUIRE(baan != NULL, "baan mag niet null zijn");


    timer_s += deltaTime_s;
    if (timer_s >= (float) cyclus) {
        timer_s = (int) (timer_s + 0.5f) % cyclus;
        const Voertuig* achterste = baan->getAchtersteVoertuig();
        if(!achterste || achterste->getPositie() >= (achterste->get_VOERTUIG_LENGTE() * 2)) {
            Voertuig* V = VoertuigFactory::getInstance()->create(this->type, this->baanNaam, 0);
            baan->addVoertuig(V);
        }
    }

    ENSURE(((old_timer_s + deltaTime_s < (float)cyclus)?
                    (old_baan.getVoertuigenAmt() == baan->getVoertuigenAmt())
                    :
                    (old_baan.getAchtersteVoertuig()?
                        (old_achterste->getPositie() >= old_achterste->get_VOERTUIG_LENGTE()*2 && old_voertuigen_amt + 1 == baan->getVoertuigenAmt()) ||
                        (old_achterste->getPositie()  < old_achterste->get_VOERTUIG_LENGTE()*2 && old_voertuigen_amt == baan->getVoertuigenAmt())
                        :
                        (baan->getVoertuigenAmt() == 1))),
           "Verkeerd aantal voertuigen na afloop Voertuiggenerator::update()!");

    ENSURE((old_timer_s + deltaTime_s < (float)cyclus)? timer_s == old_timer_s + deltaTime_s : timer_s == ((int) (old_timer_s + deltaTime_s + 0.5f)) % cyclus, "timer_s niet correct geupdatet" );

}