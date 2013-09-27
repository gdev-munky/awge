#include "Game.h"
	
int lastKey;
string msg;

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
	ofSetFullscreen(true);
	drawDebugInfo = true;

	//Sound.xml -----------------------------------------------------
	main_theme.loadSound("sounds/korn_coming_undone.mp3");
	main_theme.play();

	//player.xml -----------------------------------------------------
	player.texBody.loadImage("textures/afanasich_stand.tga");
	player.texBodyMirror.loadImage("textures/afanasich_stand.tga");
	tpWpn_AKSU74.loadImage("textures/wpn_aksu74.png");
	mtpWpn_AKSU74.loadImage("textures/wpn_aksu74.png");
	mtpWpn_AKSU74.mirror(false, true);
	player.texBodyMirror.mirror(false, true);
	player.texHands = &tpWpn_AKSU74;
	player.texHandsMirror = &mtpWpn_AKSU74;

	player.land->texPath = "textures/ground.tga";
	player.land->generate(ofGetWidth(), 1, 12);
	player.land->blockSize = 64.0f;

	player_pos.x = 0;
	player_pos.y = 0;
	player.spawn( player_pos );

	bMoveLeft = bMoveRight = bMoveUp = bMoveShift = false;

	//Monsters.xml -----------------------------------------------------
	monster[1].loadImage("textures/monster11.gif");
	sizeM_x[1] = 150;
	sizeM_y[1] = 230;	
	ofVec2f pos;
	for (int i = 0; i < 10; i++)
	{
		pos = player.getPosition();
		Monster1 m = Monster1();
		m.player = &player;
		pos.x += ofRandom(-2048,2048);
		pos.y = 0;
		m.spawn( pos );
		mobs.push_back(m);
	}
	
}	
	
//--------------------------------------------------------------
void AW::update() {
	counter += 0.33f;
	player.simulation();
	for(int i=0; i<mobs.size(); i++)
		mobs[i].simulation();

	ofVec2f pos = player.getPosition();
	strDeb = "[ DEBUG INFO ]\n"
			 ">> Player pos = (" + ofToString(pos.x) + "; " + ofToString(pos.y) + ")\n>> " + msg;
	if (bMoveLeft)	player.movingOn(LEFT);
	if (bMoveRight)	player.movingOn(RIGHT);
	if (bMoveUp)	player.movingOn(UP);
	if (bMoveShift) player.movingOn(K_SHIFT);

	captureMouseMove();
	
}	
	
//--------------------------------------------------------------
void AW::draw() {
	ofSetColor(255);
	player.land->draw(player.position.x);
	
	for(int i=0; i<mobs.size(); i++)
		mobs[i].draw(player.getPosition().x);
	
	player.draw();
    // вывод информации на экран
	ofSetColor(0, 0, 0);	

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
		player.angle = -asin((my - cy) / dist);
		player.bOrientedLeft = true;
	}
	player.angle/=2*PI;
	player.angle*=360;
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
void AW::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void AW::mouseReleased(int x, int y, int button) {
	
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
