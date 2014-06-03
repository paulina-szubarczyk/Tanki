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

class PyGameConfig: public IGameConfig {
public:
	PyGameConfig(const std::string& filename);
	virtual ~PyGameConfig();

	virtual int getGameboardSize() const;
	virtual std::map<int, int> getShipConfig() const;

private:
	static const std::string shipConfigFunName_;
	static const std::string gameboardSizeFunName_;
};

} /* namespace game */

#endif /* PYGAMECONFIG_H_ */
