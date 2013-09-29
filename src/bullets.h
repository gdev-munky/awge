#ifndef _BULLETS_H_
#define _BULLETS_H_

#include "ofMain.h"


class bullet_t
{
public:
	
	ofImage* texTracer;
	ofVec2f s, e;
	double a;
	double l;
	int life;

	void setUp(ofVec2f from, ofVec2f to, double angle)
	{
		s = from;
		e = to;
		life = 5+ofRandom(5, 25);
		a = angle;
		l = (e-s).length();
	}
	void draw()
	{
		if (life <= 0) return;
		life--;
		
		//glColor4f(0, 0, 0, 0.25f);
		glTranslated(s.x, s.y, 0);
		glRotated(a, 0, 0, 1);
		texTracer->draw(0, -1, l, 2);
		glRotated(-a, 0, 0, 1);
		glTranslated(-s.x, -s.y, 0);
		glColor3f(1,1,1);

		/*
		glLineWidth(5);
		glBegin(GL_LINES);
			glColor3f(0.1f, 0.01f, 0);			//glColor4f(0, 0, 0, 0);
 			glVertex2f(s.x, s.y);//;			
			glColor3f(1.0f, 0.8f,  0);			//glColor4f(1, 0.5f, 0, 1);
			glVertex2f(e.x, e.y);//;
		glEnd();
		glColor3f(1,1,1);*/
	}
};

#define MAX_BULLETS 64

static bullet_t bullets[MAX_BULLETS];

static void allocateBullet(ofVec2f src, ofVec2f tt, double a)
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].life > 0) continue;
		bullets[i].setUp(src, tt, a);
	}
	bullets[int(ofRandom(0, MAX_BULLETS))].setUp(src, tt, a);
}

#endif