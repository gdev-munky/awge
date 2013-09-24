#include "ofMain.h"
#include "Landscape.h"

enum { LEFT, RIGHT, UP, DOWN };

class GameObject {
public:
	
	void applyForce(ofVec2f force);
	bool isThisObject(int x, int y);

	virtual void spawn(ofVec2f pos) { }
	virtual void kill() { }
	virtual void draw() { }
	virtual void simulation() { }

	ofVec2f	sizeBox;
	ofVec2f	speed;
	ofVec2f	position;
	bool	isLive;
	int		health;
	double	mass;
	double	friction;
	bool	onGround;
		
	//ֻאםהראפע
	Landscape* land;

	virtual void jump()	{
		if (onGround) applyForce(ofVec2f(0, -12000));
	}
};