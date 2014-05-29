/*
 * GameWindow.cpp
 *
 *  Created on: May 18, 2014
 *      Author: klis
 */

#include "GameWindow.h"

GameWindow& GameWindow::getInstance(){
	static GameWindow instance;
	return instance;
}

GameWindow::GameWindow(){
	init();
}

void GameWindow::init(){
	grid1_.init(10);
	grid2_.init(10);
	pickedX_=-1;
	pickedY_=-1;
	ipBuffer_ = "Set IP";
	horizontal_= 0;

	for(int i=1; i<6; i++)
		shipsQuantity_.insert(std::pair<int,int>(i,i+1));
}

void GameWindow::mouseFunc1(int button, int state, int x, int y){
	mouseFunc(button, state, x, y, grid1_, pickedX_, pickedY_);
}

void GameWindow::mouseFunc2(int button, int state, int x, int y){
	mouseFunc(button, state, x, y, grid2_, pickedX_, pickedY_);
}

void GameWindow::display1(){
	display(grid1_);
}

void GameWindow::display2(){
	display(grid2_);
}

void GameWindow::displayWrapper1(){
	getInstance().display1();
}

void GameWindow::displayWrapper2(){
	getInstance().display2();
}

void GameWindow::reshapeWrapper(int w, int h){
	getInstance().reshape(w,h);
}

void GameWindow::mouseFuncWrapper1(int button, int state, int x, int y){
	getInstance().mouseFunc1(button, state, x, y);
}

void GameWindow::mouseFuncWrapper2(int button, int state, int x, int y){
	getInstance().mouseFunc2(button, state, x, y);
}

void GameWindow::idleWrapper(){
	getInstance().myGlutIdle();
}
void GameWindow::myGlutIdle(){
	if(glutGetWindow() != mainWindow_)
		glutSetWindow(mainWindow_);
	glutPostRedisplay();
}

void GameWindow::initMyGlut(){
	//Glut & main window init

		glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize (1100, 500);
		glutInitWindowPosition (100, 100);

		mainWindow_ = glutCreateWindow ("GRID");
		glClearColor (0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();

		//subwindows & Glut functions
		int subWindowWidth = 500;
		int subWindowHeight = 500;
		int subw = glutCreateSubWindow (mainWindow_, 0, 0, subWindowWidth, subWindowHeight);
		glutMouseFunc (mouseFuncWrapper1);
		glutReshapeFunc (reshapeWrapper);
		glutDisplayFunc(displayWrapper1);
		int subw2 = glutCreateSubWindow (mainWindow_, subWindowWidth + 100, 0, subWindowWidth, subWindowHeight);
		glutMouseFunc (mouseFuncWrapper2);
		glutReshapeFunc (reshapeWrapper);
		glutDisplayFunc(displayWrapper2);
}
void GameWindow::createGLUI(){

setGlui(GLUI_Master.create_glui( "Control Panel", 0, glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_Y)));


//Connect to server
		GLUI_Rollout* serverRollout = getGlui()->add_rollout("Server");
		GLUI_EditText* serverIP = getGlui()->add_edittext_to_panel(serverRollout,"Server IP: ", GLUI_EDITTEXT_TEXT, &ipBuffer_);
		serverIP->set_w(180);
		serverIP->set_text(ipBuffer_);
		getGlui()->add_button_to_panel(serverRollout,"Connect");

		//Picked Coordinates Display
		GLUI_Panel* pickedPanel = getGlui()->add_panel("Picked Coordinates");
		GLUI_EditText* xCoordinate = getGlui()->add_edittext_to_panel(pickedPanel,"X coordinate: ", GLUI_EDITTEXT_INT, &pickedX_);
		GLUI_EditText* yCoordinate = getGlui()->add_edittext_to_panel(pickedPanel,"Y coordinate: ", GLUI_EDITTEXT_INT, &pickedY_);

		//Add ship
		GLUI_Rollout* shipAdd = getGlui()->add_rollout("Add ship");
		GLUI_Spinner* shipSize = getGlui()->add_spinner_to_panel(shipAdd,"Ship Size",GLUI_SPINNER_INT, &shipSize_);
		GLUI_Listbox* orientationList = getGlui()->add_listbox_to_panel(shipAdd, "Orientation", &horizontal_);
		orientationList->add_item(0, "Horizontal");
		orientationList->add_item(1, "Vertical");
		shipSize->set_int_limits(shipsQuantity_.begin()->first,shipsQuantity_.rbegin()->first);
		GLUI_Panel* remainingPanel = getGlui()->add_panel_to_panel(shipAdd, "Remaining to add");
		getGlui()->add_button_to_panel(shipAdd,"Add");

		//Hit picked coordinates
		GLUI_Panel* hitPanel = getGlui()->add_panel("Hit");
		getGlui()->add_button_to_panel(hitPanel,"Hit");

		getGlui()->add_button("Start Game");
		getGlui()->add_button("Quit", 0, (GLUI_Update_CB)exit);
		getGlui()->set_main_gfx_window(mainWindow_);
		GLUI_Master.set_glutIdleFunc(idleWrapper);
}
void GameWindow::startGameWindow(int argc, char *argv[]){

	glutInit(&argc, argv);
	initMyGlut();
	createGLUI();
	glutMainLoop();
}
