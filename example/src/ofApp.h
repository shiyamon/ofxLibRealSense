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
    ofxToggle       _autoExposure;
    ofxToggle       _enableEmitter;
    ofxFloatSlider  _irGain;
    ofxFloatSlider  _irExposure;
    
    void onR200BoolParamChanged(bool &value);
    void onR200FloatParamChanged(float &value);
};
