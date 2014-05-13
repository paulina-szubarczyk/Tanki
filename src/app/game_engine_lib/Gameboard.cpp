/*
 * Gameboard.cpp
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#include "Gameboard.h"
#include <iostream>
#include <vector>
Gameboard::Gameboard() {
	// TODO Auto-generated constructor stub

}

Gameboard::~Gameboard() {
	// TODO Auto-generated destructor stub
}

Gameboard::Gameboard(std::size_t size) {
	size_ = size;
	for (int i = 0; i < size ; ++i)
		for (int j = 0; j < size ; ++j) {
			Field field(countPosition(i,j));
			fields_.push_back(field);
		}
//	print();
}
void Gameboard::print() {
	std::vector<Field>::const_iterator it = fields_.begin();
	for(; it != fields_.end(); ++it)
		std::cout << it->getPosition() << " ";
}

std::size_t Gameboard::getSize() const {
	return fields_.size();
}

int Gameboard::countPosition(int i, int j){
	return i * size_ + j + 1;
}

void Gameboard::hit(int positon1, int positon2) {
	fields_[countPosition(positon1, positon2)].hit();
}

Field& Gameboard::getField(int position) {
	return fields_[position];
}

Field& Gameboard::getField(int position1, int position2) {
	return fields_[countPosition(position1, position2)];
}
