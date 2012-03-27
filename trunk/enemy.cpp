/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <enemy.h>

#include <QPrinter>
#include <QtGui>

using namespace std;

enemy::enemy ()
{
  xPos = 300;
  yPos = 642;
  movementSpeed =5;
  left = 0;
  right = 0;
}

void
enemy::setX (int n)
{
  xPos = n;
}

void
enemy::setY (int n)
{
  yPos = n;
}

int
enemy::getX ()
{
  return xPos;
}

int
enemy::getY ()
{
  return yPos;
}

void
enemy::moveLeft ()		// function to move left
{
  xPos -= movementSpeed;
} void

enemy::moveRight ()		// function to move right
{
  xPos += movementSpeed;
}
