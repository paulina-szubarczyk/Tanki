/*
 * packedmessagetest.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: Adam Kosiorek
 */
#include "gtest/gtest.h"

#include "MessagePacker.h"
#include "test.pb.h"
#include <memory>

namespace {

class MessagePackerTest : public ::testing::Test {
protected:
	MessagePackerTest() {};
	~MessagePackerTest() {};
	virtual void SetUp() {};
	virtual void TearDown() {};

	typedef MessagePacker<TestMsg> PackedMessageType;
	typedef PackedMessageType::BufferType BufferType;
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(MessagePackerTest, PacksAndUnpacksMessage) {

	std::shared_ptr<TestMsg> testMsgFrom(new TestMsg());

	testMsgFrom->set_field(100);
	BufferType buffer;

	PackedMessageType packedMsgIn(testMsgFrom);
	ASSERT_TRUE(packedMsgIn.pack(buffer));

	PackedMessageType packedMsgOut;
	ASSERT_TRUE(packedMsgOut.unpack(buffer));

	ASSERT_EQ(packedMsgOut.getMsg()->field(), packedMsgIn.getMsg()->field());
}

TEST_F(MessagePackerTest, ExceptionOnNullMsgSet) {

	std::shared_ptr<TestMsg> testPtr;
	EXPECT_ANY_THROW(new PackedMessageType(testPtr));
	PackedMessageType testMsg;
	EXPECT_ANY_THROW(testMsg.setMsg(testPtr));
}

TEST_F(MessagePackerTest, DecodeHeaderSmallBuffer) {

	BufferType buffer;
	PackedMessageType testMsg;
	testMsg.getMsg()->set_field(100);
	testMsg.pack(buffer);

	BufferType smallBuffer(0);
	EXPECT_ANY_THROW(testMsg.decodeHeader(smallBuffer));
}

TEST_F(MessagePackerTest, DecodeHeader) {

	std::shared_ptr<TestMsg> msg(new TestMsg);
	msg->set_field(100);
	int size = msg->ByteSize();
	BufferType buffer(4);
	PackedMessageType packedMsg(msg);
	packedMsg.pack(buffer);
	EXPECT_EQ(packedMsg.decodeHeader(buffer), size);
}

TEST_F(MessagePackerTest, PackUninitializedMsg) {

	std::shared_ptr<TestMsg> msg(new TestMsg);
	BufferType buffer(4);
	PackedMessageType packedMsg(msg);
	EXPECT_ANY_THROW(packedMsg.pack(buffer));
}



}  // namespace



