/*
 * packedmessagetest.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: Adam Kosiorek
 */
#include "gtest/gtest.h"
#include "message.pb.h"
#include "MessageHandler.h"

namespace {

using namespace google::protobuf;
using namespace ships;

class MessageHandlerTest : public ::testing::Test {
protected:
	MessageHandlerTest() {};
	~MessageHandlerTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};

	typedef MessageHandler<MessageType, DataMsg> MsgHandlerType;
};

TEST_F(MessageHandlerTest, CtorDtorTest) {

	MsgHandlerType m;
}

TEST_F(MessageHandlerTest, TypeMethodTest) {

	MsgHandlerType m;
	DataMsg msg;
	msg.set_type(MessageType::SHIP);

	auto typeMethod = [](const MsgHandlerType::MsgType& message) -> MessageType { return message.type(); };
	m.setTypeMethod(typeMethod);

	EXPECT_EQ(m.resolveType(msg), MessageType::SHIP);
}

TEST_F(MessageHandlerTest, AddHandlerTest) {

	MsgHandlerType m;

	auto typeMethod = [](const MsgHandlerType::MsgType& message) -> MessageType { return message.type(); };
	m.setTypeMethod(typeMethod);

	ASSERT_EQ(m.getMsgHandlers().size(), 0);
	auto shipHandler = [](const DataMsg& message) { std::cout << "Ship" << std::endl; };
	auto xyHandler = [](const DataMsg& message) { std::cout << "XY" << std::endl; };

	EXPECT_TRUE(m.addMsgHandler(MessageType::SHIP, shipHandler));
	EXPECT_TRUE(m.addMsgHandler(MessageType::XY, xyHandler));
	ASSERT_EQ(m.getMsgHandlers().size(), 2);
	EXPECT_FALSE(m.addMsgHandler(MessageType::SHIP, shipHandler));
	ASSERT_EQ(m.getMsgHandlers().size(), 2);
	ASSERT_NE(m.getMsgHandlers().find(MessageType::XY), m.getMsgHandlers().end());
}

TEST_F(MessageHandlerTest, HandlerTest) {

	MsgHandlerType m;
	std::stringstream testOutputStream;

	auto typeMethod = [](const MsgHandlerType::MsgType& message) -> MessageType { return message.type(); };
	auto shipHandler = [&testOutputStream](const DataMsg& message) { testOutputStream << "Ship"; };
	auto xyHandler = [&testOutputStream](const DataMsg& message) { testOutputStream << "XY"; };

	m.setTypeMethod(typeMethod);
	m.addMsgHandler(MessageType::SHIP, shipHandler);
	m.addMsgHandler(MessageType::XY, xyHandler);

	DataMsg dataMsg;

	dataMsg.set_type(MessageType::SHIP);
	m.handleMsg(dataMsg);
	EXPECT_EQ(testOutputStream.str(), "Ship");

	//clear the stream
	testOutputStream.str(std::string());

	dataMsg.set_type(MessageType::XY);
	m.handleMsg(dataMsg);
	EXPECT_EQ(testOutputStream.str(), "XY");
}

//TEST_F(MessageParserTest, Test) {
//
//}
//
//TEST_F(MessageParserTest, Test) {
//
//}






}  // namespace



