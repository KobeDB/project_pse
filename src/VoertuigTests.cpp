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

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#include "Verkeerssimulatie.h"
#include "VerkeerssituatieReader.h"

#include "voertuigen/Voertuig.h"
#include "Baan.h"

#include "test_utils/TicTacToeUtils.h"

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
    Voertuig* voertuig = VoertuigFactory::getInstance()->create("auto", "Baan1", 10);
    voertuig->update(1, NULL, NULL);
    EXPECT_NEAR(voertuig->getPositie(), 20, 1);
    EXPECT_NEAR(voertuig->getSnelheid(), 10, 1);
    EXPECT_NEAR(voertuig->getVersnelling(), 1.25, 1);
}

// Tests the "happy day" scenario
TEST_F(VoertuigTest, HappyDay1VoertuigMetLicht) {
    Verkeerslicht licht("Baan1", 140, 7);

    Voertuig voertuig("Baan1", 10);
    voertuig.update(1, &licht, NULL);
    EXPECT_NEAR(voertuig.getPositie(), 20, 1);
    EXPECT_NEAR(voertuig.getSnelheid(), 10, 1);
    EXPECT_NEAR(voertuig.getVersnelling(), 1.25, 1);

    for(int i = 0; i < 11; i++) {
        licht.update(1);
        voertuig.update(1, &licht, NULL);
//        std::cout << licht.isRood();
//        std::cout << voertuig << "\n";
    }
    EXPECT_NEAR(voertuig.getSnelheid(), 0, 2);
}

TEST_F(VoertuigTest, HappyDayVoertuigenMetLicht) {
    Verkeerslicht licht("Baan1", 140, 6);

    Voertuig voertuig1("Baan1", 30);
    Voertuig voertuig2("Baan1", 0);
    voertuig1.update(1, &licht, NULL);
    voertuig2.update(1, &licht, &voertuig1);
    EXPECT_NEAR(voertuig1.getPositie(), 40, 1);
    EXPECT_NEAR(voertuig1.getSnelheid(), 10, 1);
    EXPECT_NEAR(voertuig1.getVersnelling(), 1, 1);
    EXPECT_NEAR(voertuig2.getPositie(), 10, 1);
    EXPECT_NEAR(voertuig2.getSnelheid(), 10, 1);
    EXPECT_NEAR(voertuig2.getVersnelling(), 1, 1);

    for(int i = 0; i < 10; i++) {
        licht.update(1);
        voertuig1.update(1, &licht, NULL);
        voertuig2.update(1, &licht, &voertuig1);
//        std::cout << "Tijdstip: " << i << "\n";
//        std::cout << "" << licht.isRood();
//        std::cout << "\t" << voertuig1 << "\n";
    }
    //Licht rood
    EXPECT_NEAR(voertuig2.getSnelheid(), 0, 2);
    EXPECT_NEAR(voertuig1.getSnelheid(), 0, 2);

    for(int i = 0; i < 3; i++) {
        licht.update(1);
        voertuig1.update(1, &licht, NULL);
        voertuig2.update(1, &licht, &voertuig1);
    }
    //Licht terug groen
    EXPECT_GT(voertuig1.getSnelheid(), 3);
    EXPECT_GT(voertuig2.getSnelheid(), 3);

}
