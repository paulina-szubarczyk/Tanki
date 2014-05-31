/*
 * Connection.h
 *
 *  Created on: May 31, 2014
 *      Author: klis
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_


class Connection{
public:
	int getGridSize(){}; // returns grid size
	/*
	 * Returns map:
	 * first is ship size
	 * second is quantity of ships for each ship size
	 */
	std::map<int,int> getShipsConfig(){};
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
	void sendHit(std::pair<int,int> hitCoordinates){}; //send hit to server

	bool getHitReply(){return true;}; //get reply for hit from server

};

#endif /* CONNECTION_H_ */
