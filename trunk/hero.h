/*
 *  character.cpp
 *  Final_Project
 *
 *  Created by Jake Flynt on 3/4/12.
 *  Copyright 2012. All rights reserved.
 *
 */  
  
#ifndef HERO_H
#define HERO_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "character.h"


// *** CHECK TO MAKE SURE CHARACTER IS ALL GONE
  
using namespace std;

class hero : public character
{

    public:
          hero (int, int, int);
      
        int getXVel ();
        int getYVel ();

        
        int isJumping;

        void setXVel (int);
        void setYVel (int);
        void moveLeft ();        // function to move left
        void moveRight ();        // function to move right

        int getGravity ();
        void jump ();            // function to jump

        
    private:
        int xVel;            // acceleration in x direction
        int yVel;            // acceleration in y direction
        int gravity;


};



#endif
