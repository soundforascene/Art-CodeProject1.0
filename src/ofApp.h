#pragma once

#include "ofMain.h"
#include "demoParticle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		particleMode currentMode;
		string currentModeStr; 

		vector <demoParticle> p;
		vector <ofPoint> attractPoints;
		vector <ofPoint> attractPointsWithMovement;
    
    ofSoundPlayer music;
    
    float * fftSmooth;
    int bands;
    
    // Low Pass
    
    class ofxLPF {
    public:
        ofxLPF(const int samplerate = 44100, const double cutoff = 5000);
        void initialize(const int samplerate, const double cutoff);
        double process(const double value);
        
    private:
        double ax[3];
        double by[3];
        double xv[3];
        double yv[3];
		
};
