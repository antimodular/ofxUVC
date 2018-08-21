#pragma once

#include "ofMain.h"
#include "ofxUVCProber.h" // <- To use the prober, you need include this header BEFORE including "ofxUVC.h"!
#include "ofxUVC.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void exit();
    
    ofVideoGrabber	vidGrabber;

    ofxUVC uvcControl;
    
    int camWidth = 640;
    int camHeight = 480;

    vector<ofxUVCControl> controls;
};
