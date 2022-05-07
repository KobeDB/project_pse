#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#include "Verkeerssimulatie.h"
#include "VoertuigFactory.h"

#include "test_utils/TicTacToeUtils.h"

class VoertuigFactoryTest: public ::testing::Test {
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

TEST_F(VoertuigFactoryTest, VoertuigFactoryGetInstanceTest) {
    ASSERT_TRUE(VoertuigFactory::getInstance());
    ASSERT_TRUE(VoertuigFactory::getInstance() == VoertuigFactory::getInstance());
}

TEST_F(VoertuigFactoryTest, VoertuigFactoryVoertuigfabricatie) {
    std::string v0Type = "auto";
    std::string v0Baan = "middelheimlaan";
    int v0Pos = 10;
    Voertuig* v0 = VoertuigFactory::getInstance()->create(v0Type, v0Baan , v0Pos);
    ASSERT_TRUE(v0->getType() == v0Type);
    ASSERT_TRUE(v0->getPositie() == v0Pos);
    ASSERT_TRUE(v0->getBaanNaam() == v0Baan);
    ASSERT_TRUE(v0->getSnelheid() == 0);
    ASSERT_TRUE(v0->getVersnelling() == 0);

    std::string v1Type = "bus";
    std::string v1Baan = "groenenborgerlaan";
    int v1Pos = 50;
    Voertuig* v1 = VoertuigFactory::getInstance()->create(v1Type, v1Baan , v1Pos);
    ASSERT_TRUE(v1->getType() == v1Type);
    ASSERT_TRUE(v1->getPositie() == v1Pos);
    ASSERT_TRUE(v1->getBaanNaam() == v1Baan);
    ASSERT_TRUE(v1->getSnelheid() == 0);
    ASSERT_TRUE(v1->getVersnelling() == 0);
}

TEST_F(VoertuigFactoryTest, VoertuigFactoryIsValidTypeTest) {
    ASSERT_TRUE(VoertuigFactory::getInstance()->isValidType("auto"));
    ASSERT_TRUE(VoertuigFactory::getInstance()->isValidType("bus"));
    ASSERT_TRUE(VoertuigFactory::getInstance()->isValidType("brandweerwagen"));
    ASSERT_TRUE(VoertuigFactory::getInstance()->isValidType("politiecombi"));
    ASSERT_TRUE(VoertuigFactory::getInstance()->isValidType("ziekenwagen"));

    ASSERT_FALSE(VoertuigFactory::getInstance()->isValidType("voertuig"));
    ASSERT_FALSE(VoertuigFactory::getInstance()->isValidType("fiets"));
    ASSERT_FALSE(VoertuigFactory::getInstance()->isValidType(""));
}