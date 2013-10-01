#include "Game.h"
	
int lastKey;
string msg;
bool MouseBtn;
ofSoundPlayer sfxMainTheme;
ofSoundPlayer sfxBulletHit;

 ResStore rStore;

//GFX------------------------------------------------------------
 int iModelPlayer;
 int iModelWpnAKS74U;
 int iModelBackGround;
//GFX - MONSTERS
 int iModelMonsterGay;

 int iAnimMonsterSlimeGreenMove;
 int iAnimMonsterSlimeGreenDie;
 int iAnimMonsterSlimeGoldMove;
 int iAnimMonsterSlimeGoldDie;
 int iAnimMonsterSlimeBlueMove;
 int iAnimMonsterSlimeBlueDie;

//SFX-----------------------------------------------------------
 int iSfxMainTheme;
 int iSfxBulletHit;
 int iSfxFireAKS74U;
 int iSfxWalkDirt;
 int iSfxPain;

inline void precache()
{
	rStore = ResStore();
	//GFX
	rStore.precacheANI("textures/tracer", ".png", 6);
	iModelPlayer				= rStore.precacheGFX("textures/afanasich_stand.tga", false, true);	
	iModelWpnAKS74U				= rStore.precacheGFX("textures/wpn_aksu74.png", true, false);
	iModelBackGround			= rStore.precacheGFX("textures/background.png", true, false);
	
	iModelMonsterGay			= rStore.precacheGFX("textures/monster1.gif",	false, true);

	iAnimMonsterSlimeGreenMove  = rStore.precacheANI("textures/slime_move000", ".png", 10);
	iAnimMonsterSlimeGreenDie	= rStore.precacheANI("textures/slime_die000", ".png", 22);
	iAnimMonsterSlimeGoldMove	= rStore.precacheANI("textures/slime_move000", "_g.png", 10);
	iAnimMonsterSlimeGoldDie	= rStore.precacheANI("textures/slime_die000", "_g.png", 22);
	iAnimMonsterSlimeBlueMove	= rStore.precacheANI("textures/slime_move000", "_b.png", 10);
	iAnimMonsterSlimeBlueDie	= rStore.precacheANI("textures/slime_die000", "_b.png", 22);

	//SFX	
	iSfxMainTheme				= rStore.precacheSFX("sounds/korn_coming_undone.mp3");
	sfxMainTheme				= SFX(iSfxMainTheme);
	iSfxBulletHit				= rStore.precacheSFX("sounds/death.wav");
	sfxBulletHit				= SFX(iSfxBulletHit);
	iSfxFireAKS74U				= rStore.precacheSFX("sounds/aks74u-1.wav");rStore.precacheSFX("sounds/aks74u-2.wav");
	iSfxWalkDirt				= rStore.precacheSFX("sounds/pl_dirt1.wav");
								  rStore.precacheSFX("sounds/pl_dirt2.wav");
								  rStore.precacheSFX("sounds/pl_dirt3.wav");
	iSfxPain					= rStore.precacheSFX("sounds/pl_pain1.wav");
								  rStore.precacheSFX("sounds/pl_pain2.wav");
								  rStore.precacheSFX("sounds/pl_pain3.wav");
}

//--------------------------------------------------------------
void AW::setup() 
{
	msg = "FUCK FUCK FUCK";
	counter = 0;	
	ofVec2f player_pos;
	player.land = new Landscape();

    //TODO: сделать ввод инфы из xml
	//System.xml ------------------------------------------------------
	ofSetWindowTitle("Afanasich Alpha 0.2");
	ofEnableAntiAliasing();                                          
	ofSetVerticalSync(true);                                         
	ofSetFrameRate(75);												 
	ofSetFullscreen(true);
	drawDebugInfo = true;
	precache();

	animTracer = GFXA(0);
	for(int i =0; i < MAX_BULLETS; i++)
	{
		bullets[i].texTracer = &animTracer;
	}

	player.land->texPath = "textures/ground.tga";
	player.land->generate(10240, 1, 15);
	player.land->blockSize = 48.0f;

	player_pos.x = 0;
	player_pos.y = 0;
	player.spawn( player_pos );

	bMoveLeft = bMoveRight = bMoveUp = bMoveShift = false;

	//Monsters.xml -----------------------------------------------------

	ofVec2f pos;
	for (int i = 0; i < 15; i++)
	{
		pos = player.position;
		if (ofRandom(0,100) < 75)
		{
			MonsterSlimeGreen m = (MonsterSlimeGreen());
			m.player = &player;
			pos.x += ofRandom(-2048,2048);
			pos.y = 0;
			m.spawn( pos );
			mobs_greenSlime.push_back(m);
		}
		else if (ofRandom(0,100) < 75)
		{
			MonsterSlimeGold m = (MonsterSlimeGold());	
			m.player = &player;
			pos.x += ofRandom(-2048,2048);
			pos.y = 0;
			m.spawn( pos );
			mobs_goldSlime.push_back(m);	
		}
		else 
		{
			MonsterSlimeBlue m = (MonsterSlimeBlue());	
			m.player = &player;
			pos.x += ofRandom(-2048,2048);
			pos.y = 0;
			m.spawn( pos );
			mobs_blueSlime.push_back(m);	
		}
	}
	//sfxBulletHit.play();
}	
	
//--------------------------------------------------------------
void AW::update() {
	
	player.simulation();
	for(int i=0; i<mobs_greenSlime.size(); i++)
	{
		mobs_greenSlime[i].simulation();
	}
	for(int i=0; i<mobs_goldSlime.size(); i++)
	{
		mobs_goldSlime[i].simulation();
	}
	for(int i=0; i<mobs_blueSlime.size(); i++)
	{
		mobs_blueSlime[i].simulation();
	}

	ofVec2f pos = player.getPosition();
	strDeb = "[ DEBUG INFO ]\n"
			 ">> Player pos = (" + ofToString(pos.x) + "; " + ofToString(pos.y) + ")\n>> " + msg +
			 "\n>> Counter: '" + ofToString(counter) + "'";
	if (bMoveLeft)	player.movingOn(LEFT);
	if (bMoveRight)	player.movingOn(RIGHT);
	if (bMoveUp)	player.movingOn(UP);
	if (bMoveShift) player.movingOn(K_SHIFT);
	if (counter > 0)
		counter -= 1/ofGetFrameRate();
	captureMouseMove();
	if (MouseBtn && counter <= 0)
	{
		SFX( iSfxFireAKS74U + int(ofRandom(0,1)) ).play();
		fireBulletsPlayer(player.getGunPos(), player.angle, 1, 20, 2);
		counter = 0.1f;
	}
}	
	
//--------------------------------------------------------------
void AW::draw() 
{
	ofSetColor(255);
	float flW = ofGetWindowWidth();
	float flH = ofGetWindowHeight();
	float delta = player.position.x-floor(player.position.x/flW)*flW;
	GFXN(iModelBackGround).draw(-flW-delta, 0, flW, flH);
	GFXN(iModelBackGround).draw(-delta, 0, flW, flH);
	GFXN(iModelBackGround).draw(flW-delta, 0, flW, flH);
	player.land->draw( player.position.x );
	
	for(int i=0; i<mobs_greenSlime.size(); i++)
	{
		mobs_greenSlime[i].draw(player.position.x);
	}
	for(int i=0; i<mobs_goldSlime.size(); i++)
	{
		mobs_goldSlime[i].draw(player.position.x);
	}
	for(int i=0; i<mobs_blueSlime.size(); i++)
	{
		mobs_blueSlime[i].draw(player.position.x);
	}
	
	player.draw();
    // вывод информации на экран
	ofSetColor(0, 0, 0);	
	for(int i = 0; i < MAX_BULLETS; i++)
		bullets[i].draw();

	string strHel = "Health: " + ofToString(player.health);
	ofSetColor(ofColor::red);
	ofDrawBitmapString(strHel, ofGetWidth()-150, ofGetHeight()-20);
	ofSetColor(0, 0, 0);
    ofDrawBitmapString("Afanasich Alpha (ver. 0.1)", 20, 20);


	if(drawDebugInfo) 
	{
		string strFps = "Frame rate: " + ofToString(ofGetFrameRate(), 2);
		ofDrawBitmapString(strFps, ofGetWidth()-200, 20);
		ofDrawBitmapString(strDeb, 50, 45);
	}
}	
	
//--------------------------------------------------------------
void AW::keyPressed(int key) 
{
	lastKey = key;

	switch(key)
	{
		case 27:	ofExit(); break;
		case 97:	bMoveLeft	= true;	player.movingOn(LEFT); break;
		case 32:	bMoveUp		= true;	player.movingOn(UP); break;
		case 100:	bMoveRight	= true;	player.movingOn(RIGHT); break;
		case 2305:	bMoveShift	= true;	player.movingOn(K_SHIFT); break;
	}
}	
	
//--------------------------------------------------------------
void AW::keyReleased(int key) {
	switch(key)
	{
		case 97:	bMoveLeft	= false;	break;
		case 32:	bMoveUp		= false;	break;
		case 100:	bMoveRight	= false;	break;
		case 2305:	bMoveShift	= false;	break;
	}
}
void AW::captureMouseMove()
{
	double mx = ofGetMouseX();
	double my = ofGetMouseY();
	double cx = ofGetWindowWidth()/2;
	double cy = player.position.y;
	double dist = sqrt((cx-mx)*(cx-mx) + (cy-my)*(cy-my));

	if (mx >= cx)
	{
		player.angle = asin((my - cy) / dist);
		player.bOrientedLeft = false;
	}
	else
	{
		player.angle = -(asin((my - cy) / dist)-PI);
		player.bOrientedLeft = true;
	}
	player.angle*=180/PI;
}

//--------------------------------------------------------------
void AW::mousePressed(int x, int y, int button) 
{
	MouseBtn = true;
	
}

//--------------------------------------------------------------
void AW::mouseReleased(int x, int y, int button) {
	MouseBtn = false;
}

void AW::fireBulletsPlayer(ofVec2f vecSrc, float angle, int pellets, int dmg, float spread)
{
	for (int i = 0; i < pellets; i++)
	{
		double a = angle + ofRandom(-spread, spread);
		ofVec2f step = ofVec2f(8, 0).getRotated(a);
		ofVec2f cur = vecSrc;
		for (int j = 0; j < 150; j++)
		{
			cur += step;
			for(int k = 0; k < mobs_greenSlime.size(); k++)
			{
				if (mobs_greenSlime[k].isThisObject(cur.x, cur.y) && mobs_greenSlime[k].health>0)
				{
					mobs_greenSlime[k].takeDamge(20, true);
					if (ofRandom(0,100) < 25)
						goto escape;
				}
			}
			for(int k = 0; k < mobs_goldSlime.size(); k++)
			{
				if (mobs_goldSlime[k].isThisObject(cur.x, cur.y) && mobs_goldSlime[k].health>0)
				{
					mobs_goldSlime[k].takeDamge(20, true);
					if (ofRandom(0,100) < 35)
						goto escape;
				}
			}
			for(int k = 0; k < mobs_blueSlime.size(); k++)
			{
				if (mobs_blueSlime[k].isThisObject(cur.x, cur.y) && mobs_blueSlime[k].health>0)
				{
					mobs_blueSlime[k].takeDamge(20, true);
					if (ofRandom(0,100) < 35)
						goto escape;
				}
			}
			if (player.land->getHeightAtX(cur.x-48) >= float(ofGetScreenHeight()) - cur.y)
			{
				ofVec2f cur2 = cur - step/2;
				if (player.land->getHeightAtX(cur2.x-48) >= float(ofGetScreenHeight()) - cur2.y)
					cur = cur2;
				//HIT GROUND
				goto escape;
			}

		}
escape:
					//This will draw our bullet`s tracer over time
		allocateBullet(	ofVec2f(vecSrc.x - player.position.x - player.sizeBox.x/2 + ofGetWindowWidth()/2, vecSrc.y),
						ofVec2f(cur.x	 - player.position.x - player.sizeBox.x/2 + ofGetWindowWidth()/2, cur.y),
						a);
	}
}
