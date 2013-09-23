#include "GameObject.h"

bool GameObject::isThisObject(int x, int y) {
	if( x >= position.x && x <= (position.x + sizeBox.x) &&
		y >= position.y && y <= (position.y + sizeBox.y) ) 
		return 1;
	else 
		return 0;
		
}

void GameObject::applyForce(ofVec2f force)
{
	speed += force/mass;
}