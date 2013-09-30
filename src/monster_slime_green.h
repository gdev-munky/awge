#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "BaseMonster.h"

class MonsterSlimeGreen : public BaseMonster {
public:
	void spawn(ofVec2f pos) {
		BaseMonster::spawn(pos);
		float rnd = ofRandom(0.75f, 2.5f);
		stepSpeed = 150;
		sizeBox.x = 100*rnd;
		sizeBox.y = 60*rnd;
		texBody = &monster[1];
		texBodyMirror = &monster[1];
		texBodyMirror->mirror(false, true);
		health = 120*rnd;
		mass = 80*rnd;
		texBody = GFXN(iModelMonsterSlimeGreen);
	}
};

#endif