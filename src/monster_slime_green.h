#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "BaseMonster.h"

class MonsterSlimeGreen : public BaseMonster {
public:
	int myFrame;
	float rnd;
	void spawn(ofVec2f pos) {
		BaseMonster::spawn(pos);
		rnd = ofRandom(0.75f, 1.5f);
		stepSpeed = 150;
		sizeBox.x = 100*rnd;
		sizeBox.y = 60*rnd;
		health = 120*rnd;
		mass = 80*rnd;
		texBodyMirror.mirror(false, true);
		myFrame = int(ofRandom(0, 9));
	}

	void draw(float playerX)
	{
		if (isLive)
		{
			GFXA(iAnimMonsterSlimeGreenMove).current = myFrame;
			GFXA(iAnimMonsterSlimeGreenMove).getFrame()->draw(
				position.x + ofGetWindowWidth()/2 -sizeBox.x/2 -playerX,
				position.y-sizeBox.y/2, sizeBox.x, sizeBox.y);
			GFXA(iAnimMonsterSlimeGreenMove).play(bOrientedLeft);
			myFrame = GFXA(iAnimMonsterSlimeGreenMove).current;
		}
		else
		{			
			if (myFrame == 0)
				return;
			GFXA(iAnimMonsterSlimeGreenDie).current = myFrame;
			GFXA(iAnimMonsterSlimeGreenDie).getFrame()->draw(
				position.x + ofGetWindowWidth()/2 - sizeBox.x/2 - playerX,
				position.y - sizeBox.y/2, sizeBox.x, sizeBox.y);
			if (ofRandom(0,100)<25)
			{
				GFXA(iAnimMonsterSlimeGreenDie).play( false );
				myFrame = GFXA(iAnimMonsterSlimeGreenDie).current;
			}
		}
	}

	void kill()
	{
		BaseMonster::kill();
		myFrame = 1;
	}
};

#endif