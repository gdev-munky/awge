#ifndef _ANIM_H_
#define _ANIM_H_

#include "ofMain.h"

class AnimatedSequence
{
public:
	int count;
	vector<ofImage> frame;
	int current;
	
	AnimatedSequence() {}
	AnimatedSequence(string fname_base, string ext, int c);

	ofImage* getFrame();
	ofImage* getFrame(int i);
	void play(bool back);
};
#endif