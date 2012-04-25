/*
 *  hero.cpp
 *  Final_Project
 *
 *  Created by Jake Flynt on 3/4/12.
 *  Copyright 2012. All rights reserved.
 *
 */

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <hero.h>
#include <QPrinter>
#include <QtGui>

using namespace std;

hero::hero(int x, int y, int lives) : character (x,y,lives)
{
    setXVel(0);
    setYVel(getGravity());
    gravity = 25;
    character::rightFacing=1;
    setXSize(98);
    setYSize(164);
    movementSpeed=16;
    levelComplete=0;
}


void hero::moveLeft ()    // function to move left
{
xVel-=movementSpeed;
}
void hero::moveRight ()        // function to move right
{
xVel+=movementSpeed;
}

void hero::jump()
{
    yVel = -80;
}


int hero::getXVel()
{
    return xVel;
}

int hero::getYVel()
{
    return yVel;
}

void hero::setXVel(int n)
{
    xVel = n;
}

void hero::setYVel(int n)
{
    yVel = n;
}

int hero::getGravity()
{
    return gravity;
}






