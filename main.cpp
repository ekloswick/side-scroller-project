/*
 * main.cpp - Driver for the MyPaint class
 * CSE 20212 - Spring 2009
 * 
 * Author: Phil MacCart 
 * 03-01-2009
 * 
 */
 
 
#include <QApplication>
#include <QPrinter>
#include <QtGui>
#include "Draw.h"

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);

     /* import image, display
     QGraphicsScene scene;
     QGraphicsView view(&scene);
     QGraphicsPixmapItem item(QPixmap("mariosprite.jpg"));
     scene.addItem(&item);    
     view.show();
     */

     Draw p;
     //p.addItem(&item);
     p.show();
     return app.exec();
 }

