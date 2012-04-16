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

character::character()
{
	setXPos(360);
	setYPos(500);
	lives = 3;
	setXVel(0);
	setYVel( getGravity() );
	gravity = 25;
	rightFacing=1;
	setXSize(98);
	setYSize(164);
}

void character::moveLeft()
{
	xVel += -16;
}

void character::moveRight()
{
	xVel += 16;
}

void character::moveUp()
{
	//yPos -= 5;	
}  

void character::moveDown()
{
	//yPos += 5;
}

void character::jump()
{
	yVel = -80;
}
/*
void character::shoot()
{
  if (press == '')
    // shoot
}

*/

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

int character::getXVel()
{
	return xVel;
}

int character::getYVel()
{
	return yVel;
}

void character::setXVel(int n)
{
	xVel = n;
}

void character::setYVel(int n)
{
	yVel = n;
}

int character::getGravity()
{
	return gravity;
}

int character::getLives()
{
	return lives;
}

int character::getXSize()
{
	return xsize;
}

int character::getYSize()
{
	return ysize;
}

void character::setXSize(int n)
{
	xsize = n;
}

void character::setYSize(int n)
{
	ysize = n;
}
