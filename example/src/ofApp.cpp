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
    if(_realsense.getDeviceName() == "Intel RealSense R200") {
        
        _gui.add(_r200Params.setup("R200"));
        _r200Params.add(_autoExposure.setup("auto exposure", false));
        _r200Params.add(_enableEmitter.setup("enable emitter", false));
        _r200Params.add(_irGain.setup("ir gain", 400, 100, 6399));
        _r200Params.add(_irExposure.setup("exposure", 164, 1, 330));
        
        _autoExposure.addListener(this, &ofApp::onR200BoolParamChanged);
        _enableEmitter.addListener(this, &ofApp::onR200BoolParamChanged);
        _irGain.addListener(this, &ofApp::onR200FloatParamChanged);
        _irExposure.addListener(this, &ofApp::onR200FloatParamChanged);
    }
    else if(_realsense.getDeviceName() == "Intel RealSense SR300") {
        _gui.add(_sr300Params.setup("SR300"));
        _sr300Params.add(_laserPower.setup("laserPower", 16, 0, 16));
        _laserPower.addListener(this, &ofApp::onSR300IntParamChanged);
    }
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



void ofApp::onR200BoolParamChanged(bool &value)
{
    _realsense.setR200IROptions(_autoExposure, _enableEmitter, _irGain, _irExposure);
}


void ofApp::onR200FloatParamChanged(float &value)
{
    _realsense.setR200IROptions(_autoExposure, _enableEmitter, _irGain, _irExposure);
}


void ofApp::onSR300IntParamChanged(int &value)
{
    _realsense.setSR300Options(_laserPower);
}
