/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"hero.cpp"
*/   
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <hero.h>
#include <QPrinter>
#include <QtGui>
  using namespace std;
hero::hero (int x, int y, int lives):
character (x, y, lives) 
{ setXVel (0);setYVel (getGravity ()); gravity = 25; 
rightFacing = 1; setXSize (15);setYSize (27);movementSpeed = 16;} void
hero::moveLeft ()		// function to move left
{  xVel -= movementSpeed;} void
hero::moveRight ()		// function to move right
{ xVel += movementSpeed;} void
hero::jump () 
{ yVel = -70;} int
hero::getXVel () 
{ return xVel;}int
hero::getYVel () 
{  return yVel;}void
hero::setXVel (int n) 
{ xVel = n;} void
hero::setYVel (int n) 
{yVel = n;} int
hero::getGravity () 
{ return gravity;}


