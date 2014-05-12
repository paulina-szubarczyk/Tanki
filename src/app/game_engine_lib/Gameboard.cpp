/*
 * Gameboard.cpp
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#include "Gameboard.h"

Gameboard::Gameboard() {
	// TODO Auto-generated constructor stub

}

Gameboard::~Gameboard() {
	// TODO Auto-generated destructor stub
}

Gameboard::Gameboard(std::size_t size) {
	for (int i = 0; i < size ; ++i)
		for (int j = 0; j < size ; ++j) {
			Field field(countPosition(i,j));
			fields_.push_back(field);
		}
}

std::size_t Gameboard::getSize() const {
	return fields_.size();
}

int Gameboard::countPosition(int i, int j){
	return i*fields_.size()+j+1;
}

void Gameboard::hit(std::array<int,2> field) {
	fields_[countPosition(field[0],field[1])].hit();
}

Field& Gameboard::getField(int position) {
	return fields_[position];
}

Field& Gameboard::getField(int position1, int position2) {
	return fields_[countPosition(position1, position2)];
}
