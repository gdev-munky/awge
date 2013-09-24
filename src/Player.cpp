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
		speedI++;
		if (speedI==stepSpeed) speedI=0;
		//что за хуня??? сверху от этой строчки
		speed.x = max( -stepSpeed, speed.x - stepSpeed*speedI );
		break;
	case RIGHT:
		speedI++;
		if (speedI==stepSpeed) speedI=0;
		speed.x = min( stepSpeed, speed.x + stepSpeed*speedI );
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
	speed.y = 0;
	speed.x = 0;
	health = 0;
}

void Player::draw() {
	glBegin(GL_QUADS);
	glColor3f(0.8, 0, 0);
		glVertex2f(ofGetWindowWidth()/2-sizeBox.x/2, position.y-sizeBox.y/2);
		glColor3f(0, 0, 0.8);
		glVertex2f(ofGetWindowWidth()/2+sizeBox.x/2, position.y-sizeBox.y/2);
		glColor3f(0.8, 0.8, 0);
		glVertex2f(ofGetWindowWidth()/2+sizeBox.x/2, position.y+sizeBox.y/2);
		glColor3f(0.8, 1.0, 0.8);
		glVertex2f(ofGetWindowWidth()/2-sizeBox.x/2, position.y+sizeBox.y/2);
	glEnd();
	ofSetColor(255);

	//Отладьте текстуры - потом будете коментить старый код)
	texBody.draw(ofGetWindowWidth()/2, position.y);
}

void Player::simulation() {
	if( !onGround )
		speed.y += 9.8;

	position = position + (speed/10);

	double legsPos = position.y + sizeBox.y/2;
	double maxHeight = float(ofGetScreenHeight())-land->getHeightAtX(position.x);

	if (legsPos > maxHeight) {
		if( speed.y > 0 )
			speed.y = 0;
		position.y = maxHeight - sizeBox.y/2;
		onGround = true;
		friction = 0.8f;
	} else {
		onGround = false;
		friction = 0.999f;
	}
	
	speed *= friction;

	if(isLive) {
		if (health==0) kill();
	}
}