//
// Created by kobedb on 16.04.22.
//

#ifndef PROJECT_PSE_ZIEKENWAGEN_H
#define PROJECT_PSE_ZIEKENWAGEN_H

#include "../Prioriteitsvoertuig.h"

class Ziekenwagen : public Prioriteitsvoertuig{
public:
    //TODO: deze constantes aanpassen
    virtual float get_V_MAX() const { return 15.5f; }
    virtual float get_VERTRAAGFACTOR() const { return 0.4f; }
    virtual float get_REMFACTOR_MAX() const {return 4.47f;}
    virtual float get_VERSNELLING_MAX() const {return 1.44f;}
    virtual int get_VERTRAAGAFSTAND() const {return 50;}
    virtual int get_STOPAFSTAND() const {return 15;}
    virtual int get_MINIMALE_VOLGAFSTAND() const {return 8;}
    virtual int get_VOERTUIG_LENGTE() const {return 8;}

    Ziekenwagen(const std::string& baanNaam, int positie) : Prioriteitsvoertuig(baanNaam, positie) {}

    void update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger);

    std::string getType() const {return "ziekenwagen";} // overridden van de Base class

};


#endif //PROJECT_PSE_ZIEKENWAGEN_H
