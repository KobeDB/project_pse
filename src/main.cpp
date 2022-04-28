#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <unistd.h>
#include "tinyxml/tinyxml.h"

#include "Verkeerslicht.h"
#include "Baan.h"
#include "Verkeerssimulatie.h"
#include "voertuigen/Voertuig.h"
#include "VerkeerssituatieReader.h"


int main() {
    using namespace std;

    VerkeerssituatieReader reader("verkeerssituaties/gewone_verkeerssituatie.xml", cerr);

    Verkeerssimulatie simulatie(reader.getBanen(), reader.getVerkeerslichten(), reader.getVoertuigen(), reader.getVoertuiggeneratoren());
    std::cout << "SIMULATIE: \n";
    std::cout << simulatie << "\n";
    float time = 0;
    for(int i = 0; i < 10000; i++) { // We stoppen na 100 updates als simulatie blijft hangen
        if(time > 158) {
            //cout << "big ballz";
        }
        float deltaTime_s = 0.016;
//        usleep((int)(deltaTime_s * 1000)); // usleep uses microseconds, adjust scaling factor to let the simulation-'seconds' tick faster
        time += deltaTime_s;
        simulatie.update(deltaTime_s);
        if(simulatie.done())
            break;
        std::cout << "\tTijd: " << time << "\n";
        //std::cout << simulatie << "\n";
    }

    return 0;
}
