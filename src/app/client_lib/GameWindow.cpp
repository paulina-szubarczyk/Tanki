/*
 * GameWindow.cpp
 *
 *  Created on: May 18, 2014
 *      Author: klis
 */

#include "GameWindow.h"

GameWindow& GameWindow::getInstance() {
	static GameWindow instance;
	return instance;
}

GameWindow::GameWindow() {
}

void GameWindow::init(std::shared_ptr<ClientConnection> connection) {
	grid1_.init(manager_.getGridSize());
	grid2_.init(manager_.getGridSize());
	pickedX_ = 0;
	pickedY_ = 0;

	ipBuffer_ = "Set IP";
	horizontal_ = 0;
	shipSize_ = manager_.getSmallestSize();

	connector_ = connection;
}

GameManager& GameWindow::getManager() {
	return manager_;
}

void GameWindow::mouseLeftBtnGrid1(int button, int state, int x, int y) {
	mouseFunc(button, state, x, y, grid1_, pickedX_, pickedY_);
}

void GameWindow::mouseLeftBtnGrid2(int button, int state, int x, int y) {
	mouseFunc(button, state, x, y, grid2_, pickedX_, pickedY_);
}

void GameWindow::display1() {
	display(grid1_);
}

void GameWindow::display2() {
	display(grid2_);
}

void GameWindow::displayWrapper1() {
	getInstance().display1();
}

void GameWindow::displayWrapper2() {
	getInstance().display2();
}

void GameWindow::reshapeWrapper(int w, int h) {
	getInstance().reshape(w, h);
}


void GameWindow::mouseLeftBtnGrid1Wrapper(int button, int state, int x, int y) {
	getInstance().mouseLeftBtnGrid1(button, state, x, y);
}

void GameWindow::mouseLeftBtnGrid2Wrapper(int button, int state, int x, int y) {
	getInstance().mouseLeftBtnGrid2(button, state, x, y);
}

void GameWindow::idleWrapper() {
	getInstance().myGlutIdle();
}
void GameWindow::myGlutIdle() {
	if (glutGetWindow() != selectedW_)
		glutSetWindow(selectedW_);
	glutPostRedisplay();
}

void GameWindow::initMyGlut() {
	//Glut & main window init

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1100, 500);
	glutInitWindowPosition(100, 100);

	mainWindow_ = glutCreateWindow("GRID");
	selectedW_ = mainWindow_;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear (GL_COLOR_BUFFER_BIT);
	glFlush();

	//subwindows & Glut functions
	int subWindowWidth = 500;
	int subWindowHeight = 500;
	subW1_ = glutCreateSubWindow(mainWindow_, 0, 0, subWindowWidth,
			subWindowHeight);
	glutMouseFunc(mouseLeftBtnGrid1Wrapper);
	glutReshapeFunc(reshapeWrapper);
	glutDisplayFunc(displayWrapper1);
	subW2_ = glutCreateSubWindow(mainWindow_, subWindowWidth + 100, 0,
			subWindowWidth, subWindowHeight);
	glutMouseFunc(mouseLeftBtnGrid2Wrapper);
	glutReshapeFunc(reshapeWrapper);
	glutDisplayFunc(displayWrapper2);
}

void GameWindow::addCallbackWrapper(int) {
	getInstance().addCallback();
}
void GameWindow::addCallback() {
	bool notAdded = true;
	if (manager_.getRemainingShips(shipSize_) > 0
			&& grid1_.checkAddSize(pickedX_, pickedY_, shipSize_, horizontal_))
		if (grid1_.checkAvaible(pickedX_, pickedY_, shipSize_, horizontal_)) {
			grid1_.addNewShip(pickedX_, pickedY_, shipSize_, horizontal_);
			notAdded = false;
			manager_.decreaseShipsQuantity(shipSize_);
			sizeChangeCallback();
		}
	if (notAdded)
		grid1_.getGrid()[pickedX_][pickedY_]->setColor(0.0, 0.0, 0.7);

	remaining_->set_int_val(manager_.getRemainingShips(shipSize_));
	selectedW_ = subW1_;
	glutPostRedisplay();
}
void GameWindow::hitCallbackWrapper(int) {
	getInstance().hitCallback();
}

void GameWindow::hitCallback() {
	connector_->sendHit(std::pair<int, int>(pickedX_, pickedY_));
//setTurn(connector_->getTurn());
//grid2_.getGrid()[pickedX_][pickedY_]->registerHitReply(true); //test
		selectedW_ = subW2_;
		glutPostRedisplay();


}
void GameWindow::connectCallbackWrapper(int){
	getInstance().connectCallback();
}


void GameWindow::connectCallback(){
	connector_->connect(ipBuffer_, port_);
}

void GameWindow::sizeChangeCallbackWrapper(int) {
	getInstance().sizeChangeCallback();
}

void GameWindow::sizeChangeCallback() {
	remaining_->set_int_val(manager_.getRemainingShips(shipSize_));
}

void GameWindow::startCallbackWrapper(int) {
	getInstance().startCallback();
}

void GameWindow::startCallback() {
	//if (manager_.checkReady()) {
		connector_->sendShip(grid1_.getShips());
	//}
}
void GameWindow::createGLUI() {

	setGlui(
			GLUI_Master.create_glui("Control Panel", 0,
					glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH),
					glutGet(GLUT_WINDOW_Y)));

	//Connect to server
	GLUI_Rollout* serverRollout = getGlui()->add_rollout("Server");
	GLUI_EditText* serverIP = getGlui()->add_edittext_to_panel(serverRollout,
			"Server IP: ", ipBuffer_);
	serverIP->set_w(180);
	serverIP->set_text(ipBuffer_);
	getGlui()->add_button_to_panel(serverRollout, "Connect", 0, connectCallbackWrapper);


	//Picked Coordinates Display
	GLUI_Panel* pickedPanel = getGlui()->add_panel("Picked Coordinates");
	GLUI_EditText* xCoordinate = getGlui()->add_edittext_to_panel(pickedPanel,
			"X coordinate: ", GLUI_EDITTEXT_INT, &pickedX_);
	GLUI_EditText* yCoordinate = getGlui()->add_edittext_to_panel(pickedPanel,
			"Y coordinate: ", GLUI_EDITTEXT_INT, &pickedY_);

	/*
	 * Add ship rollout
	 */
	GLUI_Rollout* shipAdd = getGlui()->add_rollout("Add ship");
	remaining_ = getGlui()->add_edittext_to_panel(shipAdd, "Remaining");
	sizeChangeCallback();
	GLUI_Listbox* shipSize = getGlui()->add_listbox_to_panel(shipAdd,
			"Ship Size", &shipSize_, 0, sizeChangeCallbackWrapper);

	/*
	 * Creating list of ships' sizes
	 */
	std::map<int, int>::iterator it;
	it = getManager().getShipsQuantity().begin();
	for (it; it != getManager().getShipsQuantity().end(); it++) {
		std::string s = std::to_string(it->first);
		const char* name = s.c_str();
		shipSize->add_item(it->first, name);
	}

	GLUI_Listbox* orientationList = getGlui()->add_listbox_to_panel(shipAdd,
			"Orientation", &horizontal_);
	orientationList->add_item(0, "Horizontal");
	orientationList->add_item(1, "Vertical");
	addButton_ = getGlui()->add_button_to_panel(shipAdd, "Add", 0,
			addCallbackWrapper);

	//Hit picked coordinates
	GLUI_Panel* hitPanel = getGlui()->add_panel("Hit");
	hitButton_ = getGlui()->add_button_to_panel(hitPanel, "Hit", 0,
			hitCallbackWrapper);
	hitButton_->disable();
	getGlui()->add_button("Start Game", 0, startCallbackWrapper);
	getGlui()->add_button("Quit", 0, (GLUI_Update_CB) exit);
	getGlui()->set_main_gfx_window(mainWindow_);
	GLUI_Master.set_glutIdleFunc(idleWrapper);
}

void GameWindow::endGame() {
	remaining_->set_text("END");
}

void GameWindow::setHitResult(int x, int y, bool result) {
	grid2_.getGrid()[x][y]->registerHitReply(result);
}

void GameWindow::setPlayerTurn(bool turn) {
	if (turn) {
		hitButton_->enable();
	} else
		hitButton_->disable();
}
void GameWindow::startGameWindow(int argc, char *argv[]) {

	port_ = atoi(argv[1]);
	glutInit(&argc, argv);
	initMyGlut();
	createGLUI();
	glutMainLoop();
}
