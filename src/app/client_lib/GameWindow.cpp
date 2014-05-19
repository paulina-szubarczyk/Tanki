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

void GameWindow::init(){
	grid1_.init(10);
	grid2_.init(10);

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void drawSquares(GLenum mode, Grid grid) //draw grid
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

void GameWindow::mouseFunc(int button, int state, int x, int y)
{
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
   drawSquares (GL_SELECT);

   glMatrixMode (GL_PROJECTION);
   glPopMatrix ();
   glFlush ();

   hits = glRenderMode (GL_RENDER);
   processHits (hits, selectBuf);
   glutPostRedisplay();
}

void GameWindow::display(Grid grid){
	glClear(GL_COLOR_BUFFER_BIT);
	drawSquares (GL_RENDER, grid); //will later use bind
	glFlush();
}

void GameWindow::reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0, 10.0, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GameWindow::startGameWindow(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1100, 500);
	glutInitWindowPosition (100, 100);
	int mainw = glutCreateWindow ("GRID");
	int subw = glutCreateSubWindow (mainw, 0, 0, 500, 500);
	init();
	glutMouseFunc (pickSquares);
	glutReshapeFunc (reshape);
	glutDisplayFunc(display);
}
