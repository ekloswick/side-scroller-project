/*
 *  character.cpp
 *  Final_Project
 *
 *  Created by Jake Flynt on 3/4/12.
 *  Copyright 2012. All rights reserved.
 *
 */  
  
#ifndef CHARACTER_H
#define CHARACTER_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
  using namespace std;
class character 
{	public:
		character();
		int getXPos();
		int getYPos();
		void setXPos(int);
		void setYPos(int);

		int getXVel();
		int getYVel();
		void setXVel(int);
		void setYVel(int);

		int getGravity();

		void moveLeft(); // function to move left
		void moveRight(); // function to move right
		void moveUp();	// function to move up
		void moveDown();	// function to move down
	   
		void jump(); // function to jump
		//void shoot(); // function to use weapon
	   

	private:
		int xPos;
		int yPos;
	   
		//int health; // percentage of health remaining
		int lives; // number of lives remaining
		//char press; // gets keyboard input
	   
		int xVel;	// acceleration in x direction
		int yVel;	// acceleration in y direction
		int gravity;
};

#endif
