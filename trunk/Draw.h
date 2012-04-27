/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */


#ifndef DRAW_H_
#define DRAW_H_

#include <QWidget>
#include "character.h"
#include "enemy.h"
#include "hero.h"
#include "platform.h"
#include <vector>

using namespace std;


class Draw:public QWidget
{
Q_OBJECT public:
  Draw (QWidget * parent = 0);


protected:
  void paintEvent (QPaintEvent * e);
  void keyPressEvent (QKeyEvent * event);
  void keyReleaseEvent (QKeyEvent * event);
  void updatePhysics ();	//update the physics of mario
  void timerEvent (QTimerEvent *);
  void updateEnemy ();		//update the motion of the enemies
  void testCollision ();	//test for collision between mario and enemy
  void displayStageInfo ();
  void displayWelcomeMessage ();
  void drawMario ();
  void drawStage ();
  void drawEnemies ();
  void playerWon ();
  void stageComplete ();
  void gameOver ();
void xChange(unsigned int );


private:
  //size of board
  int xWindowSize;
  int yWindowSize;
  //keep track of physics
  int movingLeft;
  int movingRight;
  int jumping;

    vector < platform > board;	//vector of platform to keep track of the board
  hero mario;			//mario is an object of type hero
  enemy badguy;			//object of type badguy
    vector < enemy > enemies;	//vector of enemy to keep track of the enemies

  void loadBoard ();		//function to read in the board from a text file
  void loadEnemies ();		//function to read in the enemies from a text file

  int welcome;			// 0 for welcome message; 1 for no welcome message
  int marioScalingFactor;
  int enemyScalingFactor;
  int score;			//used to keep track of the players score   
  int level;			//used to keep track of the current level the player is on
  int gameComplete;		//used to determine if the player has beat the game
  int levelComplete;		//used to determine if the player has finished a level
  int levelMax;			//the number of levels in the game
  int playerLost;		//user lost
  int debug;			//set to 1 for debug mode; otherwise 0
};

#endif
