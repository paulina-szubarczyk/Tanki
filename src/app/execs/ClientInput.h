/*
 * ClientInput.h
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#ifndef CLIENTINPUT_H_
#define CLIENTINPUT_H_

#include "IInput.h"
#include "ClientConnection.h"

using namespace net;

class ClientInput : public IInput {
typedef std::shared_ptr<ClientConnection> ConnectionPtr;
public:
	ClientInput(ConnectionPtr connection, MsgHandlerPtr msgHandler);
	virtual ~ClientInput();

};

#endif /* CLIENTINPUT_H_ */
