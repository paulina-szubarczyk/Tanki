/*
 * Field.h
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */

#ifndef FIELD_H_
#define FIELD_H_

class Field {
public:
	Field();
	~Field();
	int getPosition() const  {
		return position_;
	}
	void setPoisiton(int position){
		position_ = position;
	}
private:
	int position_;
};
inline bool operator<(const Field &f1, const Field &f2){
	return f1.getPosition() < f2.getPosition();
}

#endif /* FIELD_H_ */
