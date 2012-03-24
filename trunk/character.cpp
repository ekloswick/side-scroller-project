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


character::character ()
{
  setX (360);
  setY (532);
  lives = 3;
}

void
character::moveLeft ()
{
  xPos -= 10;
}

void
character::moveRight ()
{
  xPos += 10;
}

void
character::jump ()
{
  yPos += 50;
  yPos -= 50;
}

int
character::getLives ()
{
  return lives;
}

void
character::setLives (int n)
{
  lives = n;
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

int
character::getX ()
{
  return xPos;
}

int
character::getY ()
{
  return yPos;
}

void
character::setX (int n)
{
  xPos = n;
}

void
character::setY (int n)
{
  yPos = n;
}
