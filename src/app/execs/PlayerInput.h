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

	void registerAddShipMethod(AddShipHandlerType handler);
	void setGamePlayer(PlayerPtr player);

private:
	PlayerPtr player_;
};

} /* namespace ships */

#endif /* PLAYERINPUT_H_ */
