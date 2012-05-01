/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"mushroom.h"
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
public:mushroom (int, int);

	void moveWithPlatform (int);
	void setXPos(int);
	void setYPos(int);
	int getXPos(void);
	int getYPos(void);

	int getXSize(void);
	int getYSize(void);

void update(int, int);
private:
	int xPos;
	int yPos;
	int xSize;
	int ySize;
};

#endif
