/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"mushroom.cpp"

This class is used to make 1UP mushroom objects
*/ 

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <mushroom.h>
#include "character.h"
#include <QPrinter>
#include <QtGui>

using namespace std;

mushroom::mushroom (int x, int y)	//constructor
{
	xPos=x;
	yPos=y; 
	xSize = 16;
	ySize = 16;
}

//set functions
void mushroom::setXPos(int x)
{
	xPos=x;
}

void mushroom::setYPos(int y)
{
	yPos=y;
}

//get functions

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

void mushroom::update(int x, int y)		//updates x and y position
{
	xPos=x;
	yPos=y;
}

void mushroom::moveWithPlatform (int speed)	//scrolls the mushroom w/ marios movement
{
	setXPos (getXPos () - speed);
}

