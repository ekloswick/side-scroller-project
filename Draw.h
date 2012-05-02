/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"Draw.h"

Creates a QT widget and performs the logic to run
the game
*/

#ifndef DRAW_H_
#define DRAW_H_

#include <QWidget>
#include <vector>
#include "character.h"
#include "platform.h"
#include "mushroom.h"
#include "enemy.h"
#include "hero.h"

using namespace std;

class Draw : public QWidget
{
	Q_OBJECT
	
	public:
		Draw (QWidget * parent = 0);

	protected:
		void paintEvent (QPaintEvent * e);
		void keyPressEvent (QKeyEvent * event);
		void keyReleaseEvent (QKeyEvent * event);
		void updatePhysics ();		//update the physics of mario
		void timerEvent (QTimerEvent *);
		void updateEnemy ();		//update the motion of the enemies
		void testCollision ();		//test for collision between mario and enemy
		void drawMario ();
		void drawStage ();
		void drawEnemies ();
		void drawMushroom();
		void xChange (unsigned int);			// moves mario in x direction while testing for collisions with walls
		void xChangeOverAir (unsigned int);	// moves mario in x direction while not above platform
		void mushroomCollect();
		void mushroomLoad();
		void loadBoard ();			//function to read in the board from a text file
		void loadEnemies ();		//function to read in the enemies from a text file
		void helpMenu();			// displays readme in the terminal
		
		// display the appropriate screens
		void displayStageInfo ();
		void displayWelcomeMessage ();
		void playerWon ();
		void stageComplete ();
		void gameOver ();


	private:
		//size of board
		int xWindowSize;
		int yWindowSize;
		
		//keep track of physics
		int movingLeft;
		int movingRight;
		int jumping;

		vector < platform > board;	//vector of platform to keep track of the board
		hero mario;				//mario is an object of type hero
		enemy badguy;				//object of type badguy
		mushroom lifeMushroom;
		vector < enemy > enemies;	//vector of enemy to keep track of the enemies
		vector < vector < int > > clouds;
		vector < int >cloud;

		int welcome;				// 0 for welcome message; 1 for no welcome message
		int marioScalingFactor;
		int enemyScalingFactor;
		double bowserScalingFactor;
		int score;				//used to keep track of the players score   
		int level;				//used to keep track of the current level the player is on
		int gameComplete;			//used to determine if the player has beat the game
		int levelComplete;			//used to determine if the player has finished a level
		int levelMax;				//the number of levels in the game
		int playerLost;			//user lost
		int debug;				//set to 1 for debug mode; otherwise 0
		int cloudRandomize;			// used to randomize the clouds on each level
		int bowserTimer;			// times Bowsers animations
};

#endif

