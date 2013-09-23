#include "Game.h"
	
int lastKey;
//--------------------------------------------------------------
void AW::setup() {
	ofEnableAntiAliasing(); 
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	//ofSetWindowPosition(100, 40);
	//ofSetupScreen();
	ofSetFullscreen(true);
	
	ofVec2f player_pos;
	player_pos.x = ofGetWidth()/2;
	player_pos.y = 0;

	player.land = new Landscape();
	player.land->generate(1024, 0, 16);
	player.land->blockSize = 32.0f;

	player.spawn( player_pos );
	
    ofSetWindowTitle("AWGE Alpha 0.1");
	counter = 0;

    // TODO: сделать ввод инфы из xml
}	
	
//--------------------------------------------------------------
void AW::update() {
	counter += 2;
	player.simulation();
	

	ofVec2f pos = player.getPosition();
	strDeb = "[DEBUG]\n Player pos = (" + ofToString(pos.x) + "; " + ofToString(pos.y) + ")\n"
			+ "Key = '" + ofToString(lastKey) + "'";
}	
	
//--------------------------------------------------------------
void AW::draw() {
	player.draw();
	player.land->draw(player.position.x);

    // вывод информации на экран
	ofSetColor(0, 0, 0);
	string strFps = "Frame rate: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(strFps, ofGetWidth()-220, 20);

	string strHel = "Health: " + ofToString(player.health);
	ofSetColor(1, 0, 0);
	ofDrawBitmapString(strHel, ofGetWidth()-50, ofGetHeight()-20);

    ofDrawBitmapString("AWGE Alpha 0.1", 20, 20);

	ofDrawBitmapString(strDeb, ofGetWidth()-220, 40); // Debug information
}	
	
//--------------------------------------------------------------
void AW::keyPressed(int key) 
{
	switch(key)
	{
		case 27: ofExit(); return;
		case 356:
		case 97:	player.movingOn(LEFT); break;
		case 357:
		case 119:	player.movingOn(UP); break;
		case 358:	
		case 100:	player.movingOn(RIGHT); break;
	}
}	
	
//--------------------------------------------------------------
void AW::keyReleased(int key) {

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
