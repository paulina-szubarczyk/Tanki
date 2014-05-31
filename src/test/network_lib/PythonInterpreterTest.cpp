/*
 * PythonInterpreterTest.cpp
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#include "gtest/gtest.h"

#include "PythonInterpreter.h"

using namespace ships;

class ConfigureScriptTest : public ::testing::Test {
protected:
	ConfigureScriptTest() {};
	~ConfigureScriptTest() {};
	virtual void SetUp() {};
	virtual void TearDown() {};

	static const std::string testDir;
};

const std::string ConfigureScriptTest::testDir = "../../../test_data/";

TEST_F(ConfigureScriptTest, CtorDtorTest) {


	ConfigureScript interp(testDir + "print.py", "configure");
}

TEST_F(ConfigureScriptTest, GetConfTest) {

	ConfigureScript interp(testDir + "print.py", "configure");
	std::map<std::string, std::string> params = interp.getConfiguration();
	EXPECT_EQ(params.size(), 2);
	EXPECT_EQ(params["jeden"], "dwa");
	EXPECT_EQ(params["cztery"], "osiem");
}


