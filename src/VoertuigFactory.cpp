//
// Created by kobedb on 15.04.22.
//

#include "VoertuigFactory.h"

#include "voertuigen/Voertuig.h"
#include "voertuigen/Brandweerwagen.h"
#include "voertuigen/Bus.h"
#include "voertuigen/Auto.h"
#include "voertuigen/Politiecombi.h"
#include "voertuigen/Ziekenwagen.h"

VoertuigFactory* VoertuigFactory::factory = NULL;

VoertuigFactory* VoertuigFactory::getInstance()
{
    if(!VoertuigFactory::factory) {
        VoertuigFactory::factory = new VoertuigFactory();
    }
    return VoertuigFactory::factory;
}

VoertuigFactory::VoertuigFactory() {

    voertuigTypes.push_back("auto");
    voertuigTypes.push_back("bus");
    voertuigTypes.push_back("brandweerwagen");
    voertuigTypes.push_back("ziekenwagen");
    voertuigTypes.push_back("politiecombi");

}

bool VoertuigFactory::isValidType(const std::string& voertuigType) const
{
    return std::find(voertuigTypes.begin(), voertuigTypes.end(), voertuigType) != voertuigTypes.end();
}

Voertuig* VoertuigFactory::create(const std::string& voertuigType, const std::string& baanNaam, int positie)
{
    if(voertuigType == "auto") {
        return new Auto(baanNaam, positie);
    }
    if(voertuigType == "bus") {
        return new Bus(baanNaam, positie);
    }
    if(voertuigType == "politiecombi") {
        return new Politiecombi(baanNaam, positie);
    }
    if(voertuigType == "ziekenwagen") {
        return new Ziekenwagen(baanNaam, positie);
    }
    if(voertuigType == "brandweerwagen") {
        return new Brandweerwagen(baanNaam, positie);
    }

    std::cerr << "Factory create: niet bestaand Voertuigtype: " << voertuigType << "\n";
    return NULL;
}