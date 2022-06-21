//
// Created by kobedb on 16.04.22.
//

#ifndef PROJECT_PSE_POLITIECOMBI_H
#define PROJECT_PSE_POLITIECOMBI_H

#include "../Prioriteitsvoertuig.h"

class Politiecombi : public Prioriteitsvoertuig {

public:
    virtual float get_V_MAX() const { return 17.2f; }
    virtual float get_VERTRAAGFACTOR() const { return 0.4f; }
    virtual float get_REMFACTOR_MAX() const {return 4.92f;}
    virtual float get_VERSNELLING_MAX() const {return 1.55f;}
    virtual int get_VERTRAAGAFSTAND() const {return 50;}
    virtual int get_STOPAFSTAND() const {return 15;}
    virtual int get_MINIMALE_VOLGAFSTAND() const {return 6;}
    virtual int get_VOERTUIG_LENGTE() const {return 6;}

    Politiecombi(const std::string& baanNaam, int positie) : Prioriteitsvoertuig(baanNaam, positie) {}

    void update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger, Bushalte* bushalte);

    std::string getType() const {return "politiecombi";} // overridden van de Base class
};


#endif //PROJECT_PSE_POLITIECOMBI_H
