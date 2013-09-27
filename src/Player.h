#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"

static ofImage tpWpn_Pistol;
static ofImage tpWpn_Magnum;
static ofImage tpWpn_AKSU74;
static ofImage mtpWpn_AKSU74;
static ofImage tpWpn_Shotgun;


class Player : public BaseEntity {
public:
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
	virtual void draw();
	double angle;
};

#endif