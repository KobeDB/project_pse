//
// Created by kobedb on 19.03.22.
//

//============================================================================
// Name        : VerkeerssimulatieTests.cpp
// Author      : Kobe De Broeck
// Version     :
// Copyright?? : Project Software Engineering - BA1 Informatica - Kobe De Broeck - University of Antwerp
// Description : Verkeerssimulatie in C++, Ansi-style
//============================================================================

#include "VoertuigFactory.h"
#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include <fstream>

#include "voertuigen/Politiecombi.h"
#include "voertuigen/Ziekenwagen.h"
#include "voertuigen/Brandweerwagen.h"
#include "voertuigen/Auto.h"
#include "voertuigen/Bus.h"
#include "VoertuigFactory.h"

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#include "Verkeerssimulatie.h"
#include "VerkeerssituatieReader.h"

#include "voertuigen/Voertuig.h"
#include "Baan.h"

#include "test_utils/TicTacToeUtils.h"

#include "OurTestingUtils.h"

class VoertuigTest: public ::testing::Test {
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

// Tests the default constructor.
TEST_F(VoertuigTest, DefaultConstructor) {

}

// Tests the "happy day" scenario
TEST_F(VoertuigTest, HappyDay1VoertuigZonderLichten) {

    using namespace std;
    vector<BaanInfo> banen;
    banen.push_back(BaanInfo("Baan1", 100));

    vector<VerkeerslichtInfo> lichten;

    vector<VoertuigInfo> voertuigen;
    voertuigen.push_back(VoertuigInfo("Baan1", "auto", 10));

    vector<VoertuiggeneratorInfo> generatoren;

    Verkeerssimulatie sim(banen,lichten,voertuigen,generatoren);
    OurTestingUtils::testSimulatie(sim, 10, 1, "output_tests/HappyDay1VoertuigZonderLichtenTestOutput.txt", "output_tests/HappyDay1VoertuigZonderLichtenTestExpectedOutput.txt");
}

// Tests the "happy day" scenario
TEST_F(VoertuigTest, HappyDay1VoertuigMetLicht) {

    using namespace std;
    vector<BaanInfo> banen;
    banen.push_back(BaanInfo("Baan1", 200));

    vector<VerkeerslichtInfo> lichten;
    lichten.push_back(VerkeerslichtInfo("Baan1", 140, 7));

    vector<VoertuigInfo> voertuigen;
    voertuigen.push_back(VoertuigInfo("Baan1", "auto", 10));

    vector<VoertuiggeneratorInfo> generatoren;

    Verkeerssimulatie sim(banen,lichten,voertuigen,generatoren);
    OurTestingUtils::testSimulatie(sim, 10, 1, "output_tests/HappyDay1VoertuigMetLichtTestOutput.txt", "output_tests/HappyDay1VoertuigMetLichtTestExpectedOutput.txt");
}

TEST_F(VoertuigTest, HappyDayVoertuigenMetLicht) {
    using namespace std;
    vector<BaanInfo> banen;
    banen.push_back(BaanInfo("Baan1", 200));

    vector<VerkeerslichtInfo> lichten;
    lichten.push_back(VerkeerslichtInfo("Baan1", 140, 6));

    vector<VoertuigInfo> voertuigen;
    voertuigen.push_back(VoertuigInfo("Baan1", "auto", 40));
    voertuigen.push_back(VoertuigInfo("Baan1", "bus", 70));

    vector<VoertuiggeneratorInfo> generatoren;

    Verkeerssimulatie sim(banen,lichten,voertuigen,generatoren);
    OurTestingUtils::testSimulatie(sim, 10, 1, "output_tests/HappyDayVoertuigenMetLichtTestOutput.txt", "output_tests/HappyDayVoertuigenMetLichtTestExpectedOutput.txt");
}

TEST_F(VoertuigTest, PrioriteitsvoertuigenTest) {
    using namespace std;

    vector<BaanInfo> banen;
    banen.push_back(BaanInfo("Baan1", 200));

    vector<VerkeerslichtInfo> lichten;
    lichten.push_back(VerkeerslichtInfo("Baan1", 100, 5));

    vector<VoertuigInfo> voertuigen;
    voertuigen.push_back(VoertuigInfo("Baan1", "auto", 40));

    vector<VoertuiggeneratorInfo> generatoren;
    generatoren.push_back(VoertuiggeneratorInfo("Baan1", "politiecombi", 5));
    generatoren.push_back(VoertuiggeneratorInfo("Baan1", "ziekenwagen", 30));

    Verkeerssimulatie verkeerssimulatie(banen, lichten, voertuigen, generatoren);

    OurTestingUtils::testSimulatie(verkeerssimulatie, 10, 1, "output_tests/PrioriteitsvoertuigenTestOutput.txt", "output_tests/PrioriteitsvoertuigenTestExpectedOutput.txt");
}
