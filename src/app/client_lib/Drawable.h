/*
 * Drawable.h
 *
 *  Created on: May 17, 2014
 *      Author: klis
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

class Drawable{
public:
	virtual ~Drawable();
	virtual void draw() = 0;
};


#endif /* DRAWABLE_H_ */
