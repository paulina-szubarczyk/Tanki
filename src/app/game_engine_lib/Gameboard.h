/*
 * Gameboard.h
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include "Field.h"

class Gameboard {
public:
	Gameboard();
	Gameboard(std::size_t size);
	virtual ~Gameboard();

	std::size_t getSize() const;
	void hit(std::array<int,2> field);
	Field& getField(int position);
	Field& getField(int position1, int position2);

private:

	int countPosition(int position1, int positon2);
	std::vector<Field> fields_;
};

#endif /* GAMEBOARD_H_ */
