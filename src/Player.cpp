#include "Player.h"
double speedI=0;

void Player::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

void Player::setPosition(ofVec2f _position) {
	position = _position;
}

ofVec2f Player::getPosition() {
	return position;
}

void Player::setSpeed(int x, int y) {
	speed.x = x;
	speed.y = y;
}

void Player::setSpeed(ofVec2f _speed) {
	speed = _speed;
}

ofVec2f Player::getSpeed() {
	return speed;
}

void Player::movingOn(int direction) {
	// Types defined in GameObjects.h
	
	switch(direction) {
	case LEFT:
		applyForce(ofVec2f(onGround? -400 : -40,0));
		break;
	case RIGHT:
		applyForce(ofVec2f(onGround? 400 : 40,0));
		break;
	case UP:
		if (onGround)
			jump();
	case K_SHIFT:
		if ( onGround && (abs(speed.x)>20 ) && (abs(speed.x)<50) )
			if(speed.x > 0) speed.x += 20;
			else speed.x -= 20;
		break;
	}
}

void Player::spawn(ofVec2f pos) {
	position = pos;
	setSpeed(0, 0);
	stepSpeed = 150;
	isLive = true;
	health = 100;
	sizeBox.x = 94;
	sizeBox.y = 192;
	mass = 80.0;
	bOrientedLeft = false;
//	timeLeftToShoot = 0;
}

void Player::kill() {
	isLive = false;
	speed.y = 0;
	speed.x = 0;
	health = 0;
}

void Player::draw() 
{
	if (bOrientedLeft)
	{
		texBodyMirror.draw(ofGetWindowWidth()/2-sizeBox.x/2, position.y-sizeBox.y/2);
		
		glTranslated(ofGetWindowWidth()/2, position.y+16, 0);
		glRotated(angle,0,0,1);
		texHandsMirror->draw(-99, -33);
		glRotated(-angle,0,0,1);
		glTranslated(-ofGetWindowWidth()/2, -position.y-16, 0);
	}
	else
	{
		texBody.draw(ofGetWindowWidth()/2-sizeBox.x/2, position.y-sizeBox.y/2);

		glTranslated(ofGetWindowWidth()/2, position.y+16, 0);
		glRotated(angle,0,0,1);
		texHands->draw(-66, -33);
		glRotated(-angle,0,0,1);
		glTranslated(-ofGetWindowWidth()/2, -position.y-16, 0);
	}
}

void Player::simulation() {
	if( !onGround )
		speed.y += 9.8;
	
	/*if (timeLeftToShoot > 0)
		timeLeftToShoot -= 1/70;*/

	double legsPos = position.y + sizeBox.y/2;

	//CHECK BOUNDS
	if (position.x > 64*800-64) {
		position.x = 64*800-64;
		speed.x = min(.0f, speed.x);
	}
	if (position.x < -64*800+64) {
		position.x = 64-64*800;
		speed.x = max(.0f, speed.x);
	}

	double mhRight	= land->getHeightAtX(position.x+sizeBox.x/2);
	double mhRight2 = land->getHeightAtX(position.x+sizeBox.x/2+speed.x/10);
	double mhLeft	= land->getHeightAtX(position.x-sizeBox.x/2);
	double mhLeft2	= land->getHeightAtX(position.x-sizeBox.x/2+speed.x/10);
	double mhCenter = land->getHeightAtX(position.x);

	double maxHeight = double(ofGetScreenHeight()) - max( mhCenter, max( mhLeft, mhRight ));

	//check blocks (X)
	if ((mhLeft2 > mhCenter) && (speed.x < 0) && (legsPos > double(ofGetScreenHeight())-mhLeft2))
	{
		speed.x = 0;
	}
	else 
	if ((mhRight2 > mhCenter) && (speed.x > 0) && (legsPos > double(ofGetScreenHeight())-mhRight2))
	{
		speed.x = 0;
	}
	
	if (legsPos >= maxHeight) {
		if( speed.y > 0 )
			speed.y = 0;
		position.y = maxHeight - sizeBox.y/2;
		onGround = true;
		friction = 0.8f;
	} else {
		onGround = false;
		friction = 0.999f;
	}
	
	position = position + (speed/10);
	speed *= friction;

	if(isLive) {
		if(health == 0) kill();
	}
}