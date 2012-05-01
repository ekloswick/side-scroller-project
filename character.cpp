/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"character.cpp"
 */ 

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <character.h>

#include <QPrinter>
#include <QtGui>

using namespace std;

character::character (int x, int y, int lives)
{
  setXPos (x);
  setYPos (y);
  setLives (lives);
  rightFacing = 1;
}

int
character::getXPos ()
{
  return xPos;
}

int
character::getYPos ()
{
  return yPos;
}

void
character::setXPos (int n)
{
  xPos = n;
}

void
character::setYPos (int n)
{
  yPos = n;
}


void
character::setLives (int L)
{
  lives = L;
}

int
character::getLives ()
{
  return lives;
}

int
character::getXSize () 
{  return xsize;}

int
character::getYSize () 
{return ysize;}

void
character::setXSize (int n) 
{xsize = n;} void
character::setYSize (int n) 
{ ysize = n;}
