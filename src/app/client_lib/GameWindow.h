/*
 * GameWindow.h
 *
 *  Created on: May 18, 2014
 *      Author: klis
 */

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include "Grid.h"
#include "Drawable.h"

#include <GL/glut.h>
/*
 * Class using Signleton pattern, because there can be only one window to
 * display game content
 *
 */

class GameWindow: public Grid{
public:
	static GameWindow& getInstance();


protected:
	virtual void init();
	virtual void display(Grid grid);
	virtual void reshape(int w, int h);
	virtual void mouseFunc(int button, int state, int x, int y);

	virtual void drawSquares(GLenum mode, Grid grid);
	virtual void startGameWindow(int argc, char *argv[]);

	static void displayWrapper();
	static void reshapeWrapper();
	static void mouseFunc();

private:
	GameWindow();
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;

	Grid grid1_;
	Grid grid2_;

};
#endif /* GAMEWINDOW_H_ */
