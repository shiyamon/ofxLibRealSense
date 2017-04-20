#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // setup librealsense
    _realsense.setupDevice(0);
    _realsense.setupColor(640, 480, 60);
    _realsense.setupDepth(640, 480);
    _realsense.setupIR(640, 480);
    _realsense.startDevice();
    
    // setup GUI
    _gui.setup("r200 params");
    _gui.add(_autoExposure.setup("auto exposure", false));
    _gui.add(_enableEmitter.setup("enable emitter", false));
    _gui.add(_irGain.setup("ir gain", 400, 100, 6399));
    _gui.add(_irExposure.setup("exposure", 164, 1, 330));
    
    _autoExposure.addListener(this, &ofApp::onR200BoolParamChanged);
    _enableEmitter.addListener(this, &ofApp::onR200BoolParamChanged);
    _irGain.addListener(this, &ofApp::onR200FloatParamChanged);
    _irExposure.addListener(this, &ofApp::onR200FloatParamChanged);
}

//--------------------------------------------------------------
void ofApp::update(){
    _realsense.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    _realsense.getColorTex()->draw(0, 0, 320, 240);
    _realsense.getIrTex()->draw(320, 0, 320, 240);
    _realsense.getDepthTex()->draw(0, 240, 320, 240);
    
    _gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


void ofApp::exit()
{
    _realsense.exit();
}



void ofApp::onR200BoolParamChanged(bool &value)
{
    _realsense.setR200IROptions(_autoExposure, _enableEmitter, _irGain, _irExposure);
}


void ofApp::onR200FloatParamChanged(float &value)
{
    _realsense.setR200IROptions(_autoExposure, _enableEmitter, _irGain, _irExposure);
}
