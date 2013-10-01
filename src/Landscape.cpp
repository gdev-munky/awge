#include "Landscape.h"

//-------------------------------------
// Генерирует ландшафт, задается шириной, минимальной высотой и максимальной высотой, все в блоках
//-------------------------------------
void Landscape::generate(int _width, int minBlocks, int maxBlocks)
{
	width = _width;
	height = new int[width*2];
	height[0] = int(floor(ofRandom(minBlocks, maxBlocks)));
	int last = height[0];

	for (int x=1; x < width*2; x++)
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

	//инициализация текстуры блоков
	texBlock.loadImage(texPath);
}

//-------------------------------------
// Высота ландшафта по координате X (мировая X, относительная Высота)
//-------------------------------------
float Landscape::getHeightAtX(float x) // f(0) not exist
{
	int ax = int(floor(x/blockSize)) + width;

	if (ax < 0)
		ax = 0;
	else if (ax > 2*width)
		ax = width;
	
	return height[ax]*blockSize;
}

void Landscape::draw(float playerX)
{
	int x=1, y=getHeightAtX(x);

	int ax = int(floor(playerX/blockSize)) + width;
	int ww = ofGetScreenWidth()/blockSize;
	int sx = max(0, ax-ww);
	int ex = min(width*2, ax+ww);
	float bs = blockSize/2;
	float my = ofGetWindowHeight();
	float blockX;

	for( int x = sx; x < ex; x++ )
	{
		blockX = (x - width) * blockSize - playerX + ofGetScreenWidth()/2;
		ofSetColor(255);	
		for( int y = 1; y <= height[x]; y++ )
		{
			texBlock.draw(blockX, my-y*blockSize, blockSize, blockSize);
		}
	}
}