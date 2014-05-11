/*
 * Field.h
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */

#ifndef FIELD_H_
#define FIELD_H_
#include <memory>
class SmallGameShip;
class Field {
public:
	Field();
	Field(int position);
	~Field();
	typedef std::weak_ptr<SmallGameShip> ShipPtr;
	int getPosition() const ;

	void setShip(ShipPtr ship);
	ShipPtr getShip();
private:
	int position_;
	ShipPtr ship_;

};

inline bool operator<(const Field &f1, const Field &f2){
	return f1.getPosition() < f2.getPosition();
}

#endif /* FIELD_H_ */
