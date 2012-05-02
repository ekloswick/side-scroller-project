/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"main.cpp"

Runs the program
 */

#include <QApplication>
#include <QPrinter>
#include <QtGui>
#include "Draw.h"

int main (int argc, char *argv[])
{
	QApplication app (argc, argv);
	Draw p;
	p.show (); // makes the widget

	return app.exec ();
}
