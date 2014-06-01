/*
 * PlayerInput.h
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#ifndef PLAYERINPUT_H_
#define PLAYERINPUT_H_

#include "Input.h"

#include <vector>

class GamePlayer;


namespace ships {

class PlayerInput : public Input {
	typedef std::shared_ptr<GamePlayer> PlayerPtr;
	typedef std::vector<std::vector<int>> ShipVec;
	typedef std::function<void(PlayerPtr,const ShipVec&, const ShipVec&)>  AddShipHandlerType;;

public:
	PlayerInput(MsgHandlerPtr msgHandler);
	~PlayerInput() = default;

	bool registerAddShipMethod(PlayerPtr player, AddShipHandlerType handler);
	void setGamePlayer(PlayerPtr player);
};

} /* namespace ships */

#endif /* PLAYERINPUT_H_ */
