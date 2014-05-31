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
	ipBuffer_ = "Set IP1";
	horizontal_= 0;

}

GameManager& GameWindow::getManager(){
	return manager_;
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
	if(glutGetWindow() != selectedW_)
		glutSetWindow(selectedW_);
	glutPostRedisplay();
}

void GameWindow::initMyGlut(){
	//Glut & main window init

		glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize (1100, 500);
		glutInitWindowPosition (100, 100);

		mainWindow_ = glutCreateWindow ("GRID");
		selectedW_ = mainWindow_;
		glClearColor (0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();

		//subwindows & Glut functions
		int subWindowWidth = 500;
		int subWindowHeight = 500;
		subW1_ = glutCreateSubWindow (mainWindow_, 0, 0, subWindowWidth, subWindowHeight);
		glutMouseFunc (mouseFuncWrapper1);
		glutReshapeFunc (reshapeWrapper);
		glutDisplayFunc(displayWrapper1);
		subW2_ = glutCreateSubWindow (mainWindow_, subWindowWidth + 100, 0, subWindowWidth, subWindowHeight);
		glutMouseFunc (mouseFuncWrapper2);
		glutReshapeFunc (reshapeWrapper);
		glutDisplayFunc(displayWrapper2);
}

void GameWindow::addCallbackWrapper(int){
	getInstance().addCallback();
}
void GameWindow::addCallback(){
	if(grid1_.checkAddSize(pickedX_,pickedY_,shipSize_,horizontal_))
	grid1_.addNewShip(pickedX_,pickedY_,shipSize_,horizontal_);
	//std::cout<<pickedX_<<" "<<pickedY_<<" "<<shipSize_<<" "<<horizontal_<<"\n";
	selectedW_ = subW1_;
	//grid1_.getGrid()[pickedX_][pickedY_]->setToShip();
	glutPostRedisplay();
}
void callback(int arg){}
void GameWindow::createGLUI(){

setGlui(GLUI_Master.create_glui( "Control Panel", 0, glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_Y)));


		//Connect to server
		GLUI_Rollout* serverRollout = getGlui()->add_rollout("Server");
		GLUI_EditText* serverIP = getGlui()->add_edittext_to_panel(serverRollout,"Server IP: ", ipBuffer_);
		serverIP->set_w(180);
		serverIP->set_text(ipBuffer_); //causes segfault?!
		getGlui()->add_button_to_panel(serverRollout,"Connect");

		//Picked Coordinates Display
		GLUI_Panel* pickedPanel = getGlui()->add_panel("Picked Coordinates");
		GLUI_EditText* xCoordinate = getGlui()->add_edittext_to_panel(pickedPanel,"X coordinate: ", GLUI_EDITTEXT_INT, &pickedX_);
		GLUI_EditText* yCoordinate = getGlui()->add_edittext_to_panel(pickedPanel,"Y coordinate: ", GLUI_EDITTEXT_INT, &pickedY_);

		/*
		 * Add ship rollout
		 */
		GLUI_Rollout* shipAdd = getGlui()->add_rollout("Add ship");
		GLUI_Listbox* shipSize = getGlui()->add_listbox_to_panel(shipAdd,"Ship Size", &shipSize_);

		/*
		 * Creating list of ships' sizes
		 */
		std::map<int,int>::iterator it;
		it = getManager().getShipsQuantity().begin();
		for(it;it != getManager().getShipsQuantity().end();it++){
			std::string s = std::to_string(it->first);
			const char* name = s.c_str();
			shipSize->add_item(it->first, name);
		}

		GLUI_Listbox* orientationList = getGlui()->add_listbox_to_panel(shipAdd, "Orientation", &horizontal_);
		orientationList->add_item(0, "Horizontal");
		orientationList->add_item(1, "Vertical");
		GLUI_Panel* remainingPanel = getGlui()->add_panel_to_panel(shipAdd, "Remaining to add");
		getGlui()->add_statictext_to_panel(remainingPanel, "Size | Quantity");
		GLUI_EditText* remaining = getGlui()->add_edittext_to_panel(remainingPanel, "Remaining");
		//remaining->set_text(shipsToAdd_);
		getGlui()->add_button_to_panel(shipAdd,"Add",0,addCallbackWrapper);

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
