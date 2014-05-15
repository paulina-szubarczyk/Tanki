#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

int board[10][10];   /*  amount of color for each square  */
int board2[10][10];
/*  Clear color value for every square on the board   */
void init(void)
{
   int i, j;
   for (i = 0; i < 10; i++)
      for (j = 0; j < 10; j ++)
         board[i][j]=board2[i][j] = 0;
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glFlush();


}

void drawSquares(GLenum mode) //draw grid
{
   GLuint i, j;
   for (i = 0; i < 10; i++) {
      if (mode == GL_SELECT)
         glLoadName (i);
      for (j = 0; j < 10; j ++) {
         if (mode == GL_SELECT)
            glPushName (j);
         glPolygonMode(GL_FRONT,GL_FILL);
         glColor3f ((GLfloat) board[i][j], (GLfloat) 0.4 - board[i][j],
                    (GLfloat) 0.7 - board[i][j]);
         glRecti (i, j, i+1, j+1);
         glPolygonMode(GL_FRONT,GL_LINE);
         glColor3f(0.0,0.0,0.0);
         glRecti (i, j, i+1, j+1);
         if (mode == GL_SELECT)
            glPopName ();
      }
   }
}

void drawSquares2(GLenum mode) //draw grid
{
   GLuint i, j;
   for (i = 0; i < 10; i++) {
      if (mode == GL_SELECT)
         glLoadName (i);
      for (j = 0; j < 10; j ++) {
         if (mode == GL_SELECT)
            glPushName (j);
         glPolygonMode(GL_FRONT,GL_FILL);
         glColor3f ((GLfloat) board2[i][j], (GLfloat) 0.4 - board2[i][j],
                    (GLfloat) 0.7 - board2[i][j]);
         glRecti (i, j, i+1, j+1);
         glPolygonMode(GL_FRONT,GL_LINE);
         glColor3f(0.0,0.0,0.0);
         glRecti (i, j, i+1, j+1);
         if (mode == GL_SELECT)
            glPopName ();
      }
   }
}
/*  processHits prints out the contents of the
 *  selection array.
 */
void processHits (GLint hits, GLuint buffer[])
{
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
      board[ii][jj] = (board[ii][jj] + 1);
   }
}
void processHits2 (GLint hits, GLuint buffer[])
{
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
      board2[ii][jj] = (board2[ii][jj] + 1);
   }
}
#define BUFSIZE 512

void pickSquares(int button, int state, int x, int y)
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
/*  create 5x5 pixel picking region near cursor location      */
   gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                  5.0, 5.0, viewport);
   gluOrtho2D (0.0, 10.0, 0.0, 10.0);
   drawSquares (GL_SELECT);

   glMatrixMode (GL_PROJECTION);
   glPopMatrix ();
   glFlush ();

   hits = glRenderMode (GL_RENDER);
   processHits (hits, selectBuf);
   glutPostRedisplay();
}

void pickSquares2(int button, int state, int x, int y)
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
/*  create 5x5 pixel picking region near cursor location      */
   gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                  5.0, 5.0, viewport);
   gluOrtho2D (0.0, 10.0, 0.0, 10.0);
   drawSquares2 (GL_SELECT);

   glMatrixMode (GL_PROJECTION);
   glPopMatrix ();
   glFlush ();

   hits = glRenderMode (GL_RENDER);
   processHits2 (hits, selectBuf);
   glutPostRedisplay();
}



void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   drawSquares (GL_RENDER);
   glFlush();
}
void display2(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   drawSquares2 (GL_RENDER);
   glFlush();
}
void reshape(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (0.0, 10.0, 0.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (1100, 500);
   glutInitWindowPosition (100, 100);
   int mainw = glutCreateWindow ("GRID");
   init();

   int subw = glutCreateSubWindow (mainw, 0, 0, 500, 500);

   init ();
   glutMouseFunc (pickSquares);
   glutReshapeFunc (reshape);
   glutDisplayFunc(display);
   int subw2 = glutCreateSubWindow (mainw, 600, 0, 500, 500);
   glutMouseFunc (pickSquares2);
     glutReshapeFunc (reshape);
     glutDisplayFunc(display2);
   glutMainLoop();
   return 0;
}
