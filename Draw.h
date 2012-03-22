/*
 * MyPaint.cpp - Implementation of the MyPaint class
 * CSE 20212 - Spring 2009
 * 
 * The MyPaint class creates a paint object capable of capturing mouse clicks, drawing dots at the point of the mouse click,
 * then constructing a minimum spanning tree connecting the points.
 * 
 * Author: Phil MacCart 
 * 03-01-2009
 * 
 */

#ifndef DRAW_H_
#define DRAW_H_
 
//!
//! Yo: the Q_OBJECT macro tells us that this class can have
//! slots and signals.  It also tells qmake to compile this
//! class in a special way
//!

#include <QWidget>
#include "character.h"

using namespace std;

class Draw : public QWidget {
 	Q_OBJECT

public:
	Draw(QWidget *parent = 0);
        character hero;

protected:
	void paintEvent(QPaintEvent *e);
	void mousePressEvent(QMouseEvent *e);

private:

};

#endif

