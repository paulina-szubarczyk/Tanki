/*
 * Player.h
 *
 *  Created on: May 10, 2014
 *      Author: Adam Kosiorek
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>

namespace ships {

class Connection {};

class Player {
public:
	Player();
	virtual ~Player();

	void addConnection(Connection connection) { connections_.push_back(connection);};
	const std::vector<Connection>& getConnections() const { return connections_;};

private:
	std::vector<Connection> connections_;
};

} /* namespace ships */

#endif /* PLAYER_H_ */
