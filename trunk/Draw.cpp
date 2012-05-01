/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
*/

#include "Draw.h"
#include "platform.h"
#include <QtGui>
#include <QPainter>
#include "qlabel.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <QFont>
#include "character.h"
#include "enemy.h"
#include "hero.h"
#include <QSound>



using namespace std;

// Open Window, set title and size.
Draw::Draw (QWidget * parent):QWidget (parent), mario (50, 50, 5), badguy (1, 1, 1, 1, 1, 1)
{
  setWindowTitle (tr ("Super Mario Side Scroller"));
  xWindowSize = 1000;
  yWindowSize = 600;
  resize (xWindowSize, yWindowSize);
  level = 0;			//the stage the player is one
//  loadBoard ();
  //loadEnemies ();
  startTimer (50);
  welcome = 0;			// 0 for welcome screen; 1 for no welcome screen
  marioScalingFactor = 2;
  enemyScalingFactor = 2;
  score = 0;
  levelComplete = 1;		//0 for the level is not complete; 1 for the level is completed
  levelMax = 3;
  playerLost = 0;
//**DEBUG MODE**
  debug = 1;
  setStyleSheet ("background-color: #4c6cdc");
  cloudRandomize=1;
srand(time(NULL));
}
// This method is called when the widget needs to be redrawn
void
Draw::paintEvent (QPaintEvent *)
{
  QPainter painter (this);	// get a painter object to send drawing commands to
if (cloudRandomize==1)
{
      clouds.clear();
      cloud.clear ();
  for (int i = 0; i < 15; i++)
    {
      cloud.push_back (20 + rand () % 1000);
      cloud.push_back (20 + rand () % 150);
      cloud.push_back (58);
      cloud.push_back (36);
      clouds.push_back (cloud);
      cloud.clear ();
    }
 cloudRandomize=0;
}


  if (level == levelMax)
{
  painter.setBrush (QBrush ("#ff0000"));
painter.drawRect(0,0, xWindowSize, yWindowSize);
}
  if (level != levelMax)
    {
      for (unsigned int i = 0; i < clouds.size (); i++)
	{
	  QRectF cloudTarget (clouds[i][0], clouds[i][1], clouds[i][2],
			      clouds[1][3]);
	  QRectF cloudSource (0.0, 0.0, 58, 36);
	  QPixmap cloudPixmap ("cloud.png");
	  QPainter (this);
	  painter.drawPixmap (cloudTarget, cloudPixmap, cloudSource);
	}
    }

  if (mario.getLives () > 0 && welcome != 0 && levelComplete != 1)
    {
      updateEnemy ();
      updatePhysics ();
      //testCollision (); //this already occurs in updatePhysics?
    }
  //Welcome message that is displayed until the user hits the space bar
  if (welcome == 0)
    {
      displayWelcomeMessage ();
	  QRectF welcomeTarget(0,0,1000,600);
	  QRectF welcomeSource (0.0, 0.0, 1000, 600);
	  QPixmap welcomePixmap ("welcomeScreen.png");
	  QPainter (this);
	  painter.drawPixmap (welcomeTarget, welcomePixmap, welcomeSource);
    }

  else if (mario.getLives () > 0 && levelComplete == 0)	//while the game is running
    {
      //display the stage info
      displayStageInfo ();
      //Draw the mario
      drawMario ();
      //Draw the Stage
      drawStage ();
      //Draw the enemies
      drawEnemies ();
    }
//if mario beat the level with lives remaining display to the user and ask if they would like to play again
  else if (mario.getLives () > 0 && gameComplete == 1)
    {
      playerWon ();		//player won screen
    }
  else if (mario.getLives () > 0 && levelComplete == 1)
    {
      stageComplete ();		//stage complete screen

    }
  //mario has run out of lives and it is game over; ask the user if they would like to play again
  else if (mario.getLives () < 1 && welcome != 0)
    {
      gameOver ();		//game over screen
      playerLost = 1;

    }
}

// performs actions based on key presses
//**** TOOK OUT UPDATES FROM KEY PRESS AND RELEASE AS THEY DIDNT SEEM TO BE DOING ANYTHING*****
void
Draw::keyPressEvent (QKeyEvent * event)
{
	QSound song("./theme.wav");
  switch (event->key ())
    {
    case Qt::Key_A:		//A pressed to move the character to the left
      movingLeft = 1;
      movingRight = 0;
      mario.leftFacing = 1;
      mario.rightFacing = 0;
      break;
    case Qt::Key_D:		//D pressed to move the character to the right
      movingRight = 1;
      movingLeft = 0;
      mario.leftFacing = 0;
      mario.rightFacing = 1;
      break;
    case Qt::Key_W:		//W pressed to jump
      jumping = 1;
      break;
    case Qt::Key_Return:		//P pressed to play again; reloads the board and enemies, resets mario and his lives
      if (levelComplete || gameComplete || playerLost)
	{
	  if (playerLost)
	    {
	      level = 0;
	      score = 0;
	      mario.setLives (3);
	      playerLost = 0;
	    }
	  level += 1;
	  if (level == 1)
	    {
	      mario.setLives (5);
	    }

	  if (level > 1)
	    {
	      score += 100;
	    }
	  if (level > levelMax)
	    {
	      level = 1;
	      score = 0;
	      mario.setLives (3);
	    }
	  levelComplete = 0;
	 cloudRandomize=1;
	  gameComplete = 0;
	  mario.setXPos (50);
	  mario.setYPos (50);
	  loadBoard ();
	  loadEnemies ();
	}
      break;
    case Qt::Key_L:		//P pressed to play again; reloads the board and enemies, resets mario and his lives
      if (debug)
	{
	  levelComplete = 1;
	  if (level == 3)
	    {
	      gameComplete = 1;
	    }
	}
    case Qt::Key_Space:	//Spacebar pressed to begin the game
      welcome = 1;
QSound::play("/theme.wav");
      break;
    case Qt::Key_Escape:
      exit (1);
      break;
    }
}

// performs actions based on key releases
void
Draw::keyReleaseEvent (QKeyEvent * event)
{
  switch (event->key ())
    {
    case Qt::Key_A:		//A released to stop moving the character to the left
      movingLeft = 0;
      break;
    case Qt::Key_D:		//D released to stop moving the character to the right
      movingRight = 0;
      break;
    case Qt::Key_W:		//W pressed to jump
      jumping = 0;
      break;
    case Qt::Key_Escape:
      exit (1);
      break;
    }
}


void
Draw::xChange (unsigned int i)
{


  //prevent from walking into the wall
  for (int z = 0; z < abs (mario.getXVel ()); z++)
    {
      if (mario.getXVel () > 0)
	{
	  mario.setXPos (mario.getXPos () + 1);
	  if ((board[i + 1].getX () - mario.getXPos ()) <
	      (mario.getXSize () * marioScalingFactor)
	      && (mario.getYPos () +
		  mario.getYSize () * marioScalingFactor) >
	      board[i + 1].getY ())
	    {
	      mario.setXPos (board[i + 1].getX () -
			     mario.getXSize () * marioScalingFactor);
	      //   cout << "TEST 1:  wall.." << endl;
	      break;

	    }
	}
      else if (mario.getXVel () < 0)
	{
	  mario.setXPos (mario.getXPos () - 1);
	  if (mario.getXPos () -
	      (board[i - 1].getX () + board[i - 1].getWidth ()) < 1
	      && (mario.getYPos () + mario.getYSize () * marioScalingFactor) >
	      board[i - 1].getY ())
	    {
	      mario.setXPos (board[i - 1].getX () + board[i - 1].getWidth () +
			     1);
	      //  cout << "TEST 2: hitting wall.." << endl;
	      break;
	    }

	}
    }
}

// upates the locations/velocities of the objects onscreen
void
Draw::updatePhysics ()
{
  testCollision ();
  // checks for correct key presses
  if (movingLeft == 1)
    mario.moveLeft ();
  if (movingRight == 1)
    mario.moveRight ();

  // updates the positions based on velocities
  // mario.setXPos (mario.getXPos () + mario.getXVel ());
  mario.setYPos (mario.getYPos () + mario.getYVel ());

  // updates the velocities themselves
  mario.setXVel (mario.getXVel () / 2);
  mario.setYVel (mario.getYVel () + mario.getGravity ());

  // set caps for marios velocities
  if (mario.getXVel () > 15)
    mario.setXVel (15);

  if (mario.getYVel () > 35)
    mario.setYVel (35);

  // platform collision detection
  //loop through the entire board
  int test = 0;
  for (unsigned int i = 0; i < board.size (); i++)
    {
      //test to determine which board the player is on (between the beginning and the width of the board
      if (mario.getXPos () >= board[i].getX ()
	  && mario.getXPos () <= (board[i].getX () + board[i].getWidth ()))
	{
	  test = 1;
	  if (i != 0)
	    xChange (i);
	  //  if (i == 0)
	  //  test = 0;
	  //check ground collision
	  if (mario.getYPos () + (mario.getYSize () * marioScalingFactor) >=
	      board[i].getY ())
	    {
cout << "Board Size " << board.size () << "Line " << i+2 <<
	      endl;
	      mario.setYVel (0);
	      mario.setYPos (board[i].getY () -
			     (mario.getYSize () * marioScalingFactor));
	      //if mario is on the last platform they won
	      //cout << "Board Size " << board.size () << "Platform " << i <<
	      //sendl;
	      if (i == board.size () - 2)
		{
		  // cout << "Game Over";
		  if (level == 3)
		    {
		      gameComplete = 1;
		      levelComplete = 1;
		    }
		  else
		    levelComplete = 1;
		}
	    }
	  // prevents infinity-jumping
	  if (jumping == 1
	      && mario.getYPos () >
	      (board[i].getY () - (mario.getYSize () * marioScalingFactor) -
	       5))
	    {
	      mario.jump ();
	    }
	}
    }
  if (test == 0)
    {
      mario.setXPos (mario.getXPos () + mario.getXVel ());
    }

// test if mario has fallen off the board
  if (mario.getYPos () >= yWindowSize)
    {
      mario.setLives (mario.getLives () - 1);
      mario.setXPos (50);
      mario.setYPos (50);
    }

  // cause the screen to scroll once mario reaches a certain x position
  if (mario.getXPos () >= (double) xWindowSize * (.75))
    {
      mario.setXPos ((double) xWindowSize * (.75));
      //move the board
      for (unsigned int i = 0; i < board.size (); i++)
	{
	  board[i].moveLeft (mario.getXVel ());
	}
      //move the enemies
      for (unsigned int j = 0; j < enemies.size (); j++)
	{
	  enemies[j].moveWithPlatform (mario.getXVel ());
	}
    }

  // prevent mario from going of the left side of the screen
  if (mario.getXPos () < 0)
    {
      mario.setXVel (0);
      mario.setXPos (0);
      //  cout << "Hitting far left border" << endl;
    }
}

// constantly updates the game
void
Draw::timerEvent (QTimerEvent *)
{
  update ();
}


// updates the motion of the enemy
void
Draw::updateEnemy ()
{
//loop through all of the enemies
  for (unsigned int z = 0; z < enemies.size (); z++)
    {
      if (enemies[z].leftFacing == 0 && enemies[z].rightFacing == 0)
	{
	  enemies[z].rightFacing = 1;
	  enemies[z].leftFacing = 0;
	}
      if (enemies[z].getXPos () == enemies[z].getRangeFinish ())
	{
	  enemies[z].leftFacing = 1;
	  enemies[z].rightFacing = 0;
	}
      if (enemies[z].getXPos () == enemies[z].getRangeStart ())
	{
	  enemies[z].rightFacing = 1;
	  enemies[z].leftFacing = 0;
	}
//additional testing for the movement of the board checking if ememies have escaped range
      if (enemies[z].getXPos () > (enemies[z].getRangeFinish ()))
	{
	  enemies[z].setXPos (enemies[z].getRangeFinish () - 1);

	}
      if (enemies[z].getXPos () < (enemies[z].getRangeStart ()))
	{
	  enemies[z].setXPos (enemies[z].getRangeStart () + 1);
	}
//move the enemy the appropriate direction
      if (enemies[z].rightFacing == 1)
	{
	  enemies[z].moveRight ();
	}
      if (enemies[z].leftFacing == 1)
	{
	  enemies[z].moveLeft ();
	}
    }
}

//tests for collisions between mario and the enemies
void
Draw::testCollision ()
{
//tests if the mario is above the enemy and within an appropriate position to squash it
  for (unsigned int z = 0; z < enemies.size (); z++)
    {
      if ((mario.getXPos () < (enemies[z].getXPos () + 40))
	  && (mario.getXPos () > (enemies[z].getXPos () - 40))
	  && (mario.getYPos () < (enemies[z].getYPos () - 18))
	  && (mario.getYPos () > (enemies[z].getYPos () - 65))
	  && (mario.getYVel () > 0))
	{
	  enemies[z].setLives (enemies[z].getLives () - 1);
	  mario.jump ();
	  if (enemies[z].getLives () == 0)
	    {
	      enemies[z].destroyEnemy ();
	    }
	  score += 10;

	}
      else if ((mario.getXPos () < (enemies[z].getXPos () + 40))
	       && (mario.getXPos () > (enemies[z].getXPos () - 40))
	       && (mario.getYVel () == 0)
	       && (mario.getYPos () > (enemies[z].getYPos () - 65)))
	{
	  mario.setLives (mario.getLives () - 1);
	  mario.setXPos (50);
	  mario.setYPos (50);
	}
    }
}

void
Draw::loadBoard ()
{
  string levelString;
  ifstream boardFile;

  switch (level)
    {				//open the appropriate level
    case 1:
      if (debug)
	boardFile.open ("level1.txt");
      else
	boardFile.open ("level1.txt");
      break;
    case 2:
      if (debug)
	boardFile.open ("level2.txt");
      else
	boardFile.open ("level2.txt");
      break;
    case 3:
      if (debug)
	boardFile.open ("level3.txt");
      else
	boardFile.open ("level3.txt");
      break;
    default:
      cout << "Error: Invalid Level: See load board" << endl;
      break;
    }


  board.clear ();

  platform temp (0, 0, 0, 0);
  string tempString;
  char tempCharArray[100];
  char *ptr;
  vector < int >values;

  if (boardFile.is_open ())
    {
      int lineNums;
      boardFile >> lineNums;
      getline (boardFile, tempString);
      for (int i = 0; i < lineNums; i++)
	{
	  getline (boardFile, tempString);
	  for (unsigned int k = 0; k < (tempString.size ()); k++)
	    {
	      tempCharArray[k] = tempString[k];	//converts the line to an array of characters
	    }
	  tempCharArray[tempString.size ()] = NULL;
	  ptr = strtok (tempCharArray, ", ");	//read in a row skipping commas
	  while (ptr != NULL)
	    {
	      values.push_back (atoi (ptr));
	      ptr = strtok (NULL, ", ");
	    }
	  temp.setX (values[0]);
	  temp.setY (values[1]);
	  temp.setWidth (values[2]);
	  temp.setHeight (values[3]);
	  board.push_back (temp);
	  values.clear ();
	}
//boardFile.close();
    }
  else
    {
      cout << "ERROR: File could not be opened" << endl;
    }
}

void
Draw::loadEnemies ()
{

  ifstream enemyFile;
  switch (level)
    {				//open the appropriate level
    case 1:
      if (debug)
	enemyFile.open ("enemy1.txt");
      else
	enemyFile.open ("enemy1.txt");
      break;
    case 2:
      if (debug)
	enemyFile.open ("enemy2.txt");
      else
	enemyFile.open ("enemy2.txt");
      break;
    case 3:
      if (debug)
	enemyFile.open ("enemy3.txt");
      else
	enemyFile.open ("enemy3.txt");
      break;
    default:
      cout << "ERROR: Invalid level: See loadEnemies" << endl;
      break;
    }

  enemies.clear ();

  string tempString;
  char tempCharArray[100];
  char *ptr;
  vector < int >values;


  if (enemyFile.is_open ())
    {
      int lineNums;
      enemyFile >> lineNums;
      getline (enemyFile, tempString);
      for (int i = 0; i < lineNums; i++)
	{
	  getline (enemyFile, tempString);
	  for (unsigned int k = 0; k < (tempString.size ()); k++)
	    {
	      tempCharArray[k] = tempString[k];	//converts the line to an array of characters
	    }
	  tempCharArray[tempString.size ()] = NULL;
	  ptr = strtok (tempCharArray, ", ");	//read in a row skipping commas
	  while (ptr != NULL)
	    {
	      values.push_back (atoi (ptr));
	      ptr = strtok (NULL, ", ");
	    }
	  badguy.update (values[0], values[1], values[2], values[3],
			 values[4], values[5]);
	  enemies.push_back (badguy);
	  values.clear ();
	}
    }
  else
    {
      cout << "ERROR: File could not be opened" << endl;
    }

}

void
Draw::displayStageInfo ()
{
  QPainter painter (this);	// get a painter object to send drawing commands to
  //Set font
  QFont myFont;
  myFont.setPointSizeF (20.0);
  painter.setFont (myFont);

  //Display text of basic info
  int trash;			//stores the length of the array; this is not used
  //display the stage the player is on
  char displayStage[10];
  trash = sprintf (displayStage, "Stage: %d", level);
  painter.drawText (0, 0, 250, 250, 0, displayStage);
  //display number of lives remaining the player has
  char displayLives[10];
  trash = sprintf (displayLives, "Lives: %d", mario.getLives ());
  painter.drawText (270, 0, 200, 200, 0, displayLives);
  //display the score of the player
  char displayScore[15];
  trash = sprintf (displayScore, "Score: %d", score);
  painter.drawText (430, 0, 200, 200, 0, displayScore);


}

void
Draw::displayWelcomeMessage ()
{
  QPainter painter (this);	// get a painter object to send drawing commands to
//set the blackround back
  painter.setBrush (QBrush ("#000000"));
  painter.drawRect (0, 0, xWindowSize, yWindowSize);
  //set the pen to black
  painter.setPen (QPen ("#ffffff"));

  //display image of mario
  QRectF marioTargetRight (100, 100, 1.5 * mario.getXSize (),
			   1.5 * mario.getYSize ());
  QRectF marioSourceRight (0.0, 0.0, mario.getXSize (), mario.getYSize ());
  QPixmap marioPixmapRight ("marioRight.png");
  QPainter (this);
  painter.drawPixmap (marioTargetRight, marioPixmapRight, marioSourceRight);

  //display image of goomba
  QRectF enemyTargetLeft (800, 400, badguy.getXSize (), badguy.getYSize ());
  QRectF enemySourceLeft (0.0, 0.0, badguy.getXSize (), badguy.getYSize ());
  QPixmap enemyPixmapLeft ("goombaLeft.png");
  QPainter (this);
  painter.drawPixmap (enemyTargetLeft, enemyPixmapLeft, enemySourceLeft);

  //set the font size to a large value for the title
  QFont myFont1;
  myFont1.setPointSizeF (40.0);
  painter.setFont (myFont1);
  painter.drawText (200, 25, 600, 600, Qt::AlignHCenter,
		    "WELCOME TO \nSIDE SCROLLER");
  //set the font size smaller for additional info
  QFont myFont2;
  myFont2.setPointSizeF (20.0);
  painter.setFont (myFont2);
  painter.drawText (200, 200, 600, 600, Qt::AlignHCenter,
		    "Justin Bartlett\nJake Flynt\nEli Kloswick");
  painter.drawText (200, 350, 600, 600, Qt::AlignHCenter,
		    "Press 'A' to move left\nPress 'D' to move right\nPress 'W' to jump");
  painter.drawText (200, 500, 600, 600, Qt::AlignHCenter,
		    "Press Space Bar to Continue");

}

void
Draw::drawMario ()
{
	static int animationTimer = 0;

  QPainter painter (this);	// get a painter object to send drawing commands to
// right-facing mario
  QRectF marioTargetRight (mario.getXPos (), mario.getYPos (),
			   mario.getXSize () * marioScalingFactor,
			   mario.getYSize () * marioScalingFactor);
  QRectF marioSourceRight (0.0, 0.0, mario.getXSize (), mario.getYSize ());
  QPixmap marioPixmapRight ("marioRight.png");
  QPainter (this);	
  QPixmap marioPixmapRightOne ("right1.png");
  QPainter (this);
  QPixmap marioPixmapRightTwo ("right2.png");
  QPainter (this);
  QPixmap marioPixmapRightThree ("right3.png");
  QPainter (this);

  // left-facing mario
  QRectF marioTargetLeft (mario.getXPos (), mario.getYPos (),
			  mario.getXSize () * marioScalingFactor,
			  mario.getYSize () * marioScalingFactor);
  QRectF marioSourceLeft (0.0, 0.0, mario.getXSize (), mario.getYSize ());
  QPixmap marioPixmapLeft ("marioLeft.png");
  QPainter (this);
  QPixmap marioPixmapLeftOne ("left1.png");
  QPainter (this);
  QPixmap marioPixmapLeftTwo ("left2.png");
  QPainter (this);
  QPixmap marioPixmapLeftThree ("left3.png");
  QPainter (this);

  // update mario sprite state based on what direction he is moving
  if (mario.rightFacing == 1)
    {
		if (mario.getXVel() != 0)
		{
			if (animationTimer >= 0 && animationTimer < 2)
				painter.drawPixmap (marioTargetRight, marioPixmapRightOne, marioSourceRight);
			else if (animationTimer >= 2 && animationTimer < 4)
				painter.drawPixmap (marioTargetRight, marioPixmapRightTwo, marioSourceRight);
			else if (animationTimer >= 4 && animationTimer < 6)
				painter.drawPixmap (marioTargetRight, marioPixmapRightOne, marioSourceRight);
			else if (animationTimer >= 6 && animationTimer < 8)
				painter.drawPixmap (marioTargetRight, marioPixmapRightThree, marioSourceRight);
			
			if (animationTimer >= 7)
				animationTimer = 0;
			else
				animationTimer++;
		}
		else
			painter.drawPixmap (marioTargetRight, marioPixmapRightOne, marioSourceRight);
    }
  if (mario.leftFacing == 1)
    {
      if (mario.getXVel() != 0)
		{
			if (animationTimer >= 0 && animationTimer < 2)
				painter.drawPixmap (marioTargetLeft, marioPixmapLeftOne, marioSourceLeft);
			else if (animationTimer >= 2 && animationTimer < 4)
				painter.drawPixmap (marioTargetLeft, marioPixmapLeftTwo, marioSourceLeft);
			else if (animationTimer >= 4 && animationTimer < 6)
				painter.drawPixmap (marioTargetLeft, marioPixmapLeftOne, marioSourceLeft);
			else if (animationTimer >= 6 && animationTimer < 8)
				painter.drawPixmap (marioTargetLeft, marioPixmapLeftThree, marioSourceLeft);
			
			if (animationTimer >= 7)
				animationTimer = 0;
			else
				animationTimer++;
		}
		else
			painter.drawPixmap (marioTargetLeft, marioPixmapLeftOne, marioSourceLeft);
    }
}

void
Draw::drawStage ()
{
  QPainter painter (this);	// get a painter object to send drawing commands to
  if (level == levelMax)
    painter.setBrush (QBrush ("#666666"));
  else
    painter.setBrush (QBrush ("#1ac500"));

  for (unsigned int i = 0; i < board.size (); i++)
    {

      painter.drawRect (board[i].getX (), board[i].getY (),
			board[i].getWidth (), board[i].getHeight ());
      if (i == (board.size () - 2))
	{
	  if (level == levelMax)
	    {
	      // draw peach
	      QRectF peachTarget (board[i].getX (), board[i].getY () - 90, 50,
				  96);
	      QRectF peachSource (0.0, 0.0, 100, 193);
	      QPixmap peachPixmap ("peach.png");
	      QPainter (this);
	      painter.drawPixmap (peachTarget, peachPixmap, peachSource);
	    }
	  else
	    {
	      // draw a pipe
	      QRectF pipeTarget (board[i].getX (), board[i].getY () - 60, 80,
				 64);
	      QRectF pipeSource (0.0, 0.0, 80, 64);
	      QPixmap pipePixmap ("pipe2.png");
	      QPainter (this);
	      painter.drawPixmap (pipeTarget, pipePixmap, pipeSource);
	    }
	}
    }
}

void
Draw::drawEnemies ()
{
  QPainter painter (this);	// get a painter object to send drawing commands to
  //loop through all enemies on the board to draw them based on their position


  for (unsigned int z = 0; z < enemies.size (); z++)
    {

      if ((level == levelMax) && (z == (enemies.size () - 1)))
	{
	  {
	    // right-facing enemy
	    QRectF bowserTargetRight (enemies[z].getXPos (),
				      enemies[z].getYPos (),
				      badguy.getXSize () * 1.5,
				      badguy.getYSize () * 1.5);
	    QRectF bowserSourceRight (0.0, 0.0, 200, 202);
	    QPixmap bowserPixmapRight ("bowserRight.png");
	    QPainter (this);

	    // left-facing enemy
	    QRectF bowserTargetLeft (enemies[z].getXPos (),
				     enemies[z].getYPos (),
				     badguy.getXSize () * 1.5,
				     badguy.getYSize () * 1.5);
	    QRectF bowserSourceLeft (0.0, 0.0, 200, 202);
	    QPixmap bowserPixmapLeft ("bowserLeft.png");
	    QPainter (this);


	    //if the enemy has more than 1 life draw them on the board
	    if (enemies[z].getLives () != 0)
	      {
		// update enemy sprite state based on what direction they are moving
		if (enemies[z].rightFacing == 1)
		  {
		    painter.drawPixmap (bowserTargetRight, bowserPixmapRight,
					bowserSourceRight);
		  }

		if (enemies[z].leftFacing == 1)
		  {
		    painter.drawPixmap (bowserTargetLeft, bowserPixmapLeft,
					bowserSourceLeft);
		  }
	      }
	  }
	}

      else
	{
	  // right-facing enemy
	  QRectF enemyTargetRight (enemies[z].getXPos (),
				   enemies[z].getYPos (),
				   badguy.getXSize () / enemyScalingFactor,
				   badguy.getYSize () / enemyScalingFactor);
	  QRectF enemySourceRight (0.0, 0.0, badguy.getXSize (),
				   badguy.getYSize ());
	  QPixmap enemyPixmapRight ("goombaRight.png");
	  QPainter (this);

	  // left-facing enemy
	  QRectF enemyTargetLeft (enemies[z].getXPos (),
				  enemies[z].getYPos (),
				  badguy.getXSize () / enemyScalingFactor,
				  badguy.getYSize () / enemyScalingFactor);
	  QRectF enemySourceLeft (0.0, 0.0, badguy.getXSize (),
				  badguy.getYSize ());
	  QPixmap enemyPixmapLeft ("goombaLeft.png");
	  QPainter (this);


	  //if the enemy has more than 1 life draw them on the board
	  if (enemies[z].getLives () != 0)
	    {
	      // update enemy sprite state based on what direction they are moving
	      if (enemies[z].rightFacing == 1)
		{
		  painter.drawPixmap (enemyTargetRight, enemyPixmapRight,
				      enemySourceRight);
		}

	      if (enemies[z].leftFacing == 1)
		{
		  painter.drawPixmap (enemyTargetLeft, enemyPixmapLeft,
				      enemySourceLeft);
		}
	    }
	}
    }
}


void
Draw::playerWon ()
{
  QPainter painter (this);	// get a painter object to send drawing commands to
  //set backround to black and font to white
  painter.setBrush (QBrush ("#000000"));
  painter.drawRect (0, 0, xWindowSize, yWindowSize);
  painter.setPen (QPen ("#ffffff"));
  QFont myFont;
  myFont.setPointSizeF (60.0);
  painter.setFont (myFont);
  //display text and score to the user
  painter.drawText (200, 100, 600, 600, Qt::AlignHCenter, "YOU\nWIN\n");
  myFont.setPointSizeF (40.0);
  painter.setFont (myFont);
  char displayScore[15];
  int trash;
  trash = sprintf (displayScore, "Score: %d", score);
  painter.drawText (200, 300, 600, 600, Qt::AlignHCenter, displayScore);
  painter.drawText (200, 450, 600, 600, Qt::AlignHCenter,
		    "Press 'P' to play Again\n");
QRectF winTarget(0,0,1000,600);
	  QRectF winSource (0.0, 0.0, 1000, 600);
	  QPixmap winPixmap ("winScreen.png");
	  QPainter (this);
	  painter.drawPixmap (winTarget, winPixmap, winSource);
}

void
Draw::stageComplete ()
{
  QPainter painter (this);	// get a painter object to send drawing commands to
  //set backround to black and pen to red 

  if (level < levelMax - 1)
    {
      painter.setBrush (QBrush ("#000000"));
      painter.drawRect (0, 0, xWindowSize, yWindowSize);
      QFont myFont;
      myFont.setPointSizeF (60.0);
      painter.setFont (myFont);
      painter.setPen (QPen ("#ffffff"));
      //display the stage the user is on now
      int trash;		//stores the length of the array; this is not used
      char displayStage[10];
      trash = sprintf (displayStage, "Stage: %d", level + 1);
      painter.drawText (200, 100, 600, 600, Qt::AlignHCenter, displayStage);

	QRectF stageTarget(0,200,1000,600);
	  QRectF stageSource (0.0, 0.0, 1000, 600);
	  QPixmap stagePixmap ("stageScreen.png");
	  QPainter (this);
	  painter.drawPixmap (stageTarget, stagePixmap, stageSource);
    }
  else
    {
      painter.setBrush (QBrush ("#ff0000"));
      painter.drawRect (0, 0, xWindowSize, yWindowSize);
      QFont myFont;
      myFont.setPointSizeF (50.0);
      painter.setFont (myFont);
      painter.setPen (QPen ("#000000"));
      //display the stage the user is on now
      QRectF finalStageTarget(0,0,1000,600);
      QRectF finalStageSource (0.0, 0.0, 1000, 600);
      QPixmap finalStagePixmap ("bowserScreen.png");
      QPainter (this);
      painter.drawPixmap (finalStageTarget, finalStagePixmap, finalStageSource);

    }

}

void
Draw::gameOver ()
{
  QPainter painter (this);	// get a painter object to send drawing commands to
  //set backround to black and pen to green
  painter.setBrush (QBrush ("#000000"));
  painter.drawRect (0, 0, xWindowSize, yWindowSize);
  painter.setPen (QPen ("#C80000"));
  //print text to screen
  QFont myFont;
  myFont.setPointSizeF (60.0);
  painter.setFont (myFont);
  painter.drawText (200, 100, 600, 600, Qt::AlignHCenter, "GAME \nOVER\n");
  myFont.setPointSizeF (40.0);
  painter.setFont (myFont);
  painter.drawText (200, 350, 600, 600, Qt::AlignHCenter,
		    "Press 'P' to play Again\n");

QRectF overTarget(0,0,1000,600);
	  QRectF overSource (0.0, 0.0, 1000, 600);
	  QPixmap overPixmap ("gameOverScreen.png");
	  QPainter (this);
	  painter.drawPixmap (overTarget, overPixmap, overSource);
}
