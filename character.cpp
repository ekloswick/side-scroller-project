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
  int getX();
  int getY();

  void setX(int n);
  void setY(int n);
/*
  character(); // constructor
  void moveLeft(); // function to move left
  void moveRight(); // function to move right
  void jump(); // function to jump
  void shoot(); // function to use weapon
*/
private:
  int xPos;
  int yPos;
/*
  int health; // percentage of health remaining
  int lives; // number of lives remaining
  char press; // gets keyboard input
*/
};

/*
character::character()
{
// empty constructor
}

void character::moveLeft()
{
  if (press == 'a')
    // switch to left-facing sprite
    // move left
}

void character::moveRight()
{
  if (press == ' d')
    // swtich to right-facing sprite
    // move right
}

void character::jump()
{
  if (press == 'w')
    // jump
}

void character::shoot()
{
  if (press == '')
    // shoot
}

*/

int character::getX()
{
  return xPos;
}

int character::getY()
{
  return yPos;
}

void characet::setX(int n)
{
  xPos = n;
}

void character::setY(int n)
{
  yPos = n;
}

#endif
