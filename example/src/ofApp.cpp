#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // setup librealsense
    _realsense.setupDevice(0);
//    _realsense.setupColor(640, 480);
//    _realsense.setupDepth(640, 480, 60);
    _realsense.setupIR(640, 480, 60);
    _realsense.startDevice();
    
    cout << _realsense.getDeviceName() << endl;
    
    // setup GUI
    _gui.setup("realsense params");
    _gui.add(_realsense.getRSParamGui());
}

//--------------------------------------------------------------
void ofApp::update(){
    _realsense.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    _realsense.getColorTex()->draw(0, 0, 320, 240);
    _realsense.getIrTex()->draw(320, 0, 320, 240);
//    _realsense.getDepthTex()->draw(0, 240, 320, 240);
    
    _gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


void ofApp::exit()
{
    _realsense.exit();
}
