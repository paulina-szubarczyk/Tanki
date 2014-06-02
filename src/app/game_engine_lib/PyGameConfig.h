/*
 * PyGameConfig.h
 *
 *  Created on: Jun 2, 2014
 *      Author: Adam Kosiorek
 */

#ifndef PYGAMECONFIG_H_
#define PYGAMECONFIG_H_

#include "IGameConfig.h"

namespace game {

class PyGameConfig : public IGameConfig {
public:
	PyGameConfig(const std::string& filename, const std::string& funcName);
	virtual ~PyGameConfig();

	virtual std::map<std::string, std::string> getConfiguration() const;
};

} /* namespace ships */

#endif /* PYGAMECONFIG_H_ */
