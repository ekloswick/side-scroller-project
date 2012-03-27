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
  yPos = 300;
  movementSpeed = 20;
  left = 0;
  right = 0;
}


enemy::setX (int n)
{
  xPos = n;
}


enemy::setY (int n)
{
  yPos = n;
}

int
enemy::getX ()
{
  return xPos;
}


enemy::getY ()
{
  return yPos;
}


enemy::moveLeft ()		// function to move left
{
  xPos -= movementSpeed;
} 

enemy::moveRight ()		// function to move right
{
  xPos += movementSpeed;
}