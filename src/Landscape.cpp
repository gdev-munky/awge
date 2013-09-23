#include "Landscape.h"


//-------------------------------------
// ���������� ��������, �������� �������, ����������� ������� � ������������ �������, ��� � ������
//-------------------------------------
void	Landscape::generate(int width, int minBlocks, int maxBlocks)
{
	height = new int[width*2];
	height[0] = int(floor(ofRandom(minBlocks, maxBlocks)));
	int last = height[0];

	for (int x = 1; x < width*2; x++)
	{
		//������ ���������� �� ���������� �� ����� ��� �� 2 �����
		height[x] = int(floor(ofRandom(-2,2))) + last;
		if (height[x] > maxBlocks) 
			height[x] = maxBlocks;
		else if (height[x] < minBlocks) 
			height[x] = minBlocks;
		//��������� ��������� ��������������� ������
		last = height[x];
	}

	worldSize = width*blockSize/2;
}

//-------------------------------------
// ������ ��������� �� ���������� X (������� X, ������������� ������)
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
	//TODO: ���������� �����, �������� �� �����
}