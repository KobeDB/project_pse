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
    const int cyclus;
    float timer_s;
    bool isRood;

public:
    Verkeerslicht(const std::string& baan, int positie, int cyclus)
        : baanNaam(baan), positie(positie), cyclus(cyclus), timer_s(0), isRood(false) {}

    const std::string& getBaanNaam() const {return baanNaam;}
    int getPositie() const {return positie;}
    bool getIsRood() const {return isRood;}

    void update(float deltaTime_s);
};


#endif //PROJECT_PSE_VERKEERSLICHT_H
