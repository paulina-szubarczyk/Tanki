/*
 * singleShip.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: klis
 */

#include "ship.h"

Ship *Ship::instance = NULL;
Ship::Ship(){
	point_size = 50.0;
};
Ship::~Ship(){};
void Ship::setInstance(){
	instance = this;
}

void Ship::clear(){
	vertex_x.clear();
	vertex_y.clear();
}
void Ship::addCoordinates(int x, int y){
	vertex_x.push_back( x );
	vertex_y.push_back( glutGet( GLUT_WINDOW_HEIGHT ) - y );

}


void Ship::mouseButton( int button, int state, int x, int y )
{
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        // zapamiętanie współrzędnych punktu
    	addCoordinates(x,y);

        // wyswietlenie
        display();
    }
}

void Ship::draw(GLint x, GLint y){
	glPointSize( point_size );
	glBegin( GL_POINTS );
	glVertex2i( x, y );
	glEnd();
}
void Ship::display()
{
    // kolor tła - zawartość bufora koloru
    glClearColor( 1.0, 1.0, 1.0, 1.0 );

    // czyszczenie bufora koloru
    glClear( GL_COLOR_BUFFER_BIT );

    // wybór macierzy modelowania
    glMatrixMode( GL_MODELVIEW );

    // macierz modelowania = macierz jednostkowa
    glLoadIdentity();

    // kolor punktów
    glColor3f( 1.0, 0.0, 0.0 );

    // rysowanie punktów
    for( unsigned int i = 0; i < vertex_x.size(); i++ )
    {
        // wielkość punktów
    	draw( vertex_x[ i ], vertex_y[ i ] );
    }

    // skierowanie poleceń do wykonania
    glFlush();

    // zamiana buforów koloru
    glutSwapBuffers();
}

void Ship::reshape( int width, int height )
{
    // obszar renderingu - całe okno
    glViewport( 0, 0, width, height );

    // wybór macierzy rzutowania
    glMatrixMode( GL_PROJECTION );

    // macierz rzutowania = macierz jednostkowa
    glLoadIdentity();

    // rzutowanie prostokątne
    gluOrtho2D( 0, width, 0, height );

    // generowanie sceny 3D
    display();
}

void Ship::erase(){
	vertex_x.erase( vertex_x.begin(), vertex_x.end() );
	vertex_y.erase( vertex_y.begin(), vertex_y.end() );

}
void Ship::menu( int value )
{
    switch( value )
    {
        // usuwanie współrzędnych i rozmiarów punktów
    case CLEAR_POINTS:
//        vertex_x.erase( vertex_x.begin(), vertex_x.end() );
//        vertex_y.erase( vertex_y.begin(), vertex_y.end() );
    	erase();
        display();
        break;

        // wyjście
    case EXIT:
        exit( 0 );
    }
}

void Ship::mouseWrapper( int button, int state, int x, int y ){
	instance->mouseButton( button,  state, x, y );
}

void Ship::displayWrapper(){
	instance->display();
}
void Ship::reshapeWrapper( int width, int height ){
	instance->reshape( width, height );
}
void Ship::menuWrapper( int value ){
	instance->menu( value );
}
void Ship::testShip( int argc, char * argv[] )
{
	setInstance();
    // inicjalizacja biblioteki GLUT
    glutInit( & argc, argv );

    // inicjalizacja bufora ramki
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

    // rozmiary głównego okna programu
    glutInitWindowSize( 500, 500 );

    // utworzenie głównego okna programu
    glutCreateWindow( "Statki" );

    // dołączenie funkcji generującej scenę 3D
    glutDisplayFunc( displayWrapper );

    // dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
    glutReshapeFunc( reshapeWrapper );

    // obsługa przycisków myszki
    glutMouseFunc( mouseWrapper );

    // dołączenie funkcji obsługi klawiatury
   // glutKeyboardFunc( Keyboard );

    // menu główne
    glutCreateMenu( menuWrapper );
    #ifdef WIN32

    glutAddMenuEntry( "Wyczysc", CLEAR_POINTS );
    glutAddMenuEntry( "Wyjście", EXIT );
    #else

    glutAddMenuEntry( "Wyczysc", CLEAR_POINTS );
    glutAddMenuEntry( "Wyjscie", EXIT );
    #endif

    // określenie przycisku myszki obsługującego menu podręczne
    glutAttachMenu( GLUT_RIGHT_BUTTON );

    // wprowadzenie programu do obsługi pętli komunikatów
    glutMainLoop();
    //return 0;
}
