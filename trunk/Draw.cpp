/*
Final_Project
Justin Bartlett 
 */


#include "Draw.h"
#include <QtGui>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Open Window, set title and size.
Draw::Draw(QWidget *parent)
 : QWidget(parent) {
     setWindowTitle(tr("2-D Side Scroller"));
     resize(800, 800);
}

// This method is called when the widget needs to be redrawn
void Draw::paintEvent(QPaintEvent *) {

  //if (dots.size() == 0) return; 

	QPainter painter(this);  //! get a painter object to send drawing commands to
	 
	// a QPainter operates (by default) in pixel coordinates, with the origin
	// at the upper-left corner

	// Set the colors for each of the painters
	// The Pen is used to draw lines and figure outlines, while the brush is used to fill in
	// the figures
	painter.setPen(Qt::cyan);
	painter.setBrush(Qt::darkYellow);
	
	QPen pen(Qt::black, 2, Qt::SolidLine);
	pen.setStyle(Qt::DashDotDotLine);
	painter.drawLine(400, 200, 400, 200);
	
	painter.setPen(QColor("#000000"));

//Draw test
        painter.drawText (0, 0, 300, 100,0, "Welcome to 2-D Side Scroller Project");


        painter.drawText (0, 0, 300, 100,0, "Welcome to 2-D Side Scroller Project");

	painter.setBrush(QBrush("#1ac500"));
	painter.drawRect(10, 695, 780, 60);

	painter.setBrush(QBrush("#ffff00"));
	painter.drawEllipse(hero.getX(), hero.getY(), 80, 80);

}

// The mousePressEvent() function overrides the mousePressEvent() function of the parent QWidget
// class, and is used to capture mouse clicks (either on the button press or the button release).
void Draw::mousePressEvent(QMouseEvent *e) {
	/*************/
	// MOUSE PRESS CODE GOES HERE!!!
	// See QT Documenation to see the data members provided with the QMouseEvent class
	
	

	//  The update() function belongs to the QWidget parent class, and instructs the window
	//  that the screen needs to be redrawn.  Leave this at the end of your mousePressEvent function
	update();
}


void Draw::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
		case Qt::Key_A:
			hero.moveLeft();
			break;
		case Qt::Key_D:
			hero.moveRight();
			break;
	}

	update();
}

