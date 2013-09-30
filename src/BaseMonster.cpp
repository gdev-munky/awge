#include "BaseMonster.h"
#include "resources.h"

BaseMonster::BaseMonster(void) 
{

}

BaseMonster::~BaseMonster(void) {

}

void BaseMonster::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

void BaseMonster::setPosition(ofVec2f _position) {
	position = _position;
}

ofVec2f BaseMonster::getPosition() {
	return position;
}

void BaseMonster::setSpeed(int x, int y) {
	speed.x = x;
	speed.y = y;
}

void BaseMonster::setSpeed(ofVec2f _speed) {
	speed = _speed;
}

ofVec2f BaseMonster::getSpeed() {
	return speed;
}

void BaseMonster::movingOn(int direction) {
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

		break;
	}
}

void BaseMonster::spawn(ofVec2f pos) {
	position = pos;
	setSpeed(0, 0);
	stepSpeed = 60;
	isLive = true;
	health = 100;
	sizeBox.x = 94;
	sizeBox.y = 192;
	mass = 80.0;
	bOrientedLeft = false;
}

void BaseMonster::kill() {
	isLive = false;
	speed.y = 0;
	speed.x = 0;
	health = 0;
	sndKill[1].play();
	texBody = GFXN(iModelMonsterGay);
	counter = ofRandom(3, 5);
}

void BaseMonster::draw(float playerX) 
{	
	if (bOrientedLeft)
		texBodyMirror->draw(position.x+ofGetWindowWidth()/2-sizeBox.x/2-playerX, position.y-sizeBox.y/2, sizeBox.x, sizeBox.y);
	else
		texBody->draw(position.x+ofGetWindowWidth()/2-sizeBox.x/2-playerX, position.y-sizeBox.y/2, sizeBox.x, sizeBox.y);
}

void BaseMonster::simulation() 
{	
	if (counter > 0)
	{
		counter -= 1/ofGetFrameRate();
		if (counter <= 0)
		{
			spawn(ofVec2f(player->getPosition().x + ofRandom(-2000, 2000), 0));
		}
	}
	if( !onGround )
		speed.y += 9.8;
	bOrientedLeft = (speed.x < 0);

	double legsPos = position.y + sizeBox.y/2;

	//CHECK BOUNDS
	if (position.x > 64*800-64) 
	{
		position.x = 64*800-64;
		speed.x = min(.0f, speed.x);
	}
	if (position.x < -64*800+64) {
		position.x = 64-64*800;
		speed.x = max(.0f, speed.x);
	}

	double dist = max(position.x - player->position.x, player->position.x - position.x);
	if (dist > 2*ofGetScreenWidth())
	{
		ofVec2f pos = player->getPosition();
		pos.x += ofRandom(-2048, 2048);
		pos.y = 0;
		spawn( pos );
	}

	double mhRight = player->land->getHeightAtX(position.x+sizeBox.x/2);
	double mhRight2 = player->land->getHeightAtX(position.x+sizeBox.x/2+speed.x/10);
	double mhLeft = player->land->getHeightAtX(position.x-sizeBox.x/2);
	double mhLeft2 = player->land->getHeightAtX(position.x-sizeBox.x/2+speed.x/10);
	double mhCenter = player->land->getHeightAtX(position.x);

	double maxHeight = double(ofGetScreenHeight()) - max( mhCenter, max( mhLeft, mhRight ));
	//check blocks (X)
	
	if ((mhLeft2 > mhCenter) && (speed.x < 0) && (legsPos > double(ofGetScreenHeight())-mhLeft2))
		speed.x = 0;
	else 
		if ((mhRight2 > mhCenter) && (speed.x > 0) && (legsPos > double(ofGetScreenHeight())-mhRight2)) 
			speed.x = 0;
	
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
	sndKill[1].play();
	
	position = position + (speed/10);
	speed *= friction;
	
	if(isLive)
	{
		sndKill[1].play();
		if(health <= 0) 
		{
			kill();
			sndKill[1].play();
			return;
		}
		runAI();
		if (bMoveLeft)	movingOn(LEFT);
		if (bMoveRight)	movingOn(RIGHT);
	}
}

void BaseMonster::runAI()
{
	if (ofRandom(0,100) < 10)
	{
		bMoveLeft = !bMoveLeft;
		bMoveRight = !bMoveLeft;
	}
	else if (ofRandom(0,100) < 10)
	{
		bMoveRight = !bMoveRight;
		bMoveLeft = !bMoveRight;
	}
	if (ofRandom(0, 100) < 20 && onGround)
	{
		jump();
	}
}