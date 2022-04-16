//
// Created by kobedb on 16.04.22.
//

#ifndef PROJECT_PSE_BUS_H
#define PROJECT_PSE_BUS_H

#include "Voertuig.h"

class Bus : public Voertuig {
public:
    //TODO: deze constantes aanpassen
    virtual float get_V_MAX() const { return 16.6f; }
    virtual float get_VERTRAAGFACTOR() const { return 0.4f; }
    virtual float get_REMFACTOR_MAX() const {return 4.61f;}
    virtual float get_VERSNELLING_MAX() const {return 1.44f;}
    virtual int get_VERTRAAGAFSTAND() const {return 50;}
    virtual int get_STOPAFSTAND() const {return 15;}
    virtual int get_MINIMALE_VOLGAFSTAND() const {return 4;}
    virtual int get_VOERTUIG_LENGTE() const {return 4;}

    Bus(const std::string& baanNaam, int positie) : Voertuig(baanNaam, positie) {}

    void update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger);

};


#endif //PROJECT_PSE_BUS_H
