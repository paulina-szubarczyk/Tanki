/*
 * PlayerInput.h
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#ifndef PLAYERINPUT_H_
#define PLAYERINPUT_H_

#include "Input.h"
#include "GamePlayer.h"


namespace ships {

class PlayerInput : public Input {
	typedef MsgHandlerType::HandlerType HandlerType;
	typedef std::shared_ptr<GamePlayer> PlayerPtr;

public:
	PlayerInput(MsgHandlerPtr msgHandler);
	~PlayerInput() = default;

	bool registerAddShipMethod(HandlerType handler);
	void setGamePlayer(PlayerPtr player);
};

} /* namespace ships */

#endif /* PLAYERINPUT_H_ */
