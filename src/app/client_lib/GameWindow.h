/*
 * GameWindow.h
 *
 *  Created on: May 18, 2014
 *      Author: klis
 */

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include "Grid.h"
#include "GlutFunctions.h"
#include "GameManager.h"
#include "Connection.h"
#include <map>
#include <string>

/*
 * Class using Signleton pattern, because there can be only one window to
 * display game content
 *
 */

class GameWindow: public GlutFunctions{
public:
	static GameWindow& getInstance();

	void init();

	void display1();
	void display2();

	void myGlutIdle();

	void mouseFunc1(int button, int state, int x, int y);
	void mouseFunc2(int button, int state, int x, int y);

	void initMyGlut();
	void createGLUI();
	void startGameWindow(int argc, char *argv[]);

	static void displayWrapper1();
	static void displayWrapper2();
	static void idleWrapper();
	static void reshapeWrapper(int w, int h);
	static void mouseFuncWrapper1(int button, int state, int x, int y);
	static void mouseFuncWrapper2(int button, int state, int x, int y);

	GameManager& getManager();

	static void addCallbackWrapper(int);
	void addCallback();
	static void hitCallbackWrapper(int);
	void hitCallback();
	void startCallback();
	void connectCallback(int);

private:
	GameWindow();
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;

	Grid grid1_;
	Grid grid2_;

	int mainWindow_;
	int subW1_;
	int subW2_;
	int selectedW_;

	int pickedX_;
	int pickedY_;

	int shipSize_;
	int horizontal_;

	GameManager manager_;
	GLUI_String ipBuffer_;
	std::shared_ptr<Connection> connector_;
	//std::string shipsToAdd_;

};
#endif /* GAMEWINDOW_H_ */
