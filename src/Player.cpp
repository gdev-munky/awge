#include "Player.h"

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
		speed.x = max( -stepSpeed, speed.x - stepSpeed/10 );
		break;
	case RIGHT:
		speed.x = min( stepSpeed, speed.x + stepSpeed/10 );
		break;
	case UP:
		jump();
		break;
	}
}

void Player::spawn(ofVec2f pos) {
	position = pos;
	setSpeed(0, 0);
	stepSpeed = 60;
	isLive = true;
	health = 100;
	sizeBox.x = 40;
	sizeBox.y = 80;
	mass = 80.0;
}

void Player::kill() {
	isLive = false;
	health = 0;
}

void Player::draw() {
	glColor3f(0.8, 0, 0);
	glBegin(GL_QUADS);
		glVertex2f(position.x-sizeBox.x/2, position.y-sizeBox.y/2);
		glVertex2f(position.x+sizeBox.x/2, position.y-sizeBox.y/2);
		glVertex2f(position.x+sizeBox.x/2, position.y+sizeBox.y/2);
		glVertex2f(position.x-sizeBox.x/2, position.y+sizeBox.y/2);
	glEnd();
}

void Player::simulation() {
	if( !onGround )
		speed.y += 9.8; // slooowly

	position = position + (speed/10);
	double legsPos = position.y + sizeBox.y/2;
	double maxHeight = float(ofGetScreenHeight())-land->getHeightAtX(position.x);
	if (legsPos > maxHeight) 
	{
		if( speed.y > 0 )
			speed.y = 0;
		position.y = maxHeight - sizeBox.y/2;
		onGround = true;
		friction = 0.8;
	} 
	else 
	{
		onGround = false;
		friction = 0.999;
	}
	
	speed *= friction;

	if(isLive) 
	{

	}
}