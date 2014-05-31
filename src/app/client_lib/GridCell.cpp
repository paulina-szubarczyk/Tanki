/*
 * GridCell.cpp
 *
 *  Created on: May 15, 2014
 *      Author: klis
 */
#include "GridCell.h"

GridCell::GridCell() {
	r_ = g_ = b_ = 0.0;
	x_ = y_ = 0;
	occupied_ = false;
	alreadyHit_ = false;
}

GridCell::GridCell(float red, float green, float blue, int x, int y) {
	setColor(red, green, blue);
	setCoordinates(x, y);
	occupied_ = false;
}

void GridCell::setColor(float red, float green, float blue) {
	if (red > 1.0)
		red = 1.0;
	else if (red < 0.0)
		red = 0.0;
	if (green > 1.0)
		green = 1.0;
	else if (green < 0.0)
		green = 0.0;
	if (blue > 1.0)
		blue = 1.0;
	else if (blue < 0.0)
		blue = 0.0;
	r_ = red;
	g_ = green;
	b_ = blue;
}

void GridCell::setCoordinates(int x, int y) {
	x_ = x;
	y_ = y;
}

int GridCell::getX() {
	return x_;
}

int GridCell::getY() {
	return y_;
}
float GridCell::getRed() {
	return r_;
}

float GridCell::getGreen() {
	return g_;
}

float GridCell::getBlue() {
	return b_;
}

bool GridCell::getOccupied() {
	return occupied_;
}

void GridCell::setOccupied(bool state) {
	occupied_ = state;
}

bool GridCell::setToShip() {
	if (!occupied_) {
		setColor(0.0, 1.0, 0.0);
		occupied_ = true;
		return true;
	}
	return false;
}

bool GridCell::hitCell() {
	if (occupied_ && !alreadyHit_) {
		setColor(1.0, 0.0, 0.0);
		alreadyHit_ = true;
		return true;
	} else if (!occupied_)
		setColor(1.0, 1.0, 1.0);
	return false;
}

bool GridCell::getHitState() {
	return alreadyHit_;
}

void GridCell::registerHitReply(bool reply) {
	if (reply) {
		setToShip();
	}
	hitCell();
	alreadyHit_ = true;
}
