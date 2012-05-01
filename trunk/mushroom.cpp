/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"mushroom.cpp"
*/ 

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <mushroom.h>
#include "character.h"
#include <QPrinter>
#include <QtGui>

using namespace std;

mushroom::mushroom (int x, int y)
{
  xPos=x;
  yPos=y; 
  xSize = 16;
  ySize = 16;
}

void mushroom::setXPos(int x)
{
xPos=x;
}

void mushroom::setYPos(int y)
{
yPos=y;
}

int mushroom::getXPos(void)
{
return xPos;
}

int mushroom::getYPos(void)
{
return yPos;
}

int mushroom::getXSize(void)
{
return xSize;
}

int mushroom::getYSize(void)
{
return ySize;
}


void
mushroom::moveWithPlatform (int speed)
{
  setXPos (getXPos () - speed);
}

void 
mushroom::update(int x, int y)
{
xPos=x;
yPos=y;
}
