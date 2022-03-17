//
// Created by kobedb on 17.03.22.
//

#ifndef PROJECT_PSE_VERKEERSLICHT_H
#define PROJECT_PSE_VERKEERSLICHT_H

#include <iostream>

class Verkeerslicht {
private:
    std::string baanNaam;
    int positie;
    int cyclus;
public:
    Verkeerslicht(const std::string& baan, int positie, int cyclus) : baanNaam(baan), positie(positie), cyclus(cyclus) {}

    const std::string& getBaanNaam() const {return baanNaam;}
    int getPositie() const {return positie;}
};


#endif //PROJECT_PSE_VERKEERSLICHT_H
