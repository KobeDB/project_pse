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

#include "TicTacToeUtils.h"

class VerkeerssimulatieInputTest: public ::testing::Test {
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
TEST_F(VerkeerssimulatieInputTest, DefaultConstructor) {

}

// Tests the "happy day" scenario
TEST_F(VerkeerssimulatieInputTest, HappyDay) {
    ofstream ofs("happyDayError.txt");
    ostringstream oss;
    VerkeerssituatieReader reader("reader_tests/input/happyDay.xml", oss);
    ASSERT_TRUE(oss.str().size() == 0); // Asserteer dat er geen errors waren

    std::vector<BaanInfo> banen = reader.getBanen();
    ASSERT_TRUE(banen.size() == 1);
    EXPECT_TRUE(banen[0].naam == "Middelheimlaan");
    EXPECT_TRUE(banen[0].lengte == 600);

    std::vector<VerkeerslichtInfo> lichten = reader.getVerkeerslichten();
    ASSERT_TRUE(lichten.size() == 1);
    EXPECT_TRUE(lichten[0].baanNaam == banen[0].naam);
    EXPECT_TRUE(lichten[0].positie == 450);
    EXPECT_TRUE(lichten[0].cyclus == 10);
}

TEST_F(VerkeerssimulatieInputTest, InputIllegalVerkeerssituaties) {
    std::string inputDir = "reader_tests/input/";
    ASSERT_TRUE(DirectoryExists(inputDir));

    ofstream myfile;
    int fileCounter = 1;
    string fileName = inputDir + "illegalVerkeerssituatie" + SSTR(fileCounter) + ".xml";
    string errorfileName;

    while (FileExists (fileName)) {
        std::string testResult =(inputDir + "zzzError.txt");
        myfile.open(testResult.c_str());
        VerkeerssituatieReader reader(fileName, myfile);
        myfile.close();
        errorfileName = inputDir + "illegalError" + SSTR(fileCounter) + ".txt";
        if(!FileExists(errorfileName)) {
            ofstream outf(errorfileName.c_str());
            ifstream ifs(testResult.c_str());
            outf << ifs.rdbuf();
        }

        EXPECT_TRUE(FileCompare(testResult, errorfileName));

        fileCounter = fileCounter + 1;
        fileName = inputDir + "illegalVerkeerssituatie" + SSTR(fileCounter) + ".xml";
    }
}