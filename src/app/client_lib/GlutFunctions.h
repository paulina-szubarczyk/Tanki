/*
 * GlutFunctions.h
 *
 *  Created on: May 29, 2014
 *      Author: klis
 */

#ifndef GLUTFUNCTIONS_H_
#define GLUTFUNCTIONS_H_

#include "Grid.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <glog/logging.h>
#include <memory>

class GlutFunctions {
public:

	void display(Grid& grid);

	void reshape(int w, int h);

	void mouseFunc(int button, int state, int x, int y, Grid& grid,
			int& pickedX, int& pickedY);
	void drawSquares(GLenum mode, Grid& grid);

	void processHits(GLint hits, GLuint buffer[], Grid& grid, int& pickedX,
			int& pickedY);

	GLUI* getGlui() {
		return glui_;
	}
	void setGlui(GLUI* nglui) {
		glui_ = nglui;
	}

private:
	GLUI* glui_;

};

#endif /* GLUTFUNCTIONS_H_ */
