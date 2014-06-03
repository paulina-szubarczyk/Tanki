/*
 * IOutput.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: Adam Kosiorek
 */

#include "IOutput.h"
#include "glog/logging.h"
#include <stdexcept>

IOutput::IOutput(ConnectionPtr connection) : connection_(connection) {

	LOG(INFO) << "Creating IOutput";
	if(!connection) {

		std::invalid_argument err("Can't creating output for a null connection");
		LOG(ERROR) << err.what();
		throw err;
	}
};

auto IOutput::createMsg(MessageType type) const -> MsgPtr {
	auto msg = std::make_shared<DataMsg>();
	msg->set_type(type);
	return msg;
}

void IOutput::send(MsgPtr msg) const {
	connection_->send(msg);
}


