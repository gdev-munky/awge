#ifndef _MONSTER_SLIME_GOLD_H_
#define _MONSTER_SLIME_GOLD_H_

#include "BaseMonster.h"

class MonsterSlimeGold : public BaseMonster {
public:
	float counterDamage;
	int myFrame;
	void spawn(ofVec2f pos) {
		BaseMonster::spawn(pos);
		float rnd = ofRandom(0.9f, 1.9f);
		stepSpeed = 150;
		sizeBox.x = 100*rnd;
		sizeBox.y = 60*rnd;
		health = 200*rnd;
		mass = 90*rnd;
		myFrame = 0;
	}

	void runAI()
	{
		BaseMonster::runAI();
		float dist = player->position.x - position.x;
		if ( dist < 0 )
		{
			bMoveLeft = true;
			bMoveRight = false;
		}
		else
		{			
			bMoveLeft = false;
			bMoveRight = true;
		}

		if (dist > -sizeBox.x/2 && dist < sizeBox.x/2 && counterDamage <= 0)
		{
			player->takeDamge(1.25, true);
			counterDamage = 0.5f;//twice a second
		}
	}

	void simulation()
	{
		BaseMonster::simulation();
		if (counterDamage > 0)
			counterDamage -= 1/ofGetFrameRate();
	}
	void draw(float playerX)
	{
		
		if (isLive)
		{
			GFXA(iAnimMonsterSlimeGoldMove).current = myFrame;
			GFXA(iAnimMonsterSlimeGoldMove).getFrame()->draw(
				position.x + ofGetWindowWidth()/2 -sizeBox.x/2 -playerX,
				position.y-sizeBox.y/2, sizeBox.x, sizeBox.y);
			GFXA(iAnimMonsterSlimeGoldMove).play(bOrientedLeft);
			myFrame = GFXA(iAnimMonsterSlimeGoldMove).current;
		}
		else
		{			
			if (myFrame == 0)
				return;
			GFXA(iAnimMonsterSlimeGoldDie).current = myFrame;
			GFXA(iAnimMonsterSlimeGoldDie).getFrame()->draw(
				position.x + ofGetWindowWidth()/2 - sizeBox.x/2 - playerX,
				position.y - sizeBox.y/2, sizeBox.x, sizeBox.y);
			if (ofRandom(0,100)<25)
			{
				GFXA(iAnimMonsterSlimeGoldDie).play( false );
				myFrame = GFXA(iAnimMonsterSlimeGoldDie).current;
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