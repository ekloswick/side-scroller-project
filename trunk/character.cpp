/*
 *  character.cpp
 *  Final_Project
 *
 *  Created by Jake Flynt on 3/4/12.
 *  Copyright 2012. All rights reserved.
 *
 */

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <character.h>

#include <QPrinter>
#include <QtGui>

using namespace std;

character::character(int x, int y, int lives)
{
	setXPos(x);
	setYPos(y);
	setLives(lives);
	rightFacing=1;
}

int character::getXPos()
{
	return xPos;
}

int character::getYPos()
{
	return yPos;
}

void character::setXPos(int n)
{
	xPos = n;
}

void character::setYPos(int n)
{
	yPos = n;
}


void character::setLives(int L)
{
	lives=L;
}

int character::getLives()
{
	return lives;
}




