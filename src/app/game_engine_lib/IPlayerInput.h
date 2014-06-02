/*
 * IPlayerInput.h
 *
 *  Created on: Jun 2, 2014
 *      Author: Adam Kosiorek
 */

#ifndef IPLAYERINPUT_H_
#define IPLAYERINPUT_H_

namespace game {

class GamePlayer;

class IPlayerInput {
protected:
	typedef std::shared_ptr<game::GamePlayer> PlayerPtr;
	typedef std::vector<std::vector<int>> ShipVec;
	typedef std::function<void(PlayerPtr,const ShipVec&, const ShipVec&)>  AddShipHandlerType;
public:
	IPlayerInput() = default;
	virtual ~IPlayerInput() = default;

	virtual void registerAddShipMethod(AddShipHandlerType handler) = 0;
	virtual void setGamePlayer(PlayerPtr player) = 0;
};

} // namespace game



#endif /* IPLAYERINPUT_H_ */
