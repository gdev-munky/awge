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
	//TODO: нарисовать блокИ, входящие на экран
	// дай мне Х и Y - нарисую 
	string strDeb = "playerX="+ofToString(playerX)+" width="+ofToString(width)+
		" worldSize="+ofToString(worldSize)+" height[0]="+ofToString(height[0]) + "\n" +
		"getHeight(0)="+ofToString(getHeightAtX(1));
	ofDrawBitmapString(strDeb, 50, 100);

	/*
	for(float i = playerX-width; i < playerX+width+1; i += blockSize) 
		for(int j = 0; j <= getHeightAtX(i)/blockSize; j++)
			texBlock.draw(i, getHeightAtX(i)-j*blockSize);
			*/
	int ax = int(floor(playerX/blockSize)) + width;
	int ww = ofGetScreenWidth()/blockSize;
	int sx = max(0, ax-ww);
	int ex = min(width*2, ax+ww);
	float bs = blockSize/2;
	float my = ofGetWindowHeight();
	ofDrawBitmapString(">>"+ofToString(ax)+", ["+ofToString(sx)+", "+ofToString(ex) + "], my="+ofToString(my), 450, 150);
	float blockX;
	for( int x = sx; x < ex; x++ )
	{
		blockX = (x - width) * blockSize - playerX;
		glBegin(GL_QUADS);
			glColor3f(0.8, 0, 0);
			glVertex2f(blockX-bs, my);
			glColor3f(0, 0, 0.8);
			glVertex2f(blockX+bs, my);
			glColor3f(0.8, 0.8, 0);
			glVertex2f(blockX+bs, my - height[x]*blockSize);
			glColor3f(0.8, 1.0, 0.8);
			glVertex2f(blockX-bs, my - height[x]*blockSize);
		glEnd();
	}
	ofDrawBitmapString(">>"+ofToString(blockX), 450, 175);
}