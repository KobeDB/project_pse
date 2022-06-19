#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <unistd.h>
#include "tinyxml/tinyxml.h"
#include <fstream>

#include "Verkeerslicht.h"
#include "Baan.h"
#include "Verkeerssimulatie.h"
#include "voertuigen/Voertuig.h"
#include "VerkeerssituatieReader.h"


int main() {
    using namespace std;

    VerkeerssituatieReader reader("verkeerssituaties/gewone_verkeerssituatie.xml", cerr);

    Verkeerssimulatie simulatie(reader.getBanen(), reader.getVerkeerslichten(), reader.getVoertuigen(), reader.getVoertuiggeneratoren(), reader.getBushaltes());
    std::cout << "SIMULATIE: \n";
    std::cout << simulatie << "\n";
    std::ofstream grafischeImpressie("grafische_impressie.txt");

    float tick = 0;
    const float deltaTime_s = 0.016;
    for(float time_s = 0; time_s < 100; time_s += deltaTime_s) { // We stoppen na 100 updates als simulatie blijft hangen

//        usleep((int)(deltaTime_s * 1000)); // usleep uses microseconds, adjust scaling factor to let the simulation-'seconds' tick faster

        simulatie.update(deltaTime_s);
//        if(simulatie.done())
//            break;

        // Print de situatie af om de zoveel stappen
        tick += deltaTime_s;
        if(tick > 1) {
            tick = 0;
            std::cout << "\tTijd: " << time_s << "\n";
            simulatie.teken(cout);
            simulatie.teken(grafischeImpressie);
        }

        //std::cout << simulatie << "\n";
    }

    return 0;
}
