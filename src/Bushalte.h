//
// Created by kobedb on 18.05.22.
//

#ifndef PROJECT_PSE_BUSHALTE_H
#define PROJECT_PSE_BUSHALTE_H

#include <iostream>

class Bushalte {
    int positie;
    int wachttijd;

public:
    void* toegekendeBus;

public:
    Bushalte(int positie, int wachttijd) : positie(positie), wachttijd(wachttijd), toegekendeBus(NULL) {}
    int getPositie() const {return positie;}
    int getWachttijd() const {return wachttijd;}
};


#endif //PROJECT_PSE_BUSHALTE_H
