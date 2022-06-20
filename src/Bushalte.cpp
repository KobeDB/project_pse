//
// Created by kobedb on 18.05.22.
//

#include "Bushalte.h"

#include "test_utils/DesignByContract.h"

Bushalte::Bushalte(int positie, int wachttijd) : positie(positie), wachttijd(wachttijd), toegekendeBus(NULL)
{
    REQUIRE(positie >= 0, "Positie moet positief zijn");
    REQUIRE(wachttijd > 0, "wachttijd moet strikt groter zijn dan 0");
    ENSURE(this->getPositie() == positie, "positie is correct ingesteld");
    ENSURE(this->getWachttijd() == wachttijd, "wachttijd is correct ingesteld");
}