#ifndef _GAME_H_
#define _GAME_H_

#include "resources.h"
#include "Player.h"
#include "BaseMonster.h"
#include "bullets.h"
#include "animation.h"

#include "monster_slime_green.h"
#include "monster_slime_gold.h"
#include "monster_slime_blue.h"


class AW : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		void captureMouseMove();

		ofSoundPlayer* main_theme;
		Player player;

		// debug info
		bool drawDebugInfo;
		string strDeb; 
		
		float counter;

		//Состояния клавиш (Munky)
		bool bMoveLeft, bMoveUp, bMoveRight, bMoveShift;

		vector<MonsterSlimeGreen> mobs_greenSlime;
		vector<MonsterSlimeGold> mobs_goldSlime;
		vector<MonsterSlimeBlue> mobs_blueSlime;
		void fireBulletsPlayer(ofVec2f vecSrc, float angle, int pellets, int dmg, float spread);
		
		//ofImage texTracer;
		AnimatedSequence animTracer;
};

#endif