#include "Landscape.h"


//-------------------------------------
// Генерирует ландшафт, задается шириной, минимальной высотой и максимальной высотой, все в блоках
//-------------------------------------
void	Landscape::generate(int width, int minBlocks, int maxBlocks)
{
	height = new int[width*2];
	height[0] = int(floor(ofRandom(minBlocks, maxBlocks)));
	int last = height[0];

	for (int x = 1; x < width*2; x++)
	{
		//высота отличается от предыдущей не более чем на 2 блока
		height[x] = int(floor(ofRandom(-2,2))) + last;
		if (height[x] > maxBlocks) 
			height[x] = maxBlocks;
		else if (height[x] < minBlocks) 
			height[x] = minBlocks;
		//запомнили последнюю сгенерированную высоту
		last = height[x];
	}

	worldSize = width*blockSize/2;
}

//-------------------------------------
// Высота ландшафта по координате X (мировая X, относительная Высота)
//-------------------------------------
float	Landscape::getHeightAtX(float x)
{
	int ax = int(floor(worldSize/x)) - width;
	if (ax < 0)
		ax = 0;
	else if (ax > width)
		ax = width;
	return height[ax]*blockSize;
}

void	Landscape::draw(float playerX)
{
	//TODO: нарисовать блоки, входящие на экран
}