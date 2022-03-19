#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <unistd.h>
#include "tinyxml.h"

#include "Verkeerslicht.h"
#include "Baan.h"
#include "Verkeerssimulatie.h"
#include "Voertuig.h"






int main() {
    using namespace std;

    vector<Baan> banen;
    vector<Verkeerslicht> lichten;
    vector<Voertuig> voertuigen;
//    readVerkeerssituatieFromXml("test.xml", banen, lichten, voertuigen);

    Verkeerssimulatie simulatie(banen, lichten, voertuigen);
    std::cout << "SIMULATIE: \n";
    std::cout << simulatie << "\n";
    float time = 0;
    for(int i = 0; i < 55; i++) {
        float deltaTime_s = 1;
        usleep((int)(deltaTime_s * 1000)); // usleep uses microseconds, adjust scaling factor to let the simulation-'seconds' tick faster
        time += deltaTime_s;
        simulatie.update(deltaTime_s);
        std::cout << "\tTijd: " << time << "\n";
        std::cout << simulatie << "\n";
    }

    return 0;
}
