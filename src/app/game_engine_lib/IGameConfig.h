/*
 * IGameConfig.h
 *
 *  Created on: Jun 2, 2014
 *      Author: Adam Kosiorek
 */

#ifndef IGAMECONFIG_H_
#define IGAMECONFIG_H_

#include <string>
#include <map>

namespace game {

struct IGameConfig {
	IGameConfig() = default;
	virtual ~IGameConfig() = default;

	virtual int getGameboardSize() const = 0;
	virtual std::map<int, int> getShipConfig() const = 0;
};

} /* namespace ships */

#endif /* IGAMECONFIG_H_ */
