/*
Final_Project
Justin Bartlett, Jake Flynt, Eli Kloswick
 */


#ifndef DRAW_H_
#define DRAW_H_
 
#include <QWidget>
#include "character.h"
#include "enemy.h"
#include "hero.h"
#include "platform.h"
#include <vector>

using namespace std;


class Draw : public QWidget
{
     Q_OBJECT

	public:
		Draw(QWidget *parent = 0);


	protected:
		void paintEvent(QPaintEvent *e);
		//void mousePressEvent(QMouseEvent *e);
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
		void updatePhysics();
		void timerEvent(QTimerEvent *);
                void updateEnemy();
		void testCollision();


	private:
		int msleep(unsigned long);
		int xWindowSize;
		int yWindowSize;
		int movingLeft;
		int movingRight;
		int jumping;
		vector < platform > board;
		hero mario;
		enemy badguy;
		vector < enemy > enemies;

		void loadBoard();
		void loadEnemies();
		int welcome;
int drawScalingFactor;
};

#endif
