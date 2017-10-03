#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, demoParticle());
    
    // I have changed the stating mode to the 'noise' from mode 'attract'
	currentMode = PARTICLE_MODE_NOISE;

    // I have removed the code bellow as I am not needing to change mode
	// currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";

	resetParticles();
    
    // Loading the piece of Audio
    music.load("nature.mp3");
    // Setting the Volume for the track
    music.setVolume(0.5f);
    // Playing the audio
    music.play();
    
    fftSmooth = new float [8192];
    for (int i = 0; i < 8192; i++){
        fftSmooth[i] = 0;
        
        music.setLoop(true);
        bands = 64;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the forth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].update();
	}
	
	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}
    
    ofSoundUpdate();
    float * value = ofSoundGetSpectrum(bands);
    for (int i = 0; i < bands; i++) {
        fftSmooth[i] *= 0.9f;
        if (fftSmooth[i] < value[i]) {
            fftSmooth[i] = value[i];
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for (int i = 0; i < bands; i++){
        
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, -(fftSmooth[i]*3000));
    }
    
    // I have changed the background grdient to white from (60, 60, 60/ 10, 10, 10)
    ofBackgroundGradient(ofColor:: white, ofColor:: gray);

    // The code bellow draws the particles!
    
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
	}


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // I have removed all 'if key pressed' actions as I am not changing mode in this project
    // I have changed noise to '1' and repel to '2'
    // I gave removed attract and nearest points
    // I have removed the text that is printed on screen from noise 
    
    if( key == '1'){
        currentMode = PARTICLE_MODE_NOISE;
        //resetParticles();
    }
    
	if( key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
	}
	
    // If the space bar is hit it will reset the particle system
    
	//if( key == ' ' ){
	//	resetParticles();
	//}
    
    switch (key) {
        case 'k':
            music.play();
            break;
        case 'l':
            music.stop();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    // I have added this code from the Audioplayback example in the openframeworks folder. The code used to be on the mousre dragged instead of the mouse moved
    
    float widthStep = ofGetWidth() / 3.0f;
    if (x >= widthStep && x < widthStep*2){
        music.setVolume( 0.1f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*1.0f);

}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
