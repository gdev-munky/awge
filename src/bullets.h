#ifndef _BULLETS_H_
#define _BULLETS_H_

#include "ofMain.h"
#include "animation.h"


class bullet_t
{
public:
	AnimatedSequence* texTracer;
	ofVec2f s, e;
	double a;
	double l;
	int life;

	void setUp(ofVec2f from, ofVec2f to, double angle)
	{
		s = from;
		e = to;
		life = 6;
		a = angle;
		l = (e-s).length();
	}
	void draw()
	{
		if (life <= 0) return;
		life--;
		
		glColor4f(1, 1, 1, 0.75f);
		glTranslated(s.x, s.y, 0);
		glRotated(a, 0, 0, 1);
		texTracer->getFrame()->draw(0, -1, l, 2);
		glRotated(-a, 0, 0, 1);
		glTranslated(-s.x, -s.y, 0);
		glColor3f(1, 1, 1);

		texTracer->play(false);
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