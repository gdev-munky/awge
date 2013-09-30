#include "GameObject.h"

bool BaseEntity::isThisObject(int x, int y) 
{
	return	x >= position.x && x <= (position.x + sizeBox.x) &&
			y >= position.y && y <= (position.y + sizeBox.y);	
		
}

void BaseEntity::applyForce(ofVec2f force)
{
	speed += force/mass;
}

