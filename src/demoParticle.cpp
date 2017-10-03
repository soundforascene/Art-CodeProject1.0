#include "demoParticle.h"

//------------------------------------------------------------------
demoParticle::demoParticle(){
    
    // Im guessing this corisponds to mode 3?
	attractPoints = NULL;
}

//------------------------------------------------------------------
void demoParticle::setMode(particleMode newMode){
	mode = newMode;
}

//------------------------------------------------------------------
void demoParticle::setAttractPoints( vector <ofPoint> * attract ){
	attractPoints = attract;
}

//------------------------------------------------------------------
void demoParticle::reset(){
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);
	
	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();
	
	vel.x = ofRandom(-3.9, 3.9);
    // Changed vel.y in attempts to made a faster more 'rain' feel. from 3.9 , 3.9 to -100 , -99
	vel.y = ofRandom(-100, -99);
	
	frc   = ofPoint(0,0,0);
	
	scale = ofRandom(0.5, 1.0);
    
    // Below is for mode 'noise'. I have deleted the if statement meaning particles in all modes will fall down (tried)
	
		drag  = ofRandom(0.95, 0.998);
		vel.y = fabs(vel.y) * 3.0; //make the particles all be going down

}

//------------------------------------------------------------------
void demoParticle::update(){

	//1 - APPLY THE FORCES BASED ON WHICH MODE WE ARE IN 

	
    if( mode == PARTICLE_MODE_REPEL ){
		ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
		frc = attractPt-pos;   // we get the attraction force/vector by looking at the mouse pos relative to our pos
		
		//let get the distance and only repel points close to the mouse
		float dist = frc.length();
		frc.normalize(); //by normalizing we disregard how close the particle is to the attraction point
		
		vel *= drag; //apply drag
		if( dist < 150 ){
			vel += -frc * 0.6; //apply force//notice the frc is negative
		}else{
			//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy. 			
			frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
			frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
			vel += frc * 0.04;
		}
	}
	else if( mode == PARTICLE_MODE_NOISE ){
        
        ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
        frc = attractPt-pos;   // we get the attraction force/vector by looking at the mouse pos relative to our pos
        
        //let get the distance and only repel points close to the mouse
        float dist = frc.length(); // This creates a float which is the distance from the mouse
        frc.normalize();  //by normalizing we disregard how close the particle is to the attraction point
        
        vel *= drag; // apply drag
        if( dist < 150 ){
            vel += -frc * 0.4; //apply force// notice the frc is negative // 
        }else{
            
            //lets simulate falling snow
            //the fake wind is meant to add a shift to the particles based on where in x they are
            //we add pos.y as an arg so to prevent obvious vertical banding around x values - try removing the pos.y * 0.006 to see the banding
            float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.6, ofGetElapsedTimef() * 0.6);
            
            // frc.x controls the movement the particles made from left to right
            frc.x = fakeWindX + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
            // frc.y controls the downward movement, notice how fakeWindX is only applied on the x axis
            
            // If I remove this line it looks really cool
            //frc.y = ofSignedNoise(uniqueVal, pos.x * 6, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;
            
            vel *= drag;
            vel += frc * 0.4;
            
            //we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
            if( pos.y + vel.y > ofGetHeight() ){
                pos.y -= ofGetHeight();
            
            
            }
        }
    }
	
	//2 - UPDATE OUR POSITION
	
	pos += vel; 
	
	
	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN 
	//we could also pass in bounds to check - or alternatively do this at the ofApp level
	if( pos.x > ofGetWidth() ){
		pos.x = ofGetWidth();
		vel.x *= -1.0;
	}else if( pos.x < 0 ){
		pos.x = 0;
		vel.x *= -1.0;
	}
	if( pos.y > ofGetHeight() ){
		pos.y = ofGetHeight();
		vel.y *= -1.0;
	}
	else if( pos.y < 0 ){
		pos.y = 0;
		vel.y *= -1.0;
	}	
		
}

//------------------------------------------------------------------
void demoParticle::draw(){
    
    if( mode == PARTICLE_MODE_NOISE ){
        ofSetColor(00, 00, 00);
	}
	else if( mode == PARTICLE_MODE_REPEL ){
		ofSetColor(00, 00, 00);
	}

        ofDrawCircle(pos.x, pos.y, scale * 4.0);
}

