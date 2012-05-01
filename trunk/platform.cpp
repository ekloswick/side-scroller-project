/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"platform.cpp"
*/  
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <platform.h>
  
#include <QPrinter>
#include <QtGui>
  using namespace std;
platform::platform (int X, int Y, int W, int H) 
{
  xPos = X;
  yPos = Y;
  width = W;
  height = H;
} void

platform::setX (int n) 
{
  xPos = n;
} void

platform::setY (int n) 
{
  yPos = n;
}

void
platform::setWidth (int n)
{
  width = n;
}

void
platform::setHeight (int n)
{
  height = n;
} int

platform::getX () 
{
  return xPos;
}

int
platform::getY () 
{
  return yPos;
}

int
platform::getHeight () 
{
  return height;
}

int
platform::getWidth () 
{
  return width;
}

void
platform::moveLeft (int movementSpeed)	// function to move left
{
  xPos -= movementSpeed;
} void

platform::moveRight (int movementSpeed)	// function to move right
{
  xPos += movementSpeed;
} 
