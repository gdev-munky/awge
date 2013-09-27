#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "BaseMonster.h"
#include "Monster1.h"

class AW : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void captureMouseMove();

		ofSoundPlayer main_theme;
		Player player;

		// debug info
		bool drawDebugInfo;
		string strDeb; 
		
		float counter;

		//Состояния клавиш (Munky)
		bool bMoveLeft, bMoveUp, bMoveRight, bMoveShift;

		vector<Monster1> mobs;
};

#endif