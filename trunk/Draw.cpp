
/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */


#include "Draw.h"
#include <QtGui>
#include <iostream>
#include <fstream>
#include <cmath>
#include <QFont>


using namespace std;


// Open Window, set title and size.
Draw::Draw (QWidget * parent):QWidget (parent)
{
  setWindowTitle (tr ("2-D Side Scroller"));
  xWindowSize = 800;
  yWindowSize = 800;
  resize (xWindowSize, yWindowSize);

  welcomeMessage = 0;		//used to display the welcome message
  int
  myints[] = { 0, 600, 800, 20 };
  for (int i = 0; i < 4; i++)
    {
      board.push_back (myints[i]);
    }
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

  QPainter painter (this);	// get a painter object to send drawing commands to


//Welcome message that is only displayed once
  if (welcomeMessage == 0)
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
			"Press Any Key To Continue");

//set welcome to 1 so this does not occur again
      welcomeMessage = 1;
    }
  else
    {
//Set font
      QFont myFont;
      myFont.setPointSizeF (20.0);
      painter.setFont (myFont);

//Display text of basic info

//stage name
      painter.drawText (0, 0, 250, 250, 0, "Stage: Test");
//number of lives remaining
      char displayLives[33];
      int trash;		//stores the length of the array; this is not used
      trash = sprintf (displayLives, "Lives: %d", hero.getLives ());
      painter.drawText (270, 0, 100, 100, 0, displayLives);

      // Set the colors for each of the painters
      // The Pen is used to draw lines and figure outlines, while the brush is used to fill in the figures

//Draw Basic Stage
      painter.setBrush (QBrush ("#1ac500"));
      painter.drawRect (board[0], board[1], board[2], board[3]);	//x,y,width,height




//Draw the Hero
      painter.setBrush (QBrush ("#ffff00"));
      painter.drawEllipse (hero.getX (), hero.getY (), 80, 80);
    }
}

// Capture mouse clicks
void
Draw::mousePressEvent (QMouseEvent * e)
{


  //  Instructs the window that the screen needs to be redrawn.
  update ();
}

//Performs actions based on key presses
void
Draw::keyPressEvent (QKeyEvent * event)
{
  switch (event->key ())
    {
    case Qt::Key_A:		//A pressed to move the character to the left
      hero.moveLeft ();
      update ();
      break;
    case Qt::Key_D:		//D pressed to move the character to the right
      hero.moveRight ();
      update ();
      break;
    case Qt::Key_W:		//D pressed to move the character to the right
      for (int j = 0; j < 30; j++)
	{
	  hero.setY (hero.getY () - 2);
	  repaint (0, 0, 800, 800);
	}
      msleep (100);

      for (int j = 0; j < 30; j++)
	{
	  hero.setY (hero.getY () + 2);
	  repaint (0, 0, 800, 800);
	}

      break;
    }
//  Instructs the window that the screen needs to be redrawn.
  // update ();
}
