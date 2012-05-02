/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"enemy.h"

Enemy class inherits from the base class character
This is used to create GOOMBA objects
*/ 
  
#ifndef ENEMY_H
#define ENEMY_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "character.h"
  using namespace std;class enemy : public character 
{
	public:		enemy (int, int, int, int, int, int);
		void destroyEnemy ();				//destroys the enemy by moving it way off the board
		void moveLeft ();					// function to move left
		void moveRight ();					// function to move right
		void update (int, int, int, int, int, int);	//updates enemy with new info
		int getRangeStart (void);
		int getRangeFinish (void);
		void moveWithPlatform (int); 			//function to scroll enemies with the platform
	private:
		//positions goombas can move between
		int rangeStart;
		int rangeFinish;
};

#endif
