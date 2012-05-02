/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"platform.h"

These platforms are used in an array to create the board
*/  
  
#ifndef PLATFORM_H
#define PLATFORM_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
  using namespace std;
class platform 
{public:	platform (int, int, int, int);  //constructor	//set functions	
	void setX (int); 			void setY (int);
	void setWidth (int);
	void setHeight (int); 	//get functions
	int getX ();	int getY ();	int getHeight ();	int getWidth ();
	//move the board left and right	void moveLeft (int);		// function to move left
	void moveRight (int);		// function to move right
private:	int xPos; 	int yPos; 	int width; 	int height;
};

#endif
