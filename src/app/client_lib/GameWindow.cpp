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

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
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
         glPolygonMode(GL_FRONT,GL_FILL);
         glColor3f ((GLfloat) grid.getGrid()[i][j]->getRed(), (GLfloat) grid.getGrid()[i][j]->getGreen(),
                    (GLfloat) grid.getGrid()[i][j]->getBlue());
         glRecti (i, j, i+1, j+1);
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
/*  create 1x1 pixel picking region near cursor location      */
   gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                  1.0, 1.0, viewport);
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
	drawSquares (GL_RENDER, grid); //will later use bind
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
	      printf (" number of names for this hit = %d\n", names);
	         ptr++;
	      printf("  z1 is %g;", (float) *ptr/0x7fffffff); ptr++;
	      printf(" z2 is %g\n", (float) *ptr/0x7fffffff); ptr++;
	      printf ("   names are ");
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
}
}

void GameWindow::displayWrapper1(){
//	display_callback = func;
//	glutDisplayFunc(GameWindow::displayCallbackFwd);

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

void mouseWork(int a, int b, int, int){}
void GameWindow::startGameWindow(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1100, 500);
	glutInitWindowPosition (100, 100);

	int mainw = glutCreateWindow ("GRID");
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	int subw = glutCreateSubWindow (mainw, 0, 0, 500, 500);
	init();

//	GameWindow& g = getInstance();
//	Grid& grid1ref = grid1_;
	//static boost::function<void (int,int,int,int)> mouseBind1 = boost::bind(&GameWindow::mouseFunc,boost::ref(g),_1, _2, _3, _4, grid1ref);
	//boost::function<void (int,int,int,int)>* mouseBind1 = new boost::function<void (int,int,int,int)>(boost::bind(&GameWindow::mouseFunc,boost::ref(getInstance()),_1, _2, _3, _4, boost::ref(grid1_)));
	//typedef void (* function_t)(int,int,int,int);
	//glutMouseFunc (*mouseBind1.target<function_t>()); //segmentation faul
	glutMouseFunc (mouseFuncWrapper1);
	glutReshapeFunc (reshapeWrapper);
	//typedef void (* function_t2)();
	//boost::function<void ()> displayBind1 = boost::bind(&GameWindow::display,boost::ref(g), grid1ref);
	//glutDisplayFunc(*displayBind1.target<function_t2>()); //segmentation fault
	glutDisplayFunc(displayWrapper1);
	int subw2 = glutCreateSubWindow (mainw, 600, 0, 500, 500);
	glutMouseFunc (mouseFuncWrapper2);
	glutReshapeFunc (reshapeWrapper);
	glutDisplayFunc(displayWrapper2);
	glutMainLoop();
}
