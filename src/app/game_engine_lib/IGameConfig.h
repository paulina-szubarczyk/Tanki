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

namespace ships {

struct IGameConfig {
	IGameConfig() = default;
	virtual ~IGameConfig() = default;

	virtual std::map<std::string, std::string> getConfiguration() const = 0;
};

} /* namespace ships */

#endif /* IGAMECONFIG_H_ */
