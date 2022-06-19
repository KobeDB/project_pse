#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include <fstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#include "Verkeerssimulatie.h"
#include "VerkeerssituatieReader.h"

#include "voertuigen/Auto.h"

#include "test_utils/TicTacToeUtils.h"

using namespace std;

class VerkeerssimulatieOutputTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Declares the variables your tests want to use.
};


TEST_F(VerkeerssimulatieOutputTest, OutputHappyDay) {
    vector<BaanInfo> banen;
    BaanInfo baan1 ("Baan1", 200);
    banen.push_back(baan1);

    vector<VerkeerslichtInfo> lichten;
    VerkeerslichtInfo licht(baan1.naam, 100, 5);

    vector<VoertuigInfo> voertuigen;
    VoertuigInfo auto1(baan1.naam, "auto", 40);
    voertuigen.push_back(auto1);

    vector<VoertuiggeneratorInfo> generatoren;
    generatoren.push_back(VoertuiggeneratorInfo(baan1.naam, "bus", 5));

    vector<BushalteInfo> bushaltes;

    Verkeerssimulatie verkeerssimulatie(banen, lichten, voertuigen, generatoren, bushaltes);

    ofstream testOutput("output_tests/happyDayTestOutput.txt");
    if(!testOutput) cerr << "happyDayOutputTest: kan output file niet openen\n";

    const int stappen = 10;
    const float tijdstap_s = 1;
    for(int i = 0; i < stappen; i++) {
        verkeerssimulatie.update(tijdstap_s);
        testOutput << verkeerssimulatie << "\n";
    }
    testOutput.close();
    EXPECT_TRUE(FileCompare("output_tests/happyDayExpectedOut.txt", "output_tests/happyDayTestOutput.txt"));
}

TEST_F(VerkeerssimulatieOutputTest, tekenTest) {
    vector<BaanInfo> banen;
    BaanInfo baan1 ("Baan1", 200);
    banen.push_back(baan1);

    vector<VerkeerslichtInfo> lichten;
    VerkeerslichtInfo licht(baan1.naam, 100, 5);

    vector<VoertuigInfo> voertuigen;
    VoertuigInfo auto1(baan1.naam, "auto", 40);
    voertuigen.push_back(auto1);

    vector<VoertuiggeneratorInfo> generatoren;
    generatoren.push_back(VoertuiggeneratorInfo(baan1.naam, "bus", 5));

    vector<BushalteInfo> bushaltes;
    bushaltes.push_back(BushalteInfo(baan1.naam, 60, 10));

    Verkeerssimulatie verkeerssimulatie(banen, lichten, voertuigen, generatoren, bushaltes);

    ofstream testOutput("output_tests/happyDayTekenTestOutput.txt");
    if(!testOutput) cerr << "happyDayTekenOutputTest: kan output file niet openen\n";

    const int stappen = 10;
    const float tijdstap_s = 1;
    for(int i = 0; i < stappen; i++) {
        verkeerssimulatie.update(tijdstap_s);
        verkeerssimulatie.teken(testOutput);
    }
    testOutput.close();
    EXPECT_TRUE(FileCompare("output_tests/happyDayTekenExpectedOut.txt", "output_tests/happyDayTekenTestOutput.txt"));
}