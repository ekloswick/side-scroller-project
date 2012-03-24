/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */

#ifndef ENEMY_H
#define ENEMY_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
  
using namespace std;


class enemy
{
public:
 enemy (int, int, int);

void setX (int n); 
void setY (int n);
int getX ();
int getY ();   

void moveLeft ();		// function to move left
void moveRight ();		// function to move right

private:
int xPos;
int yPos;
int movementSpeed;
};

#endif