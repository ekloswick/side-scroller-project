/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"hero.h"
*/  
  
#ifndef HERO_H
#define HERO_H  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "character.h"
    using namespace std;
class hero:public character 
{
public:hero (int, int, int);
  int getXVel ();int getYVel ();int isJumping;  //variable to keep track of whether mario is jumping at the current pointvoid setXVel (int);  void setYVel (int);  
void moveLeft ();		// function to move left
void moveRight ();		// function to move right
void jump ();		// function to jump  int getGravity ();  //returns the value of the gravity
private:int xVel;		// velocity in x direction
int yVel;	       //  veloctity in y direction
int gravity;    //gravity that causes mario to fall back to the platform
};


#endif
