//
// Created by kobedb on 11.04.22.
//

#ifndef PROJECT_PSE_PRIORITEITSVOERTUIG_H
#define PROJECT_PSE_PRIORITEITSVOERTUIG_H

#include "voertuigen/Voertuig.h"

class Prioriteitsvoertuig : public Voertuig {
public:
    Prioriteitsvoertuig(const std::string &baanNaam, int positie) : Voertuig(baanNaam, positie) {}

    // REQUIRE(properlyInitialized(), "class not properly initialized");
    // REQUIRE(deltaTime_s >= 0, "deltaTime_s mag niet negatief zijn");
    // ENSURE(getSnelheid() >= 0, "Voertuig heeft negatieve snelheid!");
    // ENSURE(old(getPositie()) <= getPositie(), "Voertuig mag niet achteruit rijden!");
    virtual void update(float deltaTime_s, const Verkeerslicht* licht, const Voertuig* voorligger, Bushalte* bushalte);

    virtual ~Prioriteitsvoertuig() {}
};

#endif //PROJECT_PSE_PRIORITEITSVOERTUIG_H
