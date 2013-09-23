#include "GameObject.h"

class Player : public GameObject {
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
	virtual void draw();
	virtual void simulation();

};