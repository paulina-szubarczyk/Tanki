/*
 * GlutFunctions.cpp
 *
 *  Created on: May 29, 2014
 *      Author: klis
 */

#include "GlutFunctions.h"


void GlutFunctions::drawSquares(GLenum mode, Grid& grid) //draw grid
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

void GlutFunctions::mouseFunc(int button, int state, int x, int y, Grid& grid,int& pickedX, int& pickedY)
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
   processHits (hits, selectBuf, grid, pickedX, pickedY);
   glutPostRedisplay();
}


void GlutFunctions::display(Grid& grid){
	glClear(GL_COLOR_BUFFER_BIT);
	drawSquares (GL_RENDER, grid);
	glFlush();
}


void GlutFunctions::reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0, 10.0, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GlutFunctions::processHits(GLint hits, GLuint buffer[],Grid& grid, int& pickedX, int& pickedY){
	 unsigned int i, j;
	   GLuint ii, jj, names, *ptr;

	   printf ("hits = %d\n", hits);
	   ptr = (GLuint *) buffer;
	   for (i = 0; i < hits; i++) { /*  for each hit  */
	      names = *ptr;
	      ptr+=3;
	      for (j = 0; j < names; j++) { /*  for each name */
	         printf ("%d ", *ptr);
	         if (j == 0)  /*  set row and column  */
	            ii = *ptr;
	         else if (j == 1)
	            jj = *ptr;
	         ptr++;
	      }
	      printf ("\n");

	      //grid.getGrid()[ii][jj]->setColor(1.0,0.0,0.0);
	      pickedX=++ii;
	      pickedY=++jj;
	      glui_->sync_live();
}
}

