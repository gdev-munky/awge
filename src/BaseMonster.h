#ifndef _BASEMONSTER_H_
#define _BASEMONSTER_H_

#include "GameObject.h"
#include "Player.h"

const int MAXMOBS = 50;
static ofImage monster[3], monsterKill[3];
static ofSoundPlayer sndKill[3];
static int countM1, countM2, countM3;
static int sizeM_x[3], sizeM_y[3];

class BaseMonster : public BaseEntity {
public:
	BaseMonster(void);
	~BaseMonster(void);

	void	setPosition(int x, int y);
	void	setPosition(ofVec2f _position);
	ofVec2f getPosition();

	void	setSpeed(int x, int y);
	void	setSpeed(ofVec2f _speed);
	ofVec2f getSpeed();

	void	movingOn(int direction);
	double	stepSpeed;

	virtual void spawn(ofVec2f pos);
	virtual void kill();
	virtual void simulation();
	virtual void draw(float playerX);

	virtual void runAI();
		bool bMoveLeft, bMoveUp, bMoveRight;

	Player* player;

	float counter;

};

#endif