#pragma once
#include "ofMain.h"

enum particleMode{
    // I have removed the two modes I wasent using
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NOISE
};

class demoParticle{

	public:
		demoParticle();
		
		void setMode(particleMode newMode);	
		void setAttractPoints( vector <ofPoint> * attract );

		void reset();
		void update();
		void draw();		
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		
		particleMode mode;
		vector <ofPoint> * attractPoints;
};
