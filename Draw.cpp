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

using namespace std;


//mario mario (50, 50, 5);
//enemy badguy (400, 400, 1, 10, 400, 200);

// Open Window, set title and size.
Draw::Draw (QWidget * parent):QWidget (parent), mario(50, 50, 5),
		badguy(400, 400, 1, 10, 400, 200)
{

  setWindowTitle (tr ("2-D Side Scroller"));

  xWindowSize = 1000;
  yWindowSize = 600;

  resize (xWindowSize, yWindowSize);

  ifstream myfile ("level.txt");
  string tempString;
  char
    tempCharArray[100];
  char *
    ptr;
  vector < int >
    values;

  platform temp (0, 0, 0, 0);

  if (myfile.is_open ())
    {
      while (myfile.good ())
	{
	  getline (myfile, tempString);
	  for (int k = 0; k < (tempString.size ()); k++)
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
	  cout << "VALUES: " << values[0] << " " << values[1] << " " <<
	    values[2] << " " << values[3] << " " << endl;
	  temp.setX (values[0]);
	  temp.setY (values[1]);
	  temp.setWidth (values[2]);
	  temp.setHeight (values[3]);
	  board.push_back (temp);
	  values.clear ();
	}
    }

  // load in enemies

  startTimer (100);
}

int
Draw::msleep (unsigned long milisec)
{
  struct timespec req = { 0 };

  time_t sec = (int) (milisec / 1000);
  milisec = milisec - (sec * 1000);
  req.tv_sec = sec;
  req.tv_nsec = milisec * 1000000L;

  while (nanosleep (&req, &req) == -1)
    continue;

  return 1;
}

// This method is called when the widget needs to be redrawn
void
Draw::paintEvent (QPaintEvent *)
{
  static int welcome = 0;

  QPainter painter (this);	// get a painter object to send drawing commands to

  if (mario.getLives () > 0)
    {
      updateEnemy ();
      updatePhysics ();
      testCollision ();
    }
  //Welcome message that is only displayed once
  if (welcome == 0)
    {
      //set the font size to a large value for the title
      QFont myFont1;
      myFont1.setPointSizeF (50.0);
      painter.setFont (myFont1);

      painter.drawText (200, 100, 600, 600, Qt::AlignHCenter,
			"WELCOME TO \nSIDE SCROLLER");

      //set the font size smaller for additional info
      QFont myFont2;
      myFont2.setPointSizeF (25.0);
      painter.setFont (myFont2);

      painter.drawText (200, 300, 600, 600, Qt::AlignHCenter,
			"Justin Bartlett\nJake Flynt\nEli Kloswick");

      painter.drawText (200, 450, 600, 600, Qt::AlignHCenter,
			"Press 'A' to move left\nPress 'D' to move right\nPress 'W' to jump");


      //set welcome to 1 so this does not occur again
      welcome = 1;
    }
  else if (welcome == 1)
    {
      msleep (500);		//****** Set to 500 just to test the code; for final program should be larger value
      welcome = 2;
    }
  else if (mario.getLives () > 0 && mario.levelComplete == 0)
    {
      //Set font
      QFont myFont;
      myFont.setPointSizeF (20.0);
      painter.setFont (myFont);

      //Display text of basic info
      painter.drawText (0, 0, 250, 250, 0, "Stage: Test");
      //number of lives remaining
      char displayLives[10];
      int trash;		//stores the length of the array; this is not used
      trash = sprintf (displayLives, "Lives: %d", mario.getLives ());
      painter.drawText (270, 0, 200, 200, 0, displayLives);

      //Draw Basic Stage
      painter.setBrush (QBrush ("#1ac500"));

      for (int i = 0; i < board.size (); i++)
	{
	  painter.drawRect (board[i].getX (), board[i].getY (),
			    board[i].getWidth (), board[i].getHeight ());
	}

      //Draw the mario
      painter.setBrush (QBrush ("#ffff00"));

      // right-facing mario
      QRectF marioTargetRight (mario.getXPos (), mario.getYPos (),
			      mario.getXSize () / 3, mario.getYSize () / 3);
      QRectF marioSourceRight (0.0, 0.0, mario.getXSize (), mario.getYSize ());
      QPixmap marioPixmapRight ("marioRight.png");

      QPainter (this);

      // left-facing mario
      QRectF marioTargetLeft (mario.getXPos (), mario.getYPos (),
			     mario.getXSize () / 3, mario.getYSize () / 3);
      QRectF marioSourceLeft (0.0, 0.0, mario.getXSize (), mario.getYSize ());
      QPixmap marioPixmapLeft ("marioLeft.png");
      QPainter (this);

      // update mario sprite state
      if (mario.rightFacing == 1)
	{
	  painter.drawPixmap (marioTargetRight, marioPixmapRight,
			      marioSourceRight);
	}
      if (mario.leftFacing == 1)
	{
	  painter.drawPixmap (marioTargetLeft, marioPixmapLeft, marioSourceLeft);
	}

      // right-facing enemy
      QRectF enemyTargetRight (badguy.getXPos (), badguy.getYPos (), 35.0,
			       43.0);
      QRectF enemySourceRight (0.0, 0.0, 70, 86);
      QPixmap enemyPixmapRight ("goombaRight.png");
      QPainter (this);

      // left-facing enemy
      QRectF enemyTargetLeft (badguy.getXPos (), badguy.getYPos (), 35.0,
			      43.0);
      QRectF enemySourceLeft (0.0, 0.0, 70, 86);
      QPixmap enemyPixmapLeft ("goombaLeft.png");
      QPainter (this);

      if (badguy.getLives () != 0)
	{
	  painter.drawPixmap (enemyTargetRight, enemyPixmapRight,
			      enemySourceRight);

	  // update enemy sprite state
	  if (badguy.rightFacing == 1)
	    {
	      painter.drawPixmap (enemyTargetRight, enemyPixmapRight,
				  enemySourceRight);
	    }

	  if (badguy.leftFacing == 1)
	    {
	      painter.drawPixmap (enemyTargetLeft, enemyPixmapLeft,
				  enemySourceLeft);
	    }
	}
    }
  else if (mario.getLives () > 0 && mario.levelComplete == 1)
    {
      QFont myFont;
      myFont.setPointSizeF (60.0);
      painter.setFont (myFont);
      painter.drawText (200, 100, 600, 600, Qt::AlignHCenter, "YOU\nWIN\n");
      myFont.setPointSizeF (40.0);
      painter.setFont (myFont);
      painter.drawText (200, 350, 600, 600, Qt::AlignHCenter,
			"Press 'P' to play Again\n");
    }
  else				//game over
    {
      QFont myFont;
      myFont.setPointSizeF (60.0);
      painter.setFont (myFont);
      painter.drawText (200, 100, 600, 600, Qt::AlignHCenter,
			"GAME \nOVER\n");
      myFont.setPointSizeF (40.0);
      painter.setFont (myFont);
      painter.drawText (200, 350, 600, 600, Qt::AlignHCenter,
			"Press 'P' to play Again\n");
    }
}

// Capture mouse clicks
void
Draw::mousePressEvent (QMouseEvent * e)
{
  update ();
}

// performs actions based on key presses
void
Draw::keyPressEvent (QKeyEvent * event)
{
  ifstream myfileTwo ("level.txt");
  string tempStringTwo;
  char tempCharArrayTwo[100];
  char *ptrTwo;
  vector < int >valuesTwo;
  platform tempTwo (0, 0, 0, 0);


  switch (event->key ())
    {
    case Qt::Key_A:		//A pressed to move the character to the left
      movingLeft = 1;
      // update sprite state
      mario.leftFacing = 1;
      mario.rightFacing = 0;
      update ();
      break;
    case Qt::Key_D:		//D pressed to move the character to the right
      movingRight = 1;
      // update sprite state
      mario.leftFacing = 0;
      mario.rightFacing = 1;
      update ();
      break;
    case Qt::Key_W:		//W pressed to jump
      jumping = 1;
      // update sprite state
      update ();
      break;
    case Qt::Key_P:		//P pressed to play again
      mario.setLives (5);
      mario.levelComplete = 0;
      mario.setXPos (50);
      mario.setYPos (50);
      board.clear ();
      if (myfileTwo.is_open ())
	{
	  while (myfileTwo.good ())
	    {
	      getline (myfileTwo, tempStringTwo);
	      for (int k = 0; k < (tempStringTwo.size ()); k++)
		{
		  tempCharArrayTwo[k] = tempStringTwo[k];	//converts the line to an array of characters
		}
	      tempCharArrayTwo[tempStringTwo.size ()] = NULL;
	      ptrTwo = strtok (tempCharArrayTwo, ", ");	//read in a row skipping commas
	      while (ptrTwo != NULL)
		{
		  valuesTwo.push_back (atoi (ptrTwo));
		  ptrTwo = strtok (NULL, ", ");
		}
//cout<<"VALUES: "<<values[0]<<" "<<values[1]<<" "<<values[2]<< " "<<values[3]<< " "<<endl;
	      tempTwo.setX (valuesTwo[0]);
	      tempTwo.setY (valuesTwo[1]);
	      tempTwo.setWidth (valuesTwo[2]);
	      tempTwo.setHeight (valuesTwo[3]);
	      board.push_back (tempTwo);
	      valuesTwo.clear ();
	    }
	}
      // update sprite state
      update ();
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
      update ();
      break;
    case Qt::Key_D:		//D released to stop moving the character to the right
      movingRight = 0;
      update ();
      break;
    case Qt::Key_W:		//W pressed to jump
      jumping = 0;
      update ();
      break;
    case Qt::Key_Escape:
      exit (1);
      break;
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

  // prevents infinity-jumping
  for (int i = 0; i < board.size (); i++)
    {
      if (jumping == 1 && mario.getYPos () > (board[i].getY () - 69))
	mario.jump ();
    }

  // updates the positions based on velocities
  mario.setXPos (mario.getXPos () + mario.getXVel ());
  mario.setYPos (mario.getYPos () + mario.getYVel ());

  // updates the velocities themselves
  mario.setXVel (mario.getXVel () / 2);
  mario.setYVel (mario.getYVel () + mario.getGravity ());

  // platform collision detection

/*
if( (mario.getXPos() - board[i].getX()) >= 0 && 
    (mario.getXPos() - board[i].getX()) <= board[i].getWidth() &&
    (board[i].getY()- mario.getYPos()) >= 0 &&
    (board[i].getY()- mario.getYPos()) <= (mario.getYSize()/3) )
        	{
*///mario.setYPos(board[i].getY())-(mario.getYSize()/3));

  //loop through the entire board
  for (int i = 0; i < board.size (); i++)
    {
      //test to determine which board the player is on (between the beginning and the width of the board
      if (mario.getXPos () > board[i].getX ()
	  && mario.getXPos () < (board[i].getX () + board[i].getWidth ()))
	{
	  //test if the next board is higher than the players position 
	  if (board[i + 1].getY () < board[i].getY ())
	    {
	      //prevent from walking into the wall
	      if ((board[i + 1].getX () - mario.getXPos ()) <
		  (mario.getXSize () / 3)
		  && (mario.getYPos () + mario.getYSize () / 3) >
		  board[i + 1].getY ())
		{
		  mario.setXPos (board[i + 1].getX () - mario.getXSize () / 3);
		  cout << "TEST 1: hitting wall.." << endl;

		}
	    }
	     /* //test if the previous board is higher than the players position
	      if (board[i - 1].getY () < board[i].getY ())
		{
		    //prevent from walking into the wall behind them
		  if (mario.getXPos () -  (board[i - 1].getX () + board[i - 1].getWidth ()) < 5
		      && (mario.getYPos () + mario.getYSize () / 3) >  board[i - 1].getY ())
		    {
		      mario.setXVel(0);
		      mario.setXPos (board[i - 1].getX ()+board[i-1].getWidth()+1);
		      cout << "TEST 2: hitting wall.." << endl;
		    }
		}
*/
	    

	  //check ground collision
	  if (mario.getYPos () + (mario.getYSize () / 3) >= board[i].getY ())
	    {
	      mario.setYVel (0);
	      mario.setYPos (board[i].getY () - (mario.getYSize () / 3));

	      //if mario is on the last platform they won
	      cout << "Board Size " << board.
		size () << "Platform " << i << endl;
	      if (i == board.size () - 1)
		{
		  cout << "Game Over";
		  mario.levelComplete = 1;
		}
	    }

	}
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
      for (int i = 0; i < board.size (); i++)
	{
	  board[i].moveLeft (mario.getXVel ());
	}
    }

}

// constantly updates the game
void
Draw::timerEvent (QTimerEvent * event)
{
  update ();
}

// updates the motion of the enemy
void
Draw::updateEnemy ()
{
  if (badguy.leftFacing == 0 && badguy.rightFacing == 0)
    {
      badguy.moveRight ();
    }
  if (badguy.getXPos () ==
      (badguy.getRangeStart () + badguy.getRangeFinish ()))
    {
      badguy.leftFacing = 1;
      badguy.rightFacing = 0;
    }
  if (badguy.getXPos () == badguy.getRangeStart ())
    {
      badguy.rightFacing = 1;
      badguy.leftFacing = 0;
    }

  if (badguy.rightFacing == 1)
    {
      badguy.moveRight ();
    }
  if (badguy.leftFacing == 1)
    {
      badguy.moveLeft ();
    }
}

void
Draw::testCollision ()
{
//tests if the mario is above the enemy and within an appropriate position to squash it
  if ((mario.getXPos () < (badguy.getXPos () + 30))
      && (mario.getXPos () > (badguy.getXPos () - 30))
      && (mario.getYPos () < (badguy.getYPos () - 18))
      && (mario.getYPos () > (badguy.getYPos () - 100))
      && (mario.getYVel () > 0))
    {
      badguy.setLives (0);
      mario.jump ();
      badguy. ~ enemy ();
    }
}
