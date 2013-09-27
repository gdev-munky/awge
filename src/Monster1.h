#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "BaseMonster.h"

class Monster1 : public BaseMonster {
public:
	void spawn(ofVec2f pos) {
		position = pos;
		setSpeed(0, 0);
		stepSpeed = 150;
		isLive = true;
		health = 20;
		sizeBox.x = sizeM_x[1];
		sizeBox.y = sizeM_y[1];
		mass = 80.0;
		bOrientedLeft = false;
		texBody = monster[1];
		texBodyMirror = monster[1];
		texBodyMirror.mirror(false, true);
	}
};

#endif