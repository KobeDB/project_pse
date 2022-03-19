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
    Verkeerssimulatie* simulatie;
};

// Tests the default constructor.
TEST_F(VerkeerssimulatieInputTest, DefaultConstructor) {

}

// Tests the "happy day" scenario
TEST_F(VerkeerssimulatieInputTest, HappyDay) {
}

TEST_F(VerkeerssimulatieInputTest, CornerCases) {
    std::string inputFilesPath =  "reader_tests/input/";
    std::string outputFilesPath = "reader_tests/output/";

    std::ofstream ofs("reader_tests/output/out_test_no_root.xml");
    VerkeerssituatieReader("reader_tests/input/illegalVerkeerssituatie1.xml", ofs);

}

TEST_F(VerkeerssimulatieInputTest, InputIllegalGames) {
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