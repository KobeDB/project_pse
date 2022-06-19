//
// Created by kobedb on 17.03.22.
//

#include "Baan.h"
#include "Voertuig_generator.h"
#include "voertuigen/Voertuig.h"
#include "VoertuigFactory.h"

Baan::Baan(const std::string& naam, int lengte) : naam(naam), lengte(lengte)
{
    REQUIRE(!naam.empty(), "baannaam mag niet leeg zijn");
    REQUIRE(lengte > 0, "lengte moet groter zijn dan 0");
}

Baan::~Baan() {

    for (std::vector<Voertuig*>::size_type i = 0; i < voertuigen.size(); i++) {
        delete voertuigen[i];
    }

}


std::ostream& operator<<(std::ostream& os, const Baan& baan)
{
    for(int i = baan.voertuigen.size()-1; i >= 0 ; i--) {
        os << "\tVoertuig " << (baan.voertuigen.size()-1-i) << "\n";
        os << *baan.voertuigen[i] << "\n";
    }
    return os;
}

void Baan::addVerkeerslicht(const Verkeerslicht &licht)
{
    // De verkeerslichten zijn gesorteerd op positie, van klein naar groot
    for(unsigned i = 0; i < verkeerslichten.size(); i++) {
        if(verkeerslichten[i].getPositie() > licht.getPositie()) {
            std::vector<Verkeerslicht>::iterator it = verkeerslichten.begin() + i;
            verkeerslichten.insert(it, licht);
            return;
        }
    }
    verkeerslichten.push_back(licht);
}



const Verkeerslicht *Baan::getVolgendeLicht(int pos) const {
    for(unsigned i = 0; i < verkeerslichten.size(); i++) {
        const Verkeerslicht& licht = verkeerslichten[i];
        if(pos < licht.getPositie()) // We nemen meteen dit licht omdat onze verkeerslichten volgens afstand gesorteerd zijn
            return &licht;
    }
    return NULL;
}


void Baan::addVoertuig(Voertuig* voertuig)
{
    REQUIRE(voertuig, "voertuig mag niet NULL zijn");

    // De verkeerslichten zijn gesorteerd op positie, van klein naar groot
    for(unsigned i = 0; i < voertuigen.size(); i++) {
        if(voertuigen[i]->getPositie() > voertuig->getPositie()) {
            std::vector<Voertuig*>::iterator it = voertuigen.begin() + i;
            voertuigen.insert(it, voertuig);
            return;
        }
    }
    voertuigen.push_back(voertuig);
}

void Baan::addBushalte(Bushalte bushalte)
{
    // De verkeerslichten zijn gesorteerd op positie, van klein naar groot
    for(unsigned i = 0; i < bushaltes.size(); i++) {
        if(bushaltes[i].getPositie() > bushalte.getPositie()) {
            std::vector<Bushalte>::iterator it = bushaltes.begin() + i;
            bushaltes.insert(it, bushalte);
            return;
        }
    }
    bushaltes.push_back(bushalte);
}

Bushalte* Baan::getVolgendeBushalte(int pos)
{
    for(unsigned i = 0; i < bushaltes.size(); i++) {
        Bushalte& bushalte = bushaltes[i];
        if(pos < bushalte.getPositie()) // We nemen meteen dit licht omdat onze verkeerslichten volgens afstand gesorteerd zijn
            return &bushalte;
    }
    return NULL;
}

const Voertuig* Baan::getVoorligger(int pos) const {
    REQUIRE(pos >= 0, "pos mag niet negatief zijn");

    const Voertuig* returnval = NULL;

    for(unsigned i = 0; i < voertuigen.size(); i++) {
        const Voertuig* voertuig = voertuigen[i];
        if(pos < voertuig->getPositie()) { // We nemen meteen dit voertuig omdat onze verkeerslichten volgens afstand gesorteerd zijn
            returnval = voertuig;
            break;
        }
    }
    ENSURE(returnval == NULL || pos < returnval->getPositie(), "POST: returnval is geen voorligger");
    return returnval;
}

const Voertuig* Baan::getAchtersteVoertuig() const {
    if(voertuigen.size() <= 0) return NULL;
    return voertuigen[0];
}

void Baan::update(float deltaTime_s)
{
    for(unsigned i = 0; i < verkeerslichten.size(); i++) {
        Verkeerslicht& licht = verkeerslichten[i];
        licht.update(deltaTime_s);
    }

    // We lopen de lijst van achter naar voren af, omdat we de lijst ondertussen bewerken
    for(int i = voertuigen.size()-1; i >= 0; i--) {
        Voertuig* tuig = voertuigen[i];
        tuig->update(deltaTime_s, getVolgendeLicht(tuig->getPositie()), getVoorligger(tuig->getPositie()), getVolgendeBushalte(tuig->getPositie()));
        if(tuig->getPositie() > getLengte()) {
            voertuigen.erase(voertuigen.begin() + i);
        }
    }
}

bool Baan::done() const {
    return voertuigen.empty();
}

void Baan::teken(std::ostream& os) const {
    std::string baanNaamStr = getNaam();
    std::string verkeerslichtenStr = " >verkeerslichten";
    std::string bushalteStr = " >bushaltes";
    int width = std::max(std::max(baanNaamStr.size(), verkeerslichtenStr.size()), bushalteStr.size());

    os << baanNaamStr;
    for(int i = baanNaamStr.size(); i < width; i++) { os << " "; }

    os << "| ";
    int baanPos = 0;
    for(std::vector<Voertuig*>::size_type i = 0; i < voertuigen.size(); i++) {
        const Voertuig* voertuig = voertuigen[i];
        for(; baanPos < voertuig->getPositie(); baanPos++) {
            os << "=";
        }
        std::string voertuigType = voertuig->getType();
        if(voertuigType.empty()) {std::cerr << "Baan::teken : voertuig heeft geen grafische voorstelling;\n";}
        os << (char)(toupper(voertuig->getType()[0]));
    }
    for(; baanPos < getLengte(); baanPos++) {
        os << "=";
    }
    os << "\n";

    os << verkeerslichtenStr;
    for(int i = verkeerslichtenStr.size(); i < width; i++) { os << " "; }
    os << "| ";
    baanPos = 0;
    // volgendeBushalte variabele nodig om het streepje '|' te tekenen
    std::vector<Bushalte>::const_iterator volgendeBushalte = bushaltes.empty()? bushaltes.end() : bushaltes.begin();
    for(std::vector<Verkeerslicht*>::size_type i = 0; i < verkeerslichten.size(); i++) {
        const Verkeerslicht& verkeerslicht = verkeerslichten[i];

        if(volgendeBushalte != bushaltes.end() && volgendeBushalte->getPositie() < verkeerslicht.getPositie()) {
            for(; baanPos < volgendeBushalte->getPositie(); baanPos++) {
                os << " ";
            }
            os << "|";
            volgendeBushalte++;
        }
        for(; baanPos < verkeerslicht.getPositie(); baanPos++) {
            os << " ";
        }
        os << (verkeerslicht.isRood()? "R" : "G");
    }
    for(;volgendeBushalte != bushaltes.end(); volgendeBushalte++) {
        for(; baanPos < volgendeBushalte->getPositie(); baanPos++) {
            os << " ";
        }
        os << "|";
    }

    os << "\n";

    os << bushalteStr;
    for(int i = bushalteStr.size(); i < width; i++) { os << " "; }
    os << "| ";
    baanPos = 0;
    for(std::vector<Bushalte>::size_type i = 0; i < bushaltes.size(); i++) {
        const Bushalte& bushalte = bushaltes[i];
        for(; baanPos < bushalte.getPositie(); baanPos++) {
            os << " ";
        }
        os << (bushalte.toegekendeBus? "H" : "h"); // 'H' -> halte geclaimd door bus, 'h' halte ongeclaimd
    }

    os << "\n";
}

Baan::Baan(const Baan &other) : naam(other.naam), lengte(other.lengte), verkeerslichten(other.verkeerslichten), voertuigen()
{
    for(std::vector<Voertuig*>::size_type i = 0; i < other.voertuigen.size(); i++) {
        Voertuig* other_v = other.voertuigen[i];
        voertuigen.push_back(VoertuigFactory::getInstance()->create(other_v->getType(), other_v->getBaanNaam(), other_v->getPositie()));
    }
}



