/*
 * PlayerInput.h
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#ifndef PLAYERINPUT_H_
#define PLAYERINPUT_H_

#include "IInput.h"
#include "game_engine_lib/IPlayerInput.h"

#include <vector>

using namespace game;

class PlayerInput : public IInput, public IPlayerInput {
public:
	PlayerInput(MsgHandlerPtr msgHandler);
	~PlayerInput() = default;

	virtual void registerAddShipMethod(AddShipHandlerType handler) override;
	virtual void setGamePlayer(PlayerPtr player) override;

private:
	PlayerPtr player_;
};

#endif /* PLAYERINPUT_H_ */
