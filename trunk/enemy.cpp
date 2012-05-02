/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"enemy.cpp"

Enemy class inherits from the base class character
This is used to create GOOMBA objects
 */ 

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <enemy.h>
#include "character.h"
#include <QPrinter>
#include <QtGui>

using namespace std;
//constructor
enemy::enemy (int x, int y, int lives, int mSpeed, int rstart, int rfinish):
character (x, y, lives)
{
  setMovementSpeed(mSpeed);
  rangeStart = rstart;
  rangeFinish = rfinish;
  setXSize (70);
  setYSize (86);
  setLeftFacing (0);
  setRightFacing (1);
}

//this function is called once the enemy has been killed in order to move it off of the board
void
enemy::destroyEnemy ()
{
  setXPos(-5000);
  setYPos(-5000);
  rangeStart = -5000;
  rangeFinish = -5000;
  setMovementSpeed (0);
}

//motion functions
void
enemy::moveLeft ()
{
  setXPos (getXPos () - getMovementSpeed());
}

void
enemy::moveRight ()
{
  setXPos (getXPos () + getMovementSpeed());
}

//range tracking
int
enemy::getRangeStart (void)
{
  return rangeStart;
}

int
enemy::getRangeFinish (void)
{
  return rangeFinish;
}

//updates the goomba to allow the information of it to be read in from a text file
void
enemy::update (int x, int y, int lives, int mSpeed, int rstart, int rfinish)
{
  setMovementSpeed (mSpeed);
  rangeStart = rstart;
  rangeFinish = rfinish;

  setLeftFacing (0);
  setRightFacing (0);
  setXPos (x);
  setYPos (y - (getYSize () / 2) + 8);	//allows it to program easily so that the goombas are on the board if the text file has same y value as board file
  setLives (lives);
}

//updates the values of the goombas to allow it to scroll along with the platform as mario moves
void
enemy::moveWithPlatform (int speed)
{
  setXPos (getXPos () - speed);
  rangeStart -= speed;
  rangeFinish -= speed;
}
