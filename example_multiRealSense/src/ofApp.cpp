#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    _realsense.resize(ofxLibRealSense::getDeviceCount());
    
    for(int i=0; i<_realsense.size(); i++) {
        _realsense[i] = new ofxLibRealSense();
        _realsense[i]->setupDevice(i);
        _realsense[i]->setupColor(640, 480);
        _realsense[i]->setupIR(640, 480);
        _realsense[i]->startDevice();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(ofxLibRealSense* rs : _realsense) {
        rs->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i=0; i<_realsense.size(); i++) {
        ofPushMatrix();
        ofTranslate(0, 240*i);
        _realsense[i]->getColorTex()->draw(0, 0, 320, 240);
        _realsense[i]->getIrTex()->draw(320, 0, 320, 240);
        ofPopMatrix();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


void ofApp::exit()
{
    for(int i=0; i<_realsense.size(); i++) {
        _realsense[i]->exit();
    }
    
//    for(ofxLibRealSense* rs : _realsense) {
//        rs->exit();
//    }
}
