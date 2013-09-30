#include "animation.h"

AnimatedSequence::AnimatedSequence(string a, string b, int c)
{
	count = c;
	current = 0;
	for (int i = 0; i < c; i++)
	{
		frame.push_back(ofImage(a + ofToString(i) + b));
	}
}

ofImage* AnimatedSequence::getFrame()
{
	return &(frame[current]);
}

ofImage* AnimatedSequence::getFrame(int i)
{
	return &(frame[max(min(i, count-1), 0)]);
}

void AnimatedSequence::play(bool back)
{
	if (back)
	{
		current = (current == 0) ? count-1 : current-1;
	}
	else
	{
		current++;
		if (current >= count) current = 0;
	}
}