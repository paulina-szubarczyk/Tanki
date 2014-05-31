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
	int getGridSize() {
		return 10;
	}
	; // returns grid size
	/*
	 * Allow server to set size of grid in GameManager
	 */
	void setGridSize(int n);
	/*
	 * Returns map:
	 * first is ship size
	 * second is quantity of ships for each ship size
	 */
	std::map<int, int>& getShipsConfig() {
	}
	;
	/*
	 * Allow server to set ships configuration in GameManager
	 */
	void setShipsConfig(std::map<int, int>& config);
	/*
	 * Connect to the server
	 */
	void connect(std::string serverIP) {
	}
	;
	/*
	 * Send ship to server:
	 * ship is vector of <int,int> pairs where:
	 * first is X coordinate
	 * second is Y coordinate
	 */
	void sendShip(std::vector<std::pair<int, int> > ship) {
	}
	;
	/*
	 * Send hit to server
	 * Hit is a <int,int> pair where
	 * first is X coordinate
	 * second is Y coordinate
	 */
	void sendHit(std::pair<int, int> hitCoordinates) {
	}
	; //send hit to server, arg is pair of XY coordinates

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
	 * Sends info that player has clicked "Start" and he's ready for the game
	 */
	void sendStart() {
	}
	;
};

#endif /* CLIENTCONNECTION_H_ */
