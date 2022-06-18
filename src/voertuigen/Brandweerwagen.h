//
// Created by kobedb on 16.04.22.
//

#ifndef PROJECT_PSE_BRANDWEERWAGEN_H
#define PROJECT_PSE_BRANDWEERWAGEN_H

#include "../Prioriteitsvoertuig.h"

class Brandweerwagen : public Prioriteitsvoertuig {
public:
    //TODO: deze constantes aanpassen
    virtual float get_V_MAX() const { return 14.6f; }
    virtual float get_VERTRAAGFACTOR() const { return 0.4f; }
    virtual float get_REMFACTOR_MAX() const {return 4.56f;}
    virtual float get_VERSNELLING_MAX() const {return 1.33f;}
    virtual int get_VERTRAAGAFSTAND() const {return 50;}
    virtual int get_STOPAFSTAND() const {return 15;}
    virtual int get_MINIMALE_VOLGAFSTAND() const {return 10;}
    virtual int get_VOERTUIG_LENGTE() const {return 10;}
public:
    Brandweerwagen(const std::string& baanNaam, int positie) : Prioriteitsvoertuig(baanNaam, positie) {}

    void update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger, Bushalte* bushalte);

    std::string getType() const {return "brandweerwagen";} // overridden van de Base class

};


#endif //PROJECT_PSE_BRANDWEERWAGEN_H
