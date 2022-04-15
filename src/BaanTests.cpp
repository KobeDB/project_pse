//============================================================================
// Name        : BaanTests.cpp
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

#include "Verkeerslicht.h"
#include "Baan.h"

#include "TicTacToeUtils.h"

class BaanTest: public ::testing::Test {
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


// Tests the "happy day" scenario
TEST_F(BaanTest, baanHappyDay) {
    Baan baan("Baan1", 200);
    const Verkeerslicht* licht = baan.getVolgendeLicht(0);
    EXPECT_TRUE(licht == NULL);
    const Voertuig* voertuig = baan.getVoorligger(0);
    EXPECT_TRUE(voertuig == NULL);

    Verkeerslicht volgendLicht("Baan1", 50, 5);
    baan.addVerkeerslicht(volgendLicht);

    licht = baan.getVolgendeLicht(0);
    ASSERT_TRUE(licht != NULL);
    EXPECT_TRUE(licht->getPositie() == volgendLicht.getPositie());

    Voertuig* voorligger = new Voertuig("Baan1", 60);
    baan.addVoertuig(voorligger);

    voertuig = baan.getVoorligger(0);
    ASSERT_TRUE(voertuig != NULL);
    EXPECT_TRUE(voertuig->getPositie() == voorligger->getPositie());
}