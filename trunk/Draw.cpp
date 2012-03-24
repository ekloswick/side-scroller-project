
/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */


#include "Draw.h"
#include <QtGui>
#include <QPainter>
#include "qlabel.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <QFont>

using namespace std;


// Open Window, set title and size.
Draw::Draw (QWidget * parent) : QWidget (parent)
{
	setWindowTitle (tr ("2-D Side Scroller"));
	resize (800, 800);
	startTimer(100);
}



int Draw::msleep (unsigned long milisec)
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
void Draw::paintEvent (QPaintEvent *)
{
	static int welcome = 0;
	
	QPainter painter (this);	// get a painter object to send drawing commands to

	updatePhysics();

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
		//painter.drawEllipse (hero.getXPos(), hero.getYPos(), 80, 80);

		QRectF target(hero.getXPos(), hero.getYPos(), 56.0, 69.0);
		QRectF source(0.0, 0.0, 56, 69);
		QPixmap pixmap("marioRight.jpg");
		QPainter(this);
		painter.drawPixmap(target, pixmap, source);
	}
}

// Capture mouse clicks
void Draw::mousePressEvent (QMouseEvent * e)
{
	update ();
}

//Performs actions based on key presses
void Draw::keyPressEvent (QKeyEvent * event)
{ 
	switch (event->key ())
	{
		case Qt::Key_A:		//A pressed to move the character to the left
			hero.moveLeft();
			update();
			break;
		case Qt::Key_D:		//D pressed to move the character to the right
			hero.moveRight();
			update();
			break;
		case Qt::Key_W:		//W pressed to jump
			hero.jump();
			update();
			break;
		case Qt::Key_Escape:
			exit(1);
			break;
	}
}

// upates the locations/velocities of the objects onscreen
void Draw::updatePhysics()
{
	// updates the positions based on velocities
	hero.setXPos(hero.getXPos() + hero.getXVel());
	hero.setYPos(hero.getYPos() + hero.getYVel());
	
	// updates the velocities themselves
	hero.setXVel(hero.getXVel() / 2);
	hero.setYVel(hero.getYVel() + hero.getGravity());
	
	// ground collision detection
	if (hero.getYPos() > 626)
		hero.setYPos(626);
	
	// wall collision detection (TEMPORARY)
	if (hero.getXPos() < 0)
		hero.setXPos(10);
	else if (hero.getXPos() > 800)
		hero.setXPos(790);
		
}

// constantly updates the game
void Draw::timerEvent(QTimerEvent *event)
{
	update();
}
