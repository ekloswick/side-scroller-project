/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */  
  
#ifndef PLATFORM_H
#define PLATFORM_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
  using namespace std;
class platform 
{
public:platform (int, int, int, int);
  void setX (int);
  void setY (int);
  void setWidth (int);
  void setHeight (int);
  int getX ();
  int getY ();
  int getHeight ();
  int getWidth ();
  void moveLeft (int);		// function to move left
  void moveRight (int);		// function to move right
private:int xPos;
  int yPos;
  int width;
  int height;
};


#endif
