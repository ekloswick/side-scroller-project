/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"character.h"

Character is used as a base class from which hero and enemy derive. It mainly deals with positions, lives and movement  
*/
  
#ifndef CHARACTER_H
#define CHARACTER_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
  using namespace std;
class character 
{
	public:
		character (int, int, int);
		
		//functions for the position		int getXPos ();  		int getYPos ();		void setXPos (int); 		void setYPos (int);
		
		//functions for tracking lives
		int getLives ();
		void setLives (int);
		
		//functions for movement
		void setMovementSpeed(int);
		int getMovementSpeed(void);
		
		//functions for the size
		int getXSize ();		int getYSize ();		void setXSize (int);		void setYSize (int);
		
		//functions for the direction moving
		int getRightFacing(void);
		int getLeftFacing(void);
		void setRightFacing(int);
		void setLeftFacing(int);
	private:		int xsize; 		int ysize;		int lives; // number of lives remaining
		int xPos;		int yPos;
		int movementSpeed;
		
		//direction facing
		int leftFacing;
		int rightFacing;};

#endif

