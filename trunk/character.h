/*
 *  character.cpp
 *  Final_Project
 *
 *  Created by Jake Flynt on 3/4/12.
 *  Copyright 2012. All rights reserved.
 *
 */

/*
Base character class
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
  character (int, int, int);

  //functions for the position           int getXPos ();                int getYPos ();                void setXPos (int);            void setYPos (int);

  //function for moving          int leftFacing;
  int rightFacing;

  //functions for tracking lives
  int getLives ();
  void setLives (int);
  int movementSpeed;
  int xPos;
  int yPos;
  int lives;			// number of lives remaining

  int getXSize ();
  int getYSize ();
  void setXSize (int);
  void setYSize (int);
private:int xsize;
  int ysize;
};


#endif
