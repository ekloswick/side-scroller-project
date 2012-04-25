/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <enemy.h>
#include "character.h"
#include <QPrinter>
#include <QtGui>

using namespace std;
 
enemy::enemy (int x, int y, int lives, int mSpeed, int rstart, int rfinish) : character(x,y,lives)
{
  movementSpeed=mSpeed;
  rangeStart = rstart;
  rangeFinish= rfinish;

  setXSize(70);
  setYSize(86);


  character::leftFacing = 0;
  character::rightFacing = 1;
}

void enemy::destroyEnemy()
{
	xPos = -5000;
	yPos = -5000;
rangeStart = -5000;
rangeFinish = -5000;
	movementSpeed = 0;
}

void enemy::moveLeft()
	{
	setXPos(getXPos()-movementSpeed);
	}

void enemy::moveRight()
	{
	setXPos(getXPos()+movementSpeed);
	}

int enemy::getRangeStart(void)
{
return rangeStart;
}

int enemy::getRangeFinish(void)
{
return rangeFinish;
}

void enemy::update(int x, int y, int lives, int mSpeed, int rstart, int rfinish)
{
  movementSpeed=mSpeed;
  rangeStart = rstart;
  rangeFinish= rfinish;

  character::leftFacing = 0;
  character::rightFacing = 0;
  setXPos(x);
  setYPos(y-(getYSize()/2)+8); //allows it to program easily so that the goombas are on the board if the text file has same y value as board file
  setLives(lives);
}

void enemy::moveWithPlatform(int speed)
{
	setXPos(getXPos()-speed);
	rangeStart -= speed;
	rangeFinish -= speed;
}






