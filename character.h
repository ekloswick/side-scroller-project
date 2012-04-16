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
  

{

  		character ();
  
  
  
		int getYVel ();
		int getXSize();
		int getYSize();
		void setXSize(int);
		void setYSize(int);

		int leftFacing;
		int rightFacing;
		int isJumping;

		void setXVel (int);
		void setYVel (int);

		int getGravity ();
		int getLives ();
  
		void moveRight ();		// function to move right
		void moveUp ();			// function to move up
		void moveDown ();		// function to move down 
  		//void shoot(); // function to use weapon


  		//int health;			// percentage of health remaining

		int xVel;			// acceleration in x direction
	  	int yVel;			// acceleration in y direction
 		int gravity;
		int xsize;
		int ysize;



#endif