#include "Game.h"
	
int lastKey;
string msg;
bool MouseBtn;


inline void precache()
{
	//GFX
	rStore.precacheANI("textures/tracer", ".png", 6);
	iModelPlayer				= rStore.precacheGFX("textures/afanasich_stand.tga", false, true);	
	iModelWpnAKS74U				= rStore.precacheGFX("textures/wpn_aksu74.png", true, false);
	iModelBackGround			= rStore.precacheGFX("textures/background.png", true, false);
	
	iModelMonsterSlimeGreen		= rStore.precacheGFX("textures/slime.png",		false, true);
	iModelMonsterSlimeGold		= rStore.precacheGFX("textures/slime0.png",		false, true);
	iModelMonsterSlimeBlue		= rStore.precacheGFX("textures/slime1.png",		false, true);
	iModelMonsterGay			= rStore.precacheGFX("textures/monster1.gif",	false, true);

	//SFX	
	iSfxMainTheme				= rStore.precacheSFX("sounds/korn_coming_undone.mp3");
	iSfxBulletHit				= rStore.precacheSFX("sounds/death.wav");
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
	ofSetWindowTitle("AWGE Alpha 0.1");
	ofEnableAntiAliasing();                                          
	ofSetVerticalSync(true);                                         
	ofSetFrameRate(75);												 
	//ofSetFullscreen(true);
	drawDebugInfo = true;
	//precache();
	//GFX
	rStore.precacheANI("textures/tracer", ".png", 6);
	iModelPlayer				= rStore.precacheGFX("textures/afanasich_stand.tga", false, true);	
	iModelWpnAKS74U				= rStore.precacheGFX("textures/wpn_aksu74.png", true, false);
	iModelBackGround			= rStore.precacheGFX("textures/background.png", true, false);
	
	iModelMonsterSlimeGreen		= rStore.precacheGFX("textures/slime.png",		false, true);
	iModelMonsterSlimeGold		= rStore.precacheGFX("textures/slime0.png",		false, true);
	iModelMonsterSlimeBlue		= rStore.precacheGFX("textures/slime1.png",		false, true);
	iModelMonsterGay			= rStore.precacheGFX("textures/monster1.gif",	false, true);

	//SFX	
	iSfxMainTheme				= rStore.precacheSFX("sounds/korn_coming_undone.mp3");
	iSfxBulletHit				= rStore.precacheSFX("sounds/death.wav");

	player.texBody			 = GFXN(iModelPlayer);
	player.texBodyMirror	 = GFXM(iModelPlayer);

	player.texHands			 = GFXN(iModelWpnAKS74U);
	player.texHandsMirror	 = GFXM(iModelWpnAKS74U);
	

	animTracer = GFXA(0);
	for(int i =0; i < MAX_BULLETS; i++)
	{
		bullets[i].texTracer = animTracer;
	}

	player.land->texPath = "textures/ground.tga";
	player.land->generate(10240, 1, 11);
	player.land->blockSize = 64.0f;

	player_pos.x = 0;
	player_pos.y = 0;
	player.spawn( player_pos );

	bMoveLeft = bMoveRight = bMoveUp = bMoveShift = false;

	//Monsters.xml -----------------------------------------------------

	ofVec2f pos;
	for (int i = 0; i < 10; i++)
	{
		pos = player.getPosition();
		BaseMonster m;
		if (ofRandom(0,100) < 50)
			m = (BaseMonster)MonsterSlimeGreen();
		else //if (ofRandom(0,100) < 50)
			m = (BaseMonster)MonsterSlimeGold();		
		

		m.player = &player;
		pos.x += ofRandom(-2048,2048);
		pos.y = 0;
		m.spawn( pos );
		mobs.push_back(&m);
	}
	SFX(iSfxBulletHit)->play();
}	
	
//--------------------------------------------------------------
void AW::update() {
	
	player.simulation();
	for(int i=0; i<mobs.size(); i++)
		mobs[i]->simulation();

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
	GFXN(iModelBackGround)->draw(-flW-delta, 0, flW, flH);
	GFXN(iModelBackGround)->draw(-delta, 0, flW, flH);
	GFXN(iModelBackGround)->draw(flW-delta, 0, flW, flH);
	player.land->draw( player.position.x );
	
	for(int i = 0; i < mobs.size(); i++)
		mobs[i]->draw(player.getPosition().x);
	
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
//DEPRICATED
void AW::mouseMoved(int x, int y) 
{
}	
	
//--------------------------------------------------------------
//DEPRICATED
void AW::mouseDragged(int x, int y, int button) {
	
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

//--------------------------------------------------------------
//DEPRICATED
void AW::windowResized(int w, int h) {

}

//--------------------------------------------------------------
//DEPRICATED
void AW::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
//DEPRICATED
void AW::dragEvent(ofDragInfo dragInfo){

}


void AW::fireBulletsPlayer(ofVec2f vecSrc, float angle, int pellets, int dmg, float spread)
{
	for (int i = 0; i < pellets; i++)
	{
		double a = angle + ofRandom(-spread, spread);
		ofVec2f step = ofVec2f(8, 0).getRotated(a);
		ofVec2f cur = vecSrc;
		for (int j = 0; j < 50; j++)
		{
			cur += step;
			for(int k = 0; k < mobs.size(); k++)
			{
				if (mobs[k]->isThisObject(cur.x, cur.y) && mobs[k]->health>0)
				{
					mobs[k]->health -= dmg;
					sndKill[1].play();
					goto escape;
				}
			}
		}
escape:
					//This will draw our bullet`s tracer over time
		allocateBullet(	ofVec2f(vecSrc.x - player.position.x - player.sizeBox.x/2 + ofGetWindowWidth()/2, vecSrc.y),
						ofVec2f(cur.x	 - player.position.x - player.sizeBox.x/2 + ofGetWindowWidth()/2, cur.y),
						a);
	}
}
