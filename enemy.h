/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */  
  
#ifndef ENEMY_H
#define ENEMY_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
  using namespace std;
class enemy 
{
	public:		enemy ();
		~enemy();		void setX (int);
		void setY (int);
		int getX ();
		int getY ();
		void moveLeft ();		// function to move left
		void moveRight ();		// function to move right
		int left;
		int right;

		int getLife(void);
		void setLife(int);

	private:		int xPos; 		int yPos;  		int movementSpeed;
		int life;
};


#endif
