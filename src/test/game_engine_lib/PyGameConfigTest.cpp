/*
 * PythonInterpreterTest.cpp
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#include "gtest/gtest.h"

#include "PyGameConfig.h"


using namespace game;

#include <stdexcept>
#include <memory>

class PyGameConfigTest : public ::testing::Test {
protected:
	PyGameConfigTest() {};
	~PyGameConfigTest() {};
	virtual void SetUp() {};
	virtual void TearDown() {};

	static const std::string testDir;
	std::shared_ptr<IGameConfig> gameConfig;
};

const std::string PyGameConfigTest::testDir = "../../../test_data/";

TEST_F(PyGameConfigTest, CtorDtorTest) {


	EXPECT_NO_THROW(gameConfig.reset(new PyGameConfig(testDir + "test.py")));

	EXPECT_THROW(gameConfig.reset(new PyGameConfig("")), std::runtime_error);
}

TEST_F(PyGameConfigTest, GameboardSizeTest) {

	gameConfig.reset(new PyGameConfig(testDir + "test.py"));
	EXPECT_NO_THROW(
			EXPECT_EQ(gameConfig->getGameboardSize(), 10)
	);
}

TEST_F(PyGameConfigTest, ShipConfigTest) {

	gameConfig.reset(new PyGameConfig(testDir + "test.py"));
	std::map<int, int> shipConfig;
	EXPECT_NO_THROW (shipConfig = gameConfig->getShipConfig());
	EXPECT_EQ(shipConfig.size(), 2);
	EXPECT_EQ(shipConfig[1], 2);
	EXPECT_EQ(shipConfig[4], 8);
}


