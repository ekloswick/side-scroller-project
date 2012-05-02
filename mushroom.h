/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"mushroom.h"

This class is used to make 1UP mushroom objects
*/ 
  
#ifndef MUSHROOM_H
#define MUSHROOM_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "character.h"
  using namespace std;
class mushroom
{
public:	mushroom (int, int);
	//set functions
	void setXPos(int);
	void setYPos(int);
	//get functions	
	int getXPos(void);
	int getYPos(void);
	int getXSize(void);
	int getYSize(void);
	void update(int, int);		//updates x and y position	
	void moveWithPlatform (int);    //scrolls the mushroom w/ marios movement
private:
	int xPos;
	int yPos;
	int xSize;
	int ySize;
};

#endif
