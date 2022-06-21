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
    Baan(); // Dit bestaat enkel en alleen om banen te kunnen opslaan in de STL containers

    // REQUIRE(!naam.empty(), "baannaam mag niet leeg zijn");
    // REQUIRE(lengte > 0, "lengte moet groter zijn dan 0");
    // ENSURE(getLengte() == lengte, "lengte is goed geinitialiseerd");
    // ENSURE(getNaam() == naam, "naam is goed geinitialiseerd");
    Baan(const std::string& naam, int lengte);

    Baan(const Baan& other);

    // Baan destructor delete elk voertuig
    ~Baan();

    // REQUIRE(deltaTime_s >= 0, "deltaTime_s is een positief getal");
    void update(float deltaTime_s);

    bool done() const;

    const std::string& getNaam() const {return naam;}
    int getLengte() const {return lengte;}

    // REQUIRE(pos >= 0, "pos mag niet negatief zijn");
    // ENSURE(returnval == NULL || pos < returnval->getPositie(), "POST: returnval is geen voorligger")
    const Verkeerslicht* getVolgendeLicht(int pos) const;

    // REQUIRE(pos >= 0, "pos mag niet negatief zijn");
    // ENSURE(returnval == NULL || pos < returnval->getPositie(), "POST: returnval is geen voorligger")
    Bushalte* getVolgendeBushalte(int pos);

    /*
     * REQUIRE(pos >= 0, "pos mag niet negatief zijn");
     * ENSURE(returnval == NULL || pos < returnval->getPositie(), "POST: returnval is geen voorligger")
     */
    const Voertuig* getVoorligger(int pos) const;

    const Voertuig* getAchtersteVoertuig() const;

    int getVoertuigenAmt() const { return voertuigen.size(); }

    void addVerkeerslicht(const Verkeerslicht& licht);

    //REQUIRE(voertuig != null, "voertuig mag niet null zijn")
    void addVoertuig(Voertuig* voertuig);
    void addBushalte(Bushalte bushalte);

    /// functie om een Baan mooi af te printen
    friend std::ostream& operator<<(std::ostream& os, const Baan& baan);

    void teken(std::ostream& os) const;
};






#endif //PROJECT_PSE_BAAN_H
