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

  character::leftFacing = 0;
  character::rightFacing = 1;
}

enemy::~enemy()
{
	xPos = -5000;
	yPos = -5000;
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
	setYPos(y);
	setLives(lives);

}

void enemy::moveWithPlatform(int speed)
{
setXPos(getXPos()-speed);
 rangeStart -= speed;
  rangeFinish -= speed;
cout<<"RANGE START: "<<rangeStart<<endl;
cout<<"RANGE FINISH: "<<rangeFinish<<endl;
cout<<"X POS: "<<getXPos()<<endl;



}






