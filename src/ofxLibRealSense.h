//
//  ofxLibRealSense.h
//  RSTestApp
//
//  Created by mtblanc on 2017/02/01.
//
//

#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "rs.hpp"


class ofxLibRealSense : public ofThread
{
public:
    enum OFX_RSTYPE { RS_R200=0, RS_SR300=1, RS_UNKNOWN=2 };
    
    static int getDeviceCount();
    
    ofxLibRealSense() : _hasNewColor(false), _hasNewIr(false), _hasNewDepth(false), _hasNewFrame(false), _deviceType(RS_R200){}
    ~ofxLibRealSense(){}
    
    void setupDevice(int deviceID);
    void setupColor(int width, int height, int fps=60);
    void setupIR(int width, int height, int fps=60);
    void setupDepth(int width, int height, int fps=60);
    void startDevice();
    void update();
    void exit();
    
    void setR200IROptions(bool autoExposure, bool emitter, float gain, float exposure);
    void setSR300Options(int laserPower);
    
    ofTexture*  getColorTex() { return &_colTex; }
    ofTexture*  getIrTex() { return &_irTex; }
    ofTexture*  getDepthTex() { return &_depthTex; }
    
    uint8_t*    getColorBuffer() { return _colBuff; }
    uint8_t*    getIrBuffer() { return _irBuff; }
    uint16_t*   getDepthBuffer() { return _depthBuff; }
    
    bool isFrameNew() {
        return _hasNewFrame;
    }
    
    int getColorWidth() { return _colorWidth; }
    int getColorHeight(){ return _colorHeight; }
    int getIrWidth()    { return _irWidth; }
    int getIrHeight()   { return _irHeight; }
    int getDepthWidth() { return _depthWidth; }
    int getDepthHeight(){ return _depthHeight; }
    string getDeviceName() { return _device->get_name(); }
    OFX_RSTYPE getDeviceType() { return _deviceType; }
    
    ofxGuiGroup* getRSParamGui() {
        if(_deviceType == RS_R200)
            return &_r200Params;
        else
            return &_sr300Params;
    }
    
    
private:
    static bool             _initialized;
    static rs::context     *_ctx;
    
    static void init();
    
    rs::device      *_device;
    uint8_t         *_colBuff;
    uint8_t         *_irBuff;    
    uint16_t        *_depthBuff;
    
    OFX_RSTYPE      _deviceType;
    
    bool            _hasNewFrame;
    bool            _hasNewColor;
    bool            _hasNewIr;
    bool            _hasNewDepth;
    
    int             _colorWidth, _irWidth, _depthWidth;
    int             _colorHeight, _irHeight, _depthHeight;
    
    ofTexture       _colTex;
    ofTexture       _irTex;
    ofTexture       _depthTex;
    
    ofxGuiGroup     _r200Params;
    ofxToggle       _autoExposure;
    ofxToggle       _enableEmitter;
    ofxFloatSlider  _irGain;
    ofxFloatSlider  _irExposure;
    ofxGuiGroup     _sr300Params;
    ofxIntSlider    _laserPower;
    
    void threadedFunction();
    void onR200BoolParamChanged(bool &value);
    void onR200FloatParamChanged(float &value);
    void onSR300IntParamChanged(int &value);
};
