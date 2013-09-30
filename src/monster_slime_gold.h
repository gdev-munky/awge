#ifndef _MONSTER_SLIME_GOLD_H_
#define _MONSTER_SLIME_GOLD_H_

#include "BaseMonster.h"

class MonsterSlimeGold : public BaseMonster {
public:
	float counterDamage;

	void spawn(ofVec2f pos) {
		BaseMonster::spawn(pos);
		float rnd = ofRandom(0.9f, 3.0f);
		stepSpeed = 150;
		sizeBox.x = 100*rnd;
		sizeBox.y = 60*rnd;
		texBody = &monster[2];
		texBodyMirror = &monster[2];
		texBodyMirror->mirror(false, true);
		health = 200*rnd;
		mass = 90*rnd;
		texBody = GFXN(iModelMonsterSlimeGold);
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

		if (dist > -sizeBox.x/2 && dist > sizeBox.x/2 && counterDamage <= 0)
		{
			player->takeDamge(5, true);
			counterDamage = 0.5f;//twice a second
		}
	}

	void simulation()
	{
		BaseMonster::simulation();
		if (counterDamage > 0)
			counterDamage -= 1/ofGetFrameRate();
	}
};

#endif