#include "ofMain.h"

class Landscape {
public:
	float	getHeightAtX(float worldX);	
	void	draw(float playerX);
	void	generate(int width, int minBlocks, int maxBlocks);

	float	blockSize;
	int		width;
	float	worldSize;

	ofImage texBlock;
	string	texPath;

private:
	int*	height;
};