//
// Created by kobedb on 11.04.22.
//

#ifndef PROJECT_PSE_PRIORITEITSVOERTUIG_H
#define PROJECT_PSE_PRIORITEITSVOERTUIG_H

#include "voertuigen/Voertuig.h"

class Prioriteitsvoertuig : public Voertuig {
public:
    Prioriteitsvoertuig(const std::string &baanNaam, int positie) : Voertuig(baanNaam, positie) {}
    virtual void update(float deltaTime_s, const Verkeerslicht* licht, const Voertuig* voorligger);

    virtual ~Prioriteitsvoertuig() {}
};

#endif //PROJECT_PSE_PRIORITEITSVOERTUIG_H
