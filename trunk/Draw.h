/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */


#ifndef DRAW_H_
#define DRAW_H_
 
#include <QWidget>
#include "character.h"
#include <vector>

using namespace std;

class Draw : public QWidget {
        Q_OBJECT

public:
        Draw(QWidget *parent = 0);
     character hero;

protected:
        void paintEvent(QPaintEvent *e);
        void mousePressEvent(QMouseEvent *e);
        void keyPressEvent(QKeyEvent *event);

private:
        int msleep(unsigned long);
        int xWindowSize;
        int yWindowSize;
        int welcomeMessage;
        vector < int > board;
       

};

#endif
