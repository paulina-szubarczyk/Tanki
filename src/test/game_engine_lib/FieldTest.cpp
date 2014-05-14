/*
 * FieldTest.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */
#include "gtest/gtest.h"
#include "Field.h"

class FieldTest : public ::testing::Test {
protected:
	FieldTest() {};
	~FieldTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F(FieldTest, ConstructorTest){
	Field field;
}

TEST_F(FieldTest, PositionTest){
	Field field;
	Field field2(10);
	EXPECT_EQ(field.getPosition(), 0);
	EXPECT_EQ(field2.getPosition(),10);
}

TEST_F(FieldTest, OperatorLessThenTest){
	Field field1(10), field2(1);
	EXPECT_TRUE(field2 < field1);
	EXPECT_FALSE(field1 < field2);
}

TEST_F(FieldTest, RegisterHitObserverTest){
	std::shared_ptr<Field> field(new Field(1));

	class TestHitObserver : public HitObserver{
	public:
		TestHitObserver() : HitObserver(), id_(0), state_(0) {};
		TestHitObserver(int id) : HitObserver(), id_(id), state_(0) {};
		~TestHitObserver() = default;
		void hit() {
			++state_ ;
		}
		int getState() {return state_; }
	private:
		int id_;
		int state_;
	};

	std::shared_ptr<TestHitObserver> thobs(new TestHitObserver());
	field->registerHitObserver(thobs);
	EXPECT_EQ(thobs->getState(), 0);
	field->hit();
	EXPECT_EQ(thobs->getState(), 1);

	std::shared_ptr<TestHitObserver> thobs2(new TestHitObserver(1));
	field->registerHitObserver(thobs2);
	EXPECT_EQ(thobs2->getState(), 0);
	EXPECT_EQ(thobs->getState(), 1);
	field->hit();
	EXPECT_EQ(thobs->getState(), 2);
	EXPECT_EQ(thobs2->getState(), 1);
}



