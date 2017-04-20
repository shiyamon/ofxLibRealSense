//
//  ofxLibRealSense.h
//  RSTestApp
//
//  Created by mtblanc on 2017/02/01.
//
//

#pragma once
#include "ofMain.h"
#include "rs.hpp"


class ofxLibRealSense : public ofThread
{
public:
    static int getDeviceCount();
    
    ofxLibRealSense() : _hasNewColor(false), _hasNewIr(false), _hasNewDepth(false){}
    
    ~ofxLibRealSense(){}
    
    void setupDevice(int deviceID);
    void setupColor(int width, int height, int fps=60);
    void setupIR(int width, int height, int fps=60);
    void setupDepth(int width, int height, int fps=60);
    void startDevice();
    void update();
    void exit();
    
    void setR200IROptions(bool autoExposure, bool emitter, float gain, float exposure);
    
    ofTexture*  getColorTex() { return &_colTex; }
    ofTexture*  getIrTex() { return &_irTex; }
    ofTexture*  getDepthTex() { return &_depthTex; }
    
    
private:
    static bool             _initialized;
    static rs::context     *_ctx;
    
    static void init();
    
    rs::device      *_device;
    uint8_t         *_colBuff;
    uint8_t         *_irBuff;    
    uint16_t        *_depthBuff;
    
    bool            _hasNewColor;
    bool            _hasNewIr;
    bool            _hasNewDepth;
    
    int             _colorWidth, _irWidth, _depthWidth;
    int             _colorHeight, _irHeight, _depthHeight;
    
    ofTexture       _colTex;
    ofTexture       _irTex;
    ofTexture       _depthTex;
    
    void threadedFunction();
};
