//
// Created by kobedb on 15.04.22.
//

#ifndef PROJECT_PSE_AUTO_H
#define PROJECT_PSE_AUTO_H


#include "Voertuig.h"

class Auto : public Voertuig {
public:
    Auto(const std::string &baanNaam, int positie) : Voertuig(baanNaam, positie) {}
    void update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger, Bushalte* bushalte);
    std::string getType() const {return "auto";} // overridden van de Base class
};


#endif //PROJECT_PSE_AUTO_H
