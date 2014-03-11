/*
 * packedmessagetest.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: Adam Kosiorek
 */
#include "gtest/gtest.h"

#include "packedmessage.h"
#include "test.pb.h"
#include <memory>

namespace {

class PackedMessageTest : public ::testing::Test {
protected:
	PackedMessageTest() {};
	~PackedMessageTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(PackedMessageTest, PacksAndUnpacksMessage) {

	std::shared_ptr<TestMsg> testMsgFrom(new TestMsg());

	testMsgFrom->set_field(100);
	DataBuffer buffer;

	PackedMessage<TestMsg> packedMsgIn(testMsgFrom);
	ASSERT_TRUE(packedMsgIn.pack(buffer));

	PackedMessage<TestMsg> packedMsgOut;
	ASSERT_TRUE(packedMsgOut.unpack(buffer));

	ASSERT_EQ(packedMsgOut.getMsg()->field(), packedMsgIn.getMsg()->field());
}

TEST_F(PackedMessageTest, ExceptionOnNullMsgSet) {

	std::shared_ptr<TestMsg> testPtr;
	EXPECT_ANY_THROW(new PackedMessage<TestMsg>(testPtr));
	PackedMessage<TestMsg> testMsg;
	EXPECT_ANY_THROW(testMsg.setMsg(testPtr));
}

TEST_F(PackedMessageTest, DecodeHeaderSmallBuffer) {

	DataBuffer buffer;
	PackedMessage<TestMsg> testMsg;
	testMsg.getMsg()->set_field(100);
	testMsg.pack(buffer);

	DataBuffer smallBuffer(0);
	EXPECT_ANY_THROW(testMsg.decodeHeader(smallBuffer));
}

TEST_F(PackedMessageTest, DecodeHeader) {

	std::shared_ptr<TestMsg> msg(new TestMsg);
	msg->set_field(100);
	int size = msg->ByteSize();
	DataBuffer buffer(4);
	PackedMessage<TestMsg> packedMsg(msg);
	packedMsg.pack(buffer);
	EXPECT_EQ(packedMsg.decodeHeader(buffer), size);
}

TEST_F(PackedMessageTest, PackUninitializedMsg) {

	std::shared_ptr<TestMsg> msg(new TestMsg);
	DataBuffer buffer(4);
	PackedMessage<TestMsg> packedMsg(msg);
	EXPECT_ANY_THROW(packedMsg.pack(buffer));
}



}  // namespace



