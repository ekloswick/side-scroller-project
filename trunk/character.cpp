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

using namespace std;


character::character()
{
	setX(300);
	setY(300);
}

void character::moveLeft()
{
	xPos -= 20;
}

void character::moveRight()
{
	xPos += 20;
}
/*
void character::jump()
{
  if (press == 'w')
    // jump
}

void character::shoot()
{
  if (press == '')
    // shoot
}

*/

int character::getX()
{
  return xPos;
}

int character::getY()
{
  return yPos;
}

void character::setX(int n)
{
  xPos = n;
}

void character::setY(int n)
{
  yPos = n;
}

