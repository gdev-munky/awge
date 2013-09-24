#include "Game.h"
	
int lastKey;

//--------------------------------------------------------------
void AW::setup() {
	counter = 0;	
	ofVec2f player_pos;
	player.land = new Landscape();


    //TODO: сделать ввод инфы из xml
	//System.xml ------------------------------------------------------
	ofSetWindowTitle("AWGE Alpha 0.1");
	ofEnableAntiAliasing();                                          
	ofSetVerticalSync(true);                                         
	ofSetFrameRate(60);												 
	ofSetFullscreen(true);
	drawDebugInfo = true;

	//Sound.xml -----------------------------------------------------
	//main_theme.loadSound("sounds/korn_coming_undone.mp3");
	//main_theme.play();
	// ПОКА ЧТО НЕ НУЖНО)))000НАЛЬ

	//Player.xml -----------------------------------------------------
	player.texBody.loadImage("textures/test.tga");

	player.land->texPath = "textures/ground.tga";
	player.land->generate(ofGetWidth(), 5, 10);
	player.land->blockSize = 64.0f;

	player_pos.x = ofGetWidth() / 2;
	player_pos.y = 0;
	player.spawn( player_pos );

	player.stepSpeed = 100;
}	
	
//--------------------------------------------------------------
void AW::update() {
	counter += 0.33f;
	player.simulation();

	ofVec2f pos = player.getPosition();
	strDeb = "  [ DEBUG INFO ]\n"
			 " Player pos = (" + ofToString(pos.x) + "; " + ofToString(pos.y) + ")\n" +
			 " Last key = '" + ofToString(lastKey) + "'";
	if (bMoveLeft)	player.movingOn(LEFT);
	if (bMoveRight)	player.movingOn(RIGHT);
	if (bMoveUp)	player.movingOn(UP);
}	
	
//--------------------------------------------------------------
void AW::draw() {
	player.draw();
	player.land->draw(player.position.x);

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
		case 27: ofExit(); break;
		case 97:	bMoveLeft = true;	player.movingOn(LEFT); break;
		case 32:	bMoveUp = true;		player.movingOn(UP); break;
		case 100:	bMoveRight = true;	player.movingOn(RIGHT); break;
	}
}	
	
//--------------------------------------------------------------
void AW::keyReleased(int key) {
	switch(key)
	{
		case 97:	bMoveLeft = false;	break;
		case 32:	bMoveUp = false;	break;
		case 100:	bMoveRight = false; break;
	}
}
//--------------------------------------------------------------
void AW::mouseMoved(int x, int y) {

}	
	
//--------------------------------------------------------------
void AW::mouseDragged(int x, int y, int button) {
	
}	
	
//--------------------------------------------------------------
void AW::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void AW::mouseReleased(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void AW::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void AW::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void AW::dragEvent(ofDragInfo dragInfo){

}
