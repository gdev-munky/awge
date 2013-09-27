#ifndef _GAMEobJECT_H_
#define _GAMEobJECT_H_

#include "ofMain.h"
#include "Landscape.h"

enum { LEFT, RIGHT, UP, DOWN, K_SHIFT };

class BaseEntity {
public:
	
	void applyForce(ofVec2f force);
	bool isThisObject(int x, int y);

	virtual void spawn(ofVec2f pos) { }
	virtual void kill() { }
	virtual void draw() { }
	virtual void simulation() { }

	ofVec2f	sizeBox;
	ofVec2f	speed;
	ofVec2f	position;
	bool	isLive;
	int		health;
	double	mass;
	double	friction;
	bool	onGround;

	ofImage texBody, texBodyMirror;
	ofImage* texHands;
	ofImage* texHandsMirror;
	bool	bOrientedLeft;

	//ֻאםהראפע
	Landscape* land;

	virtual void jump()	{
		if (onGround) 
		{
			applyForce(ofVec2f(0, -12000));
			onGround = false;
		}
	}
};

#endif