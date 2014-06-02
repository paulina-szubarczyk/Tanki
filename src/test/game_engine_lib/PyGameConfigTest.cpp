/*
 * PythonInterpreterTest.cpp
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#include "gtest/gtest.h"

#include "PyGameConfig.h"

using namespace ships;

class PyGameConfigTest : public ::testing::Test {
protected:
	PyGameConfigTest() {};
	~PyGameConfigTest() {};
	virtual void SetUp() {};
	virtual void TearDown() {};

	static const std::string testDir;
};

const std::string PyGameConfigTest::testDir = "../../../test_data/";

TEST_F(PyGameConfigTest, CtorDtorTest) {


	PyGameConfig interp(testDir + "print.py", "configure");
}

TEST_F(PyGameConfigTest, GetConfTest) {

	PyGameConfig interp(testDir + "print.py", "configure");
	std::map<std::string, std::string> params = interp.getConfiguration();
	EXPECT_EQ(params.size(), 2);
	EXPECT_EQ(params["jeden"], "dwa");
	EXPECT_EQ(params["cztery"], "osiem");
}


