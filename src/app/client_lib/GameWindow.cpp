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
}

void GameWindow::drawSquares(GLenum mode, Grid& grid) //draw grid
{
   GLuint i, j;
   for (i = 0; i < 10; i++) { //change 10 to gridSize()
      if (mode == GL_SELECT)
         glLoadName (i);
      for (j = 0; j < 10; j ++) {
         if (mode == GL_SELECT)
            glPushName (j);

         //draw filled squares
         glPolygonMode(GL_FRONT,GL_FILL);
         glColor3f ((GLfloat) grid.getGrid()[i][j]->getRed(), (GLfloat) grid.getGrid()[i][j]->getGreen(), (GLfloat) grid.getGrid()[i][j]->getBlue());
         glRecti (i, j, i+1, j+1);

         //draw black lines
         glPolygonMode(GL_FRONT,GL_LINE);
         glColor3f(0.0,0.0,0.0);
         glRecti (i, j, i+1, j+1);
         if (mode == GL_SELECT)
            glPopName ();
      }
   }
}

void GameWindow::mouseFunc(int button, int state, int x, int y, Grid& grid)
{
	int BUFSIZE = 512;
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];

   if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
      return;

   glGetIntegerv (GL_VIEWPORT, viewport);

   glSelectBuffer (BUFSIZE, selectBuf);
   (void) glRenderMode (GL_SELECT);

   glInitNames();
   glPushName(0);

   glMatrixMode (GL_PROJECTION);
   glPushMatrix ();
   glLoadIdentity ();

/*  create picking region near cursor location      */
   gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                  0.1, 0.1, viewport);
   gluOrtho2D (0.0, 10.0, 0.0, 10.0);
   drawSquares(GL_SELECT, grid);

   glMatrixMode (GL_PROJECTION);
   glPopMatrix ();
   glFlush ();

   hits = glRenderMode (GL_RENDER);
   processHits (hits, selectBuf, grid);
   glutPostRedisplay();
}

void GameWindow::mouseFunc1(int button, int state, int x, int y){
	mouseFunc(button, state, x, y, grid1_);
}

void GameWindow::mouseFunc2(int button, int state, int x, int y){
	mouseFunc(button, state, x, y, grid2_);
}

void GameWindow::display(Grid& grid){
	glClear(GL_COLOR_BUFFER_BIT);
	drawSquares (GL_RENDER, grid);
	glFlush();
}

void GameWindow::display1(){
	display(grid1_);
}

void GameWindow::display2(){
	display(grid2_);
}

void GameWindow::reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0, 10.0, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GameWindow::processHits(GLint hits, GLuint buffer[],Grid& grid){
	 unsigned int i, j;
	   GLuint ii, jj, names, *ptr;

	   printf ("hits = %d\n", hits);
	   ptr = (GLuint *) buffer;
	   for (i = 0; i < hits; i++) { /*  for each hit  */
	      names = *ptr;
	      ptr+=3;
//	      printf (" number of names for this hit = %d\n", names);
//	         ptr++;
//	      printf("  z1 is %g;", (float) *ptr/0x7fffffff); ptr++;
//	      printf(" z2 is %g\n", (float) *ptr/0x7fffffff); ptr++;
//	      printf ("   names are ");
	      for (j = 0; j < names; j++) { /*  for each name */
	         printf ("%d ", *ptr);
	         if (j == 0)  /*  set row and column  */
	            ii = *ptr;
	         else if (j == 1)
	            jj = *ptr;
	         ptr++;
	      }
	      printf ("\n");

	      grid.getGrid()[ii][jj]->setColor(1.0,0.0,0.0);
	      pickedX_=++ii;
	      pickedY_=++jj;
	      glui_->sync_live();
}
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
	glui_ = GLUI_Master.create_glui( "Control Panel", 0, glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_Y));

		//Connect to server
		GLUI_Rollout* serverRollout = glui_->add_rollout("Server");
		GLUI_EditText* serverIP = glui_->add_edittext_to_panel(serverRollout,"Server IP: ");
		serverIP->set_w(180);
		glui_->add_button_to_panel(serverRollout,"Connect");

		//Add ship
		GLUI_Rollout* shipAdd = glui_->add_rollout("Add ship");
		GLUI_Spinner* shipSize = glui_->add_spinner_to_panel(shipAdd,"Ship Size");
		GLUI_Listbox* orientationList = glui_->add_listbox_to_panel(shipAdd, "Orientation");
		orientationList->add_item(0, "Horizontal");
		orientationList->add_item(1, "Vertical");
		shipSize->set_int_limits(1,5);
		GLUI_Panel* remainingPanel = glui_->add_panel_to_panel(shipAdd, "Remaining to add");
		GLUI_Panel* hitPanel = glui_->add_panel("Hit");

		//Hit picked coordinates
		GLUI_EditText* xCoordinate = glui_->add_edittext_to_panel(hitPanel,"X coordinate: ", GLUI_EDITTEXT_INT, &pickedX_);
		GLUI_EditText* yCoordinate = glui_->add_edittext_to_panel(hitPanel,"Y coordinate: ", GLUI_EDITTEXT_INT, &pickedY_);
		glui_->add_button_to_panel(hitPanel,"Hit");

		glui_->add_button("Start Game");
		glui_->add_button("Quit", 0, (GLUI_Update_CB)exit);
		glui_->set_main_gfx_window(mainWindow_);
		GLUI_Master.set_glutIdleFunc(idleWrapper);
}
void GameWindow::startGameWindow(int argc, char *argv[]){

	glutInit(&argc, argv);
	initMyGlut();
	createGLUI();
	glutMainLoop();
}
