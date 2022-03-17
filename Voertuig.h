//
// Created by kobedb on 17.03.22.
//

#ifndef PROJECT_PSE_VOERTUIG_H
#define PROJECT_PSE_VOERTUIG_H

#include <string>

class Voertuig {
private:
    std::string baanNaam;
    int positie;
    int snelheid;
public:
    Voertuig(const std::string& baanNaam, int positie) :  baanNaam(baanNaam), positie(positie), snelheid(0) {}

    const std::string& getBaanNaam() const {return baanNaam;}
    int getPositie() const {return positie;}
    int getSnelheid() const {return snelheid;}

};


#endif //PROJECT_PSE_VOERTUIG_H
