//============================================================================
// Name        : VerkeerslichtTests.cpp
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

#include "test_utils/TicTacToeUtils.h"

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

// TestVerkeerslichtTest
TEST_F(BaanTest, DefaultConstructor) {

}

// Tests the "happy day" scenario
TEST_F(BaanTest, EXTREMEFULLTEST) {
    Verkeerslicht licht("Baan1", 50, 5);
    EXPECT_FALSE(licht.isRood());
    licht.update(4);
    EXPECT_FALSE(licht.isRood());
    licht.update(1);
    EXPECT_TRUE(licht.isRood());
    licht.update(3);
    EXPECT_TRUE(licht.isRood());
    licht.update(2);
    EXPECT_FALSE(licht.isRood());
}