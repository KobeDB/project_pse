//
// Created by kobedb on 18.05.22.
//

#ifndef PROJECT_PSE_BUSHALTE_H
#define PROJECT_PSE_BUSHALTE_H

#include <iostream>

class Bushalte {
    int positie; // const
    int wachttijd; // const

public:
    void* toegekendeBus;

public:
    // REQUIRE(positie >= 0, "Positie moet positief zijn");
    // REQUIRE(wachttijd > 0, "wachttijd moet strikt groter zijn dan 0");
    // ENSURE(this->getPositie() == positie, "positie is correct ingesteld");
    // ENSURE(this->getWachttijd() == wachttijd, "wachttijd is correct ingesteld");
    Bushalte(int positie, int wachttijd);
    int getPositie() const {return positie;}
    int getWachttijd() const {return wachttijd;}
};


#endif //PROJECT_PSE_BUSHALTE_H
