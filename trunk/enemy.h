/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"enemy.h"
 */ 
  
#ifndef ENEMY_H
#define ENEMY_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "character.h"
  using namespace std;
class enemy:public character 
{
public:enemy (int, int, int, int, int, int);
  void destroyEnemy ();
  void moveLeft ();		// function to move left
  void moveRight ();		// function to move right
  void update (int, int, int, int, int, int);
  int getRangeStart (void);
  int getRangeFinish (void);
  int rangeStart;
  int rangeFinish;
  void moveWithPlatform (int);
private:
};


#endif
