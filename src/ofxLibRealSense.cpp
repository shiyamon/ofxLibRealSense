//
//  ofxLibRealSense.cpp
//  RSTestApp
//
//  Created by mtblanc on 2017/02/01.
//
//

#include "ofxLibRealSense.h"

bool ofxLibRealSense::_initialized = false;
rs::context* ofxLibRealSense::_ctx;


void ofxLibRealSense::init()
{
    if(_initialized) return;
    
    // setup librealsense
    _ctx = new rs::context();
    cout << "RealSense device count: " << _ctx->get_device_count() << endl;
    
    _initialized = _ctx->get_device_count() > 0;
}


void ofxLibRealSense::setupDevice(int deviceID)
{
    if(!_initialized) {
        ofLog(OF_LOG_ERROR, "you have to call ofxLibRealSence::init() before you setup device");
        return;
    }
    
    _device = _ctx->get_device(deviceID);
    cout << _device->get_name() << endl;
}


void ofxLibRealSense::setupColor(int width, int height, int fps)
{
    if(_device == nullptr) {
        ofLog(OF_LOG_ERROR, "you have to setup device befor you setup streams.");
        return;
    }
    
    _colorWidth = width;
    _colorHeight = height;
    _colTex.allocate(_colorWidth, _colorHeight, GL_RGB);
    _device->enable_stream(rs::stream::color, _colorWidth, _colorHeight, rs::format::rgb8, fps);
}


void ofxLibRealSense::setupIR(int width, int height, int fps)
{
    if(_device == nullptr) {
        ofLog(OF_LOG_ERROR, "you have to setup device befor you setup streams.");
        return;
    }
    
    _irWidth = width;
    _irHeight = height;
    _irTex.allocate(_irWidth, _irHeight, GL_LUMINANCE);
    
    int fpsToUse = fps;
    if( _device->is_stream_enabled(rs::stream::depth) && _device->get_stream_framerate(rs::stream::depth) != fpsToUse ) {
        fpsToUse = _device->get_stream_framerate(rs::stream::depth);
        ofLogWarning("IR fps is different from depth fps. IR fps is now reset to " + ofToString(fpsToUse));
    }
    
    _device->enable_stream(rs::stream::infrared, _irWidth, _irHeight, rs::format::y8, fpsToUse);
    
    try{
        _device->enable_stream(rs::stream::infrared2, _irWidth, _irHeight, rs::format::y8, fpsToUse);
    } catch(...) {
        ofLogWarning("Device does not provide infrared2 stream.");
    }
}


void ofxLibRealSense::setupDepth(int width, int height, int fps)
{
    if(_device == nullptr) {
        ofLog(OF_LOG_ERROR, "you have to setup device befor you setup streams.");
        return;
    }
    
    _depthWidth = width;
    _depthHeight = height;
    _depthTex.allocate(_depthWidth, _depthHeight, GL_LUMINANCE);
    
    int fpsToUse = fps;
    if( _device->is_stream_enabled(rs::stream::infrared) && _device->get_stream_framerate(rs::stream::infrared) != fpsToUse ) {
        fpsToUse = _device->get_stream_framerate(rs::stream::infrared);
        ofLogWarning("Depth fps is different from IR fps. Depth fps is now reset to " + ofToString(fpsToUse));
    }
    
    _device->enable_stream(rs::stream::depth, _depthWidth, _depthHeight, rs::format::z16, fpsToUse);
}


void ofxLibRealSense::startDevice()
{
    _device->start();
    startThread();
}


void ofxLibRealSense::setR200IROptions(bool autoExposure, bool emitter, float gain, float exposure)
{
    _device->set_option(rs::option::r200_lr_auto_exposure_enabled, autoExposure);
    _device->set_option(rs::option::r200_emitter_enabled, emitter);
    _device->set_option(rs::option::r200_lr_exposure, exposure);
    _device->set_option(rs::option::r200_lr_gain, gain);
}


void ofxLibRealSense::threadedFunction()
{
    while(isThreadRunning()) {
        if(_device->is_streaming()){
            if(lock()) {
                _device->wait_for_frames();
                
                if(_device->is_stream_enabled(rs::stream::color)) {
                   const void *col_frame = _device->get_frame_data(rs::stream::color);
                    _colBuff = (uint8_t*)col_frame;
                    _hasNewColor = true;
                }
                if(_device->is_stream_enabled(rs::stream::infrared)) {
                    const void *ir_frame = _device->get_frame_data(rs::stream::infrared);
                    _irBuff = (uint8_t*)ir_frame;
                    _hasNewIr = true;
                }
                if(_device->is_stream_enabled(rs::stream::depth)) {
                    const void *depth_frame = _device->get_frame_data(rs::stream::depth);
                    _depthBuff = (uint16_t *)depth_frame;
                    _hasNewDepth = true;
                }
                
                unlock();
            }
        }
    }
}


void ofxLibRealSense::update()
{
    if(!_initialized) return;
    
    if(_depthBuff && _hasNewDepth) {
        _depthTex.loadData(_depthBuff, _depthWidth, _depthHeight, GL_LUMINANCE);
        _hasNewDepth = false;
    }
    
    if(_irBuff && _hasNewIr) {
        _irTex.loadData(_irBuff, _irWidth, _irHeight, GL_LUMINANCE);
        _hasNewIr = false;
    }
    
    if(_colBuff && _hasNewColor) {
        _colTex.loadData(_colBuff, _colorWidth, _colorHeight, GL_RGB);
        _hasNewColor = false;
    }
}


void ofxLibRealSense::exit()
{
    stopThread();
    _device->stop();
    
    if(_device->is_stream_enabled(rs::stream::color))
        _device->disable_stream(rs::stream::color);
    if(_device->is_stream_enabled(rs::stream::depth))
        _device->disable_stream(rs::stream::depth);
    if(_device->is_stream_enabled(rs::stream::infrared))
       _device->disable_stream(rs::stream::infrared);
    
    delete _ctx;
}
