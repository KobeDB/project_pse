//
// Created by kobedb on 16.04.22.
//

#include "Bus.h"

#include <cmath>

void Bus::update(float deltaTime_s, const Verkeerslicht *licht, const Voertuig *voorligger, Bushalte* bushalte) {

    if(resterendeWachttijd > 0) {
        resterendeWachttijd -= deltaTime_s;
        if(resterendeWachttijd <= 0) {
            if(!bushalte) std::cerr << "Wachtende bus heeft geen bushalte! Los uw bugs op, idioot!!";
            bushalte->toegekendeBus = NULL;
            prevBushalte = bushalte; // Onthouden welke bushalte we net verlaten zijn, zodat we de volgende update niet terug zouden stoppen
        }
        return;
    }

    if(!bushalte || bushalte == prevBushalte) {
        // Geen bushalte => gewoon volgen
        Voertuig::update(deltaTime_s, licht, voorligger, bushalte);
        return;
    }

    // Deze bus nadert wel een bushalte

    if(bushalte->toegekendeBus != this && bushalte->toegekendeBus != NULL) {
        // De bus is niet de eerste bus voor de halte => gewoon volgen
        Voertuig::update(deltaTime_s, licht, voorligger, bushalte);
        return;
    }

    // De bus is wel de eerste bus voor de halte => desnoods vertragen of stoppen
    bushalte->toegekendeBus = this;
    if(abs(bushalte->getPositie()-this->getPositie()) < get_VERTRAAGAFSTAND()) {
        updatePositieEnSnelheid(deltaTime_s);
        updateVersnelling(NULL); // negeer de voorligger => NULL meegeven
        if(abs(bushalte->getPositie()-this->getPositie()) < get_STOPAFSTAND()) {
            // laat voertuig stoppen
            stop();
            if(getSnelheid() < 0.3f) {
                snelheid = 0.0f;
                resterendeWachttijd = bushalte->getWachttijd();
            }
        }
        else {
            // pas de vertraagfactor toe
            vertraag();
        }
    }
    else {
        // De bus hoeft niet te vertragen of te stoppen => gewoon volgen
        Voertuig::update(deltaTime_s, licht, voorligger, bushalte);
        return;
    }
}
