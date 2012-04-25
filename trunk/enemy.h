/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */  
  
#ifndef ENEMY_H
#define ENEMY_H
  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "character.h"
  using namespace std;
class enemy : public character
{
	public:		enemy (int, int, int, int,int,int);
		//enemy();
		void destroyEnemy();

		void moveLeft ();		// function to move left
		void moveRight ();		// function to move right
		void update(int, int, int, int, int, int);
		int  getRangeStart(void);
		int  getRangeFinish(void);
		int rangeStart;
		int rangeFinish;
		void moveWithPlatform (int);			private:		
};

#endif
