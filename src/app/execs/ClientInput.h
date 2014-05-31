/*
 * ClientInput.h
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#ifndef CLIENTINPUT_H_
#define CLIENTINPUT_H_

#include "Input.h"
#include "ClientConnection.h"

namespace ships {

class ClientInput : public Input {
typedef std::shared_ptr<ClientConnection> ConnectionPtr;
public:
	ClientInput(ConnectionPtr connection, MsgHandlerPtr msgHandler);
	virtual ~ClientInput() = default;

};

} /* namespace ships */

#endif /* CLIENTINPUT_H_ */
