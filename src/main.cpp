#include "ofMain.h"
#include "Game.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024, 768, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new AW());
}
