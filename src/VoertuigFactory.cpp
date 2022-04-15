//
// Created by kobedb on 15.04.22.
//

#include "VoertuigFactory.h"

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
        // return new Bus(baanNaam, positie);
    }
    //enzovoort

    std::cerr << "Factory create: niet bestaand Voertuigtype: " << voertuigType << "\n";
    return NULL;
}