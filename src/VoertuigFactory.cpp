//
// Created by kobedb on 15.04.22.
//

#include "VoertuigFactory.h"

#include "test_utils/DesignByContract.h"

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
    REQUIRE(positie >= 0, "positie moet >=0");

    Voertuig* result = NULL;

    if(voertuigType == "auto") {
        result = new Auto(baanNaam, positie);
    }
    if(voertuigType == "bus") {
        result = new Bus(baanNaam, positie);
    }
    if(voertuigType == "politiecombi") {
        result = new Politiecombi(baanNaam, positie);
    }
    if(voertuigType == "ziekenwagen") {
        result = new Ziekenwagen(baanNaam, positie);
    }
    if(voertuigType == "brandweerwagen") {
        result = new Brandweerwagen(baanNaam, positie);
    }

    if(result == NULL) {
        std::cerr << "Factory create: niet bestaand Voertuigtype: " << voertuigType << "\n";
    }

    ENSURE(isValidType(voertuigType)? result != NULL && result->getType() == voertuigType : result == NULL, "Indien het voertuigType bestaat, is er een instantie van dat type gemaakt");

    return result;
}