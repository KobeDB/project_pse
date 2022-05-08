//
// Created by kobedb on 08.05.22.
//

#ifndef PROJECT_PSE_OURTESTINGUTILS_H
#define PROJECT_PSE_OURTESTINGUTILS_H


#include "Verkeerssimulatie.h"

class OurTestingUtils {
public:
    static void testSimulatie(Verkeerssimulatie& verkeerssimulatie, const unsigned stappen, const float tijdstap_s, const std::string& outputFromTest, const std::string& toCompareWith);
};


#endif //PROJECT_PSE_OURTESTINGUTILS_H
