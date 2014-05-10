/*
 * singleShip.h
 *
 *  Created on: Apr 29, 2014
 *      Author: klis
 */

#ifndef SINGLESHIP_H_
#define SINGLESHIP_H_
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

class Ship{
protected:
	static Ship* instance;
public:
	Ship();
	virtual ~Ship();

	void setInstance();
	Ship* getInstance(){return instance;}

	virtual void mouseButton( int button, int state, int x, int y ); //zapisanie wspolrzednych srodka kwadratu po kliknieciu
	virtual void display(); //funkcja wyswietlajaca kwadraty
	virtual void reshape( int width, int height ); //funkcja zmieniajaca rozmiar okna
	virtual void menu( int value );//menu podreczne dostepne po nacisnieciu PPM

	void addCoordinates(int x, int y); //dodanie wspolrzednych kolejnego punktu (srodka kwadratu)
	int getX(int i){return vertex_x[i];};
	int getY(int i){return vertex_y[i];};;
	std::vector < GLint >* getVectorX(){return &vertex_x;};
	std::vector < GLint >* getVectorY(){return &vertex_y;};
	int getVectorXSize(){return vertex_x.size();}
	int getVectorYSize(){return vertex_y.size();}
	void clear();
	void draw(GLint x, GLint y); //rysowanie kwadratu o srodu w punkcie P(x,y)
	void erase();//funkcja usuwa wszystkie narysowane kwadraty
	void testShip( int argc, char * argv[] ); //prosta funkcja testowa pozwalajaca uzytkownikowi rysowac kwadraty we wskazanych myszka punktach

	//Wrappery pozwalające korzystać z bibliotek glut przy uzyciu zaimplementowanych wewnatrz klasy funkcji
	static void mouseWrapper( int button, int state, int x, int y );
	static void displayWrapper();
	static void reshapeWrapper( int width, int height );
	static void menuWrapper( int value );

	GLfloat getPointSize(){return point_size;};

private:
	//wektory wspolrzednych
	std::vector < GLint > vertex_x;
	std::vector < GLint > vertex_y;

	// rozmiar punktów

	GLfloat point_size;

	//stale uzyte w menu podrecznym
	enum
	{
	    CLEAR_POINTS, // usuwanie punktów
	    EXIT // wyjście
	};
};



#endif /* SINGLESHIP_H_ */
