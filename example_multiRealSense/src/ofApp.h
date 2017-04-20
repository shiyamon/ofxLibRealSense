#pragma once

#include "ofMain.h"
#include "ofxLibRealSense.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
    
    vector<ofxLibRealSense*> _realsense;
};
