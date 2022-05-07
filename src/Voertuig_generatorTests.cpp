#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#include "Verkeerssimulatie.h"
#include "Voertuig_generator.h"

#include "test_utils/TicTacToeUtils.h"

class Voertuig_generatorTest: public ::testing::Test {
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

TEST_F(Voertuig_generatorTest, Voertuig_generatorTestHappyDay) {
    Baan b1("middelheimlaan", 300);
    Voertuig_generator generator(b1.getNaam(), "auto", 5);
    generator.update(1, &b1);
    ASSERT_TRUE(b1.getVoertuigenAmt() == 0);
    generator.update(5, &b1);
    ASSERT_TRUE(b1.getVoertuigenAmt() == 1);
    generator.update(1, &b1);
    ASSERT_TRUE(b1.getVoertuigenAmt() == 1);
    generator.update(6, &b1);
    ASSERT_TRUE(b1.getVoertuigenAmt() == 2);
}
