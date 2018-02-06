#pragma once

#include "ofMain.h"
#include "ofxLibRealSense.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
    
    ofxLibRealSense _realsense;
    
    ofxPanel        _gui;
};
