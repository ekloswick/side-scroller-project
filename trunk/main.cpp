/*
CSE 20212
Final Project: Super Mario Side Scroller 

Created by Jake Flynt, Justin Bartlett, Eli Kloswick.
Copyright 2012. All rights reserved.

"main.cpp"
 */


#include <QApplication>
#include <QPrinter>
#include <QtGui>
#include "Draw.h"

int
main (int argc, char *argv[])
{
  QApplication app (argc, argv);

	QSound song("theme.wav");
	song.play();

  Draw p;

  p.show ();

  return app.exec ();
}
