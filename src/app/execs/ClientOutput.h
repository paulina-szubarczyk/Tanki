/*
 * ClientOutput.h
 *
 *  Created on: Jun 1, 2014
 *      Author: Adam Kosiorek
 */

#ifndef CLIENTOUTPUT_H_
#define CLIENTOUTPUT_H_

#include "IOutput.h"
#include "ClientConnection.h"

class ClientOutput: public IOutput, public ClientConnection {
public:
	ClientOutput(ConnectionPtr connection);
	virtual ~ClientOutput() = default;

	void connect(std::string serverIP, unsigned short port);
	void sendShip(std::vector<std::vector<std::pair<int,int>>> shipVec);
	void sendHit(std::pair<int,int> hitCoordinates);
};

#endif /* CLIENTOUTPUT_H_ */
