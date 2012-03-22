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

int welcome = 0;		//used to display the welcome message
		//*****SHOULD BE CHANGED FROM A GLOBAL VARIABLE??? HOWEVER I WAS GETTING COMPILER ERRORS WHEN I PUT IT IN THE .H FILE


// Open Window, set title and size.
Draw::Draw (QWidget * parent):QWidget (parent)
{
  setWindowTitle (tr ("2-D Side Scroller"));
  resize (800, 800);
}

// This method is called when the widget needs to be redrawn
void
Draw::paintEvent (QPaintEvent *)
{

  QPainter painter (this);	// get a painter object to send drawing commands to


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
			"Press Any Key To Continue");

//set welcome to 1 so this does not occur again
      welcome = 1;
    }
  else
    {
//Set font
      QFont myFont;
      myFont.setPointSizeF (20.0);
      painter.setFont (myFont);

//Display text of basic info
      painter.drawText (0, 0, 250, 250, 0, "Stage: Test");
      painter.drawText (250, 0, 100, 100, 0, "Lives: 1");


      // Set the colors for each of the painters
      // The Pen is used to draw lines and figure outlines, while the brush is used to fill in the figures

//Draw Basic Stage
      painter.setBrush (QBrush ("#1ac500"));
      painter.drawRect (10, 695, 780, 60);

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
      break;
    case Qt::Key_D:		//D pressed to move the character to the right
      hero.moveRight ();
      break;
    }
//  Instructs the window that the screen needs to be redrawn.
  update ();
}
