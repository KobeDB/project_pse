//
// Created by kobedb on 08.05.22.
//

#include "OurTestingUtils.h"

#include "VoertuigFactory.h"
#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "test_utils/TicTacToeUtils.h"

void OurTestingUtils::testSimulatie(Verkeerssimulatie &verkeerssimulatie, const unsigned stappen, const float tijdstap_s, const std::string &outputFromTest,
                                    const std::string &toCompareWith) {
    using namespace std;

    std::ofstream testOutput;
    testOutput.open(outputFromTest.c_str());
    if(!testOutput) cerr << "happyDayOutputTest: kan output file niet openen\n";

    for(unsigned i = 0; i < stappen; i++) {
        verkeerssimulatie.update(tijdstap_s);
        testOutput << verkeerssimulatie << "\n";
    }
    testOutput.close();

    ifstream ifs;
    ifs.open(toCompareWith.c_str());
    if(!ifs)
        cerr << "Couldn't open toCompareWith!\n";

    EXPECT_TRUE(FileCompare(outputFromTest, toCompareWith));

}
