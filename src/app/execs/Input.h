/*
 * Input.h
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "MessageHandler.h"
#include "message.pb.h"

#include <memory>

namespace ships {

class Input {
protected:
	typedef MessageHandler<MessageType, DataMsg> MsgHandlerType;
	typedef std::shared_ptr<MsgHandlerType> MsgHandlerPtr;
	typedef MsgHandlerType::MsgType MsgType;

public:
	Input(MsgHandlerPtr msgHandler) : msgHandler_(msgHandler) {};
	virtual ~Input() = default;

protected:
	MsgHandlerPtr msgHandler_;
};

} /* namespace ships */

#endif /* INPUT_H_ */
