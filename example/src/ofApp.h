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
    ofxGuiGroup     _r200Params;
    ofxToggle       _autoExposure;
    ofxToggle       _enableEmitter;
    ofxFloatSlider  _irGain;
    ofxFloatSlider  _irExposure;
    ofxGuiGroup     _sr300Params;
    ofxIntSlider    _laserPower;
    
    void onR200BoolParamChanged(bool &value);
    void onR200FloatParamChanged(float &value);
    void onSR300IntParamChanged(int &value);
};
