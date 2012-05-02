/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"hero.h"'

hero class inherits from base class character
This class is used to create the object MARIO!
*/  
  
#ifndef HERO_H
#define HERO_H  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "character.h"
    using namespace std;class hero:public character 
{
public:	hero (int, int, int); 	//set and get functions for the velocity	
	int getXVel ();	int getYVel ();	void setXVel (int);  	void setYVel (int);  	void moveLeft ();	// function to move left
	void moveRight ();	// function to move right
	void jump ();		// function to jump  	int getGravity ();	//returns the value of the gravityprivate:	int xVel;		// velocity in x direction
	int yVel;		//  veloctity in y direction
	int gravity;   		//gravity that causes mario to fall back to the platform
	int isJumping;		//variable to keep track of whether mario is jumping at the current point};

#endif
