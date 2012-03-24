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
{
public:
  character ();
  int getX ();
  int getY ();
  void setX (int n);
  void setY (int n);
  void moveLeft ();		// function to move left
  void moveRight ();		// function to move right
  void jump ();			// function to jump
  int getLives ();		//gets the number of lives of the character
  void setLives (int);		//sets the number of lives of the character
//  void jump(); // function to jump
//  void shoot(); // function to use weapon
private:int xPos;
  int yPos;
  int lives;			// number of lives remaining
  
/*
  int health; // percentage of health remaining

  char press; // gets keyboard input
*/ 
};


#endif	/*  */
