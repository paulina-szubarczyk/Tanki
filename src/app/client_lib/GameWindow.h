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
#include "ClientConnection.h"
#include <glog/logging.h>
#include <exception>
#include <map>
#include <string>

/*
 * Class using Signleton pattern, because there can be only one window to
 * display game content
 *
 */

class GameWindow: public GlutFunctions {
public:
	/*
	 * Singletone
	 */
	static GameWindow& getInstance();

	void init(std::shared_ptr<ClientConnection> connection);

	void display1();
	void display2();

	void myGlutIdle();

	void mouseLeftBtnGrid1(int button, int state, int x, int y);
	void mouseLeftBtnGrid2(int button, int state, int x, int y);
	void initMyGlut();
	void createGLUI();
	void startGameWindow(int argc, char *argv[]);

	static void displayWrapper1();
	static void displayWrapper2();
	static void idleWrapper();
	static void reshapeWrapper(int w, int h);
	static void mouseLeftBtnGrid1Wrapper(int button, int state, int x, int y);
	static void mouseLeftBtnGrid2Wrapper(int button, int state, int x, int y);

	std::shared_ptr<GameManager> getManager();

	static void addCallbackWrapper(int);
	void addCallback();
	static void hitCallbackWrapper(int);
	void hitCallback();
	static void startCallbackWrapper(int);
	void startCallback();
	static void connectCallbackWrapper(int);
	void connectCallback();
	static void sizeChangeCallbackWrapper(int);
	void sizeChangeCallback();
	std::shared_ptr<ClientConnection> getConnector(){return connector_;}

	/*
	 * Methods for the server to control the gameplay
	 */

	/*
	 * If turn is true enables player to hit, otherwise disables the 'Hit" button
	 */
	void setPlayerTurn(bool turn);
	void setHitResult(int x, int y, bool result);
	/*
	 * Displays info about the end of the game
	 */
	void endGame();

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
	GLUI_EditText* remaining_;
	GLUI_Button* hitButton_;
	GLUI_Button* addButton_;
	int pickedX_;
	int pickedY_;

	int shipSize_;
	int horizontal_;

	std::shared_ptr<GameManager> manager_;
	GLUI_String ipBuffer_;
	std::shared_ptr<ClientConnection> connector_;

	unsigned short port_;

};
#endif /* GAMEWINDOW_H_ */
