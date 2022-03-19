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

#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#include "Verkeerssimulatie.h"
#include "VerkeerssituatieReader.h"

#include "Voertuig.h"
#include "Baan.h"

#include "TicTacToeUtils.h"

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
TEST_F(VoertuigTest, HappyDayZonderLichten) {
    std::map<std::string, Baan> banen;
    banen["Baan1"] = Baan("Baan1", 400);
    Voertuig voertuig(banen["Baan1"].getNaam(), 10);
    EXPECT_TRUE(voertuig.getBaanNaam() == banen["Baan1"].getNaam());

    voertuig.update(1, banen);
    EXPECT_NEAR(voertuig.getPositie(), 20, 1);
    EXPECT_NEAR(voertuig.getSnelheid(), 10, 1);
    EXPECT_NEAR(voertuig.getVersnelling(), 1.25, 1);


}
