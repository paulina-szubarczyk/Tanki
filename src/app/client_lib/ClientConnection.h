/*
 * ClientConnection.h
 *
 *  Created on: May 31, 2014
 *      Author: klis
 */

#ifndef CLIENTCONNECTION_H_
#define CLIENTCONNECTION_H_

#include <map>
#include <vector>

class GameWindow;

class ClientConnection {
public:
	ClientConnection() = default;
	virtual ~ClientConnection() = default;

	/*
	 * hit coordinates are already in client
	 * if you want to send them back change this method so it returns
	 * std::pair<std::pair<int,int>,bool> (Coordinates, hitResult)
	 */
	void setHitReply(int x, int y, bool result); //set reply for hit depending on whether a ship was hit (true) or missed (false)

	/*
	 * Allow server to set player's turn
	 */
	void setTurn(bool turn);

	/*
	 * Allow server to set size of grid in GameManager
	 */
	void setGridSize(int n);

	/*
	 * Allow server to set ships configuration in GameManager
	 */

	void setShipsConfig(std::map<int,int>& config);

	/*
	 * Connect to the server
	 */
	virtual void connect(std::string serverIP, unsigned short port) = 0;

	/*
	 * Send ship to server:
	 * ship is vector of <int,int> pairs where:
	 * first is X coordinate
	 * second is Y coordinate
	 */

	virtual void sendShip(std::vector<std::vector<std::pair<int,int>>> ship) = 0;


	virtual void sendHit(std::pair<int,int> hitCoordinates) = 0; //send hit to server, arg is pair of XY coordinates
};

#endif /* CLIENTCONNECTION_H_ */
