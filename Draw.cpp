
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
#include <QFont>

using namespace std;


// Open Window, set title and size.
Draw::Draw (QWidget * parent):QWidget (parent)
{
	setWindowTitle (tr ("2-D Side Scroller"));

	xWindowSize = 1000;
	yWindowSize = 600;

	resize (xWindowSize, yWindowSize);

	platform temp1(0,500,250,100);
	platform temp2(300,500,100,100);
	platform temp3(400,400,1200,200);
        platform temp4(1700,200,600,200);
	platform temp5(2400,500,300,100);

	board.push_back(temp1);
	board.push_back(temp2);
	board.push_back(temp3);
	board.push_back(temp4);
	board.push_back(temp5);


	// load in enemies

  startTimer (50);
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

  updateEnemy ();
  updatePhysics ();
  testCollision ();

  //Welcome message that is only displayed once
  if (welcome == 0)
    {
      //set the font size to a large value for the title
      QFont myFont1;
      myFont1.setPointSizeF (50.0);
      painter.setFont (myFont1);

      painter.drawText (200, 100, 400, 300, Qt::AlignHCenter,
			"WELCOME TO \nSIDE SCROLLER");

      //set the font size smaller for additional info
      QFont myFont2;
      myFont2.setPointSizeF (25.0);
      painter.setFont (myFont2);

      painter.drawText (200, 300, 400, 200, Qt::AlignHCenter,
			"Justin Bartlett\nJake Flynt\nEli Kloswick");

      painter.drawText (200, 500, 400, 200, Qt::AlignHCenter,
			"Press 'A' to move left\nPress 'D' to move right\nPress 'W' to jump");


      //set welcome to 1 so this does not occur again
      welcome = 1;
    }
  else if (welcome == 1)
    {
      msleep (500);  //****** Set to 500 just to test the code; for final program should be larger value
      welcome = 2;
    }
  else
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
      trash = sprintf (displayLives, "Lives: %d", hero.getLives ());
      painter.drawText (270, 0, 100, 100, 0, displayLives);

      //Draw Basic Stage
      painter.setBrush (QBrush ("#1ac500"));
      
      for (int i = 0; i < board.size(); i++)
         {
      	painter.drawRect ( board[i].getX(), board[i].getY(), board[i].getWidth(), board[i].getHeight() );
	 }
	
      //Draw the Hero
      painter.setBrush (QBrush ("#ffff00"));

      //painter.drawEllipse (badguy.getX (), badguy.getY (), 80, 80);

      // right-facing hero
      QRectF heroTargetRight (hero.getXPos (), hero.getYPos (), hero.getXSize()/3, hero.getYSize()/3);
      QRectF heroSourceRight (0.0, 0.0, hero.getXSize(), hero.getYSize());
      QPixmap heroPixmapRight ("marioRight.png");

      QPainter (this);

      // left-facing hero
      QRectF heroTargetLeft (hero.getXPos (), hero.getYPos (), hero.getXSize()/3, hero.getYSize()/3);
      QRectF heroSourceLeft (0.0, 0.0, hero.getXSize(), hero.getYSize());
      QPixmap heroPixmapLeft ("marioLeft.png");
      QPainter (this);

      // update hero sprite state
      if (hero.rightFacing == 1)
	{
	  painter.drawPixmap (heroTargetRight, heroPixmapRight,
			      heroSourceRight);
	}

      if (hero.leftFacing == 1)
	{
	  painter.drawPixmap (heroTargetLeft, heroPixmapLeft, heroSourceLeft);
	}

      // right-facing enemy
      QRectF enemyTargetRight (badguy.getX (), badguy.getY (), 35.0, 43.0);
      QRectF enemySourceRight (0.0, 0.0, 70, 86);
      QPixmap enemyPixmapRight ("goombaRight.png");
      QPainter (this);

      // left-facing enemy
      QRectF enemyTargetLeft (badguy.getX (), badguy.getY (), 35.0, 43.0);
      QRectF enemySourceLeft (0.0, 0.0, 70, 86);
      QPixmap enemyPixmapLeft ("goombaLeft.png");
      QPainter (this);
/*
   if (badguy.getLife () != 0) 
	{
      painter.drawPixmap (enemyTargetRight, enemyPixmapRight,
			  enemySourceRight);
   
	  // update enemy sprite state
	  if (badguy.right == 1)
	    {
	      painter.drawPixmap (enemyTargetRight, enemyPixmapRight,
				  enemySourceRight);
	    }

	  if (badguy.left == 1)
	    {
	      painter.drawPixmap (enemyTargetLeft, enemyPixmapLeft,
				  enemySourceLeft);
	    }
	}
*/
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
  switch (event->key ())
    {
    case Qt::Key_A:		//A pressed to move the character to the left
      movingLeft = 1;
      // update sprite state
      hero.leftFacing = 1;
      hero.rightFacing = 0;
      update ();
      break;
    case Qt::Key_D:		//D pressed to move the character to the right
      movingRight = 1;
      // update sprite state
      hero.leftFacing = 0;
      hero.rightFacing = 1;
      update ();
      break;
    case Qt::Key_W:		//W pressed to jump
      jumping = 1;
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
testCollision();
  // checks for correct key presses
  if (movingLeft == 1)
    hero.moveLeft ();
  if (movingRight == 1)
    hero.moveRight ();
  
  // prevents infinity-jumping
  for (int i = 0; i < board.size(); i++)
  {    
	  if (jumping == 1 && hero.getYPos () > board[i].getY() - 69)
	    hero.jump ();
  }
	
  // updates the positions based on velocities
  hero.setXPos (hero.getXPos () + hero.getXVel ());
  hero.setYPos (hero.getYPos () + hero.getYVel ());

  // updates the velocities themselves
  hero.setXVel (hero.getXVel () / 2);
  hero.setYVel (hero.getYVel () + hero.getGravity ());

  



// platform collision detection

  for (int i = 0; i < board.size(); i++)
  {

/*
if( (hero.getXPos() - board[i].getX()) >= 0 && 
    (hero.getXPos() - board[i].getX()) <= board[i].getWidth() &&
    (board[i].getY()- hero.getYPos()) >= 0 &&
    (board[i].getY()- hero.getYPos()) <= (hero.getYSize()/3) )
	{
*/	//hero.setYPos(board[i].getY())-(hero.getYSize()/3));

   

  if(hero.getXPos() > board[i].getX() && hero.getXPos() < (board[i].getX() + board[i].getWidth()))
	{	
	if (board[i+1].getY() <	board[i].getY())
	{
		//prevent from walking into the wall
		if ((board[i+1].getX()-hero.getXPos())<(hero.getXSize()/3) &&
		(hero.getYPos() + hero.getYSize()/3) > board[i+1].getY())
		{
			hero.setXPos(board[i+1].getX()-hero.getXSize()/3);
			cout<<"test..."<<endl;

		}
	}
//check ground collision
if (hero.getYPos () > board[i].getY() )
hero.setYPos( board[i].getY()-(hero.getYSize()/3) );

}
}
  



// test if mario has fallen off the board
if (hero.getYPos() >= yWindowSize)
{
	hero.setLives(hero.getLives() -1);
	hero.setXPos(50);
	hero.setYPos(50);
}





  // cause the screen to scroll once mario reaches a certain x position
  

  if (hero.getXPos ()>= (double)xWindowSize*(.75))
	{
	hero.setXPos ((double)xWindowSize*(.75));
	for(int i=0; i<board.size(); i++)
		{
		board[i].moveLeft(hero.getXVel());
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
  if (badguy.left == 0 && badguy.right == 0)
    {
      badguy.moveRight ();
    }
  if (badguy.getX () == 600)
    {
      badguy.left = 1;
      badguy.right = 0;
    }
  if (badguy.getX () == 200)
    {
      badguy.right = 1;
      badguy.left = 0;
    }

  if (badguy.right == 1)
    {
      badguy.moveRight ();
    }
  if (badguy.left == 1)
    {
      badguy.moveLeft ();
    }
}

void
Draw::testCollision ()
{
//tests if the hero is above the enemy and within an appropriate position to squash it
  if ( (hero.getXPos () < (badguy.getX ()+30)) && (hero.getXPos() > (badguy.getX()-30)) && (hero.getYPos() < (badguy.getY()-18)) && (hero.getYPos() > (badguy.getY()-100)) && (hero.getYVel()>0) )
    {
      badguy.setLife (0);
      hero.jump();
      badguy.~enemy();
    }
}
