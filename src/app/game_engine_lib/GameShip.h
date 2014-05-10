/*
 * GameShip.h
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */

#ifndef STATEK_H_
#define STATEK_H_

#include <memory>
#include "Field.h"

class GameShip : public AbstractShip {
public:

	GameShip();
	virtual ~GameShip();

	void changeState(std::shared_ptr<Field> field, ShipState state);
	void setField(std::shared_ptr<Field> field);
	std::shared_ptr<Field> getField();

private:
	void updateState();
	std::shared_ptr<Field> field_;
};

#endif /* STATEK_H_ */
