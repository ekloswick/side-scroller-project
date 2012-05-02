/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"hero.cpp"

hero class inherits from base class character
This class is used to create the object MARIO!
*/  
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <hero.h>
#include <QPrinter>
#include <QtGui>
  using namespace std;
//constructorhero::hero (int x, int y, int lives):
character (x, y, lives) 
{	setXVel (0);	setYVel (getGravity ());	gravity = 25;
	setRightFacing (1); 	setXSize (15); 	setYSize (27);	setMovementSpeed (16);} void
hero::moveLeft ()		// function to move left
{	xVel -= getMovementSpeed();}
void
hero::moveRight ()		// function to move right
{ 	xVel += getMovementSpeed();} void
hero::jump ()      		// function to jump 
{	yVel = -70;} 
//return the velocites
int
hero::getXVel () 
{	return xVel;}int
hero::getYVel () 
{ 	return yVel;}
//set the position
void
hero::setXVel (int n) 
{  	xVel = n;} void
hero::setYVel (int n) 
{	yVel = n;} 
int
hero::getGravity () 
{	return gravity;}


