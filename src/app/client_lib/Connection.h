/*
 * Connection.h
 *
 *  Created on: May 31, 2014
 *      Author: klis
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_
#include <map>
#include <vector>

class Connection{
public:
	int getGridSize(){return 10;}; // returns grid size
	/*
	 * Returns map:
	 * first is ship size
	 * second is quantity of ships for each ship size
	 */
	std::map<int,int>& getShipsConfig(){};
	void connect(std::string serverIP){}; //connect to server
	/*
	 * Send ship to server:
	 * ship is vector of <int,int> pairs where:
	 * first is X coordinate
	 * second is Y coordinate
	 */
	void sendShip(std::vector<std::pair<int,int> > ship){};
	/*
	 * Send hit to server
	 * Hit is a <int,int> pair where
	 * first is X coordinate
	 * second is Y coordinate
	 */
	void sendHit(std::pair<int,int> hitCoordinates){}; //send hit to server, arg is pair of XY coordinates

	/*
	 * hit coordinates are already in client
	 * if you want to send them back change this method so it returns
	 * std::pair<std::pair<int,int>,bool> (Coordinates, hitResult)
	 */
	bool getHitReply(){return true;}; //get reply for hit from server whether a ship was hit (true) or not (false)
	/*
	 * Check if player can make a move (true) or if it's opponent's turn
	 */
	bool getTurn(){return true;}
	/*
	 * Sends info that player has clicked "Start" and he's ready for the game
	 */
	bool sendStart(){};
};

#endif /* CONNECTION_H_ */
