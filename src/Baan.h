//
// Created by kobedb on 17.03.22.
//

#ifndef PROJECT_PSE_BAAN_H
#define PROJECT_PSE_BAAN_H

#include <iostream>
#include <string>
#include <vector>

#include "Verkeerslicht.h"

#include "Bushalte.h"

class Voertuig;

class Baan {
private:
    std::string naam;
    int lengte;
    std::vector<Verkeerslicht> verkeerslichten;
    std::vector<Voertuig*> voertuigen;
    std::vector<Bushalte> bushaltes;
public:
    Baan() : naam(), lengte() {}
    Baan(const std::string& naam, int lengte);

    Baan(const Baan& other);

    // Baan destructor delete elk voertuig
    ~Baan();

    void update(float deltaTime_s);

    bool done() const;

    const std::string& getNaam() const {return naam;}
    int getLengte() const {return lengte;}

    const Verkeerslicht* getVolgendeLicht(int pos) const;

    Bushalte* getVolgendeBushalte(int pos);

    /*
     * POST: returnt het voertuig dat net voor pos rijdt. als er geen voorligger is, returnt NULL
     * ENSURE(returnval == NULL || pos < returnval->getPositie(), "POST: returnval is geen voorligger")
     */
    const Voertuig* getVoorligger(int pos) const;
    const Voertuig* getAchtersteVoertuig() const;

    int getVoertuigenAmt() const { return voertuigen.size(); }

    void addVerkeerslicht(const Verkeerslicht& licht);
    void addVoertuig(Voertuig* voertuig);
    void addBushalte(Bushalte bushalte);

    /// functie om een Baan mooi af te printen
    friend std::ostream& operator<<(std::ostream& os, const Baan& baan);

    void teken(std::ostream& os) const;
};






#endif //PROJECT_PSE_BAAN_H
