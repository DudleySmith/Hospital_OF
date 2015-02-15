//
//  hospitalRibbonsManager.h
//  RibbonRenderer
//
//  Created by Dudley Smith on 11/02/2015.
//
//

#pragma once

#include "ofMain.h"
#include "hospitalRibbon.h"
#include "hospitalPoint.h"

class hospitalRibbonsManager {
public:
    hospitalRibbonsManager();
    
private:
    map<string, hospitalRibbon> mRibbons;
    
    void addRibbon(hospitalRibbon _r);
    void addPointToRibbon(hospitalRibbon _r, ofPoint _p);
    
    ofColor fadingColors(float _ratio, ofColor _c1, ofColor _c2);
    
public:
    void newPoint(hospitalPoint _hp);
    
    void update();
    void draw();
    
    string countMessage(){return ofToString(mRibbons.size());};
    
private:
    // Parameters
    ofParameter<ofColor> pcForeGround;
    ofParameter<ofColor> pcBackGround;
    
    ofParameter<bool>    pbDrawCurves;
    ofParameter<bool>    pbDrawMeshes;
    
    ofParameter<float>   pfFadeTime;
    ofParameter<float>   pfDownSpeed;
    ofParameter<float>   pfMinThickness;
    ofParameter<float>   pfMaxThickness;    
    
    ofParameter<int> pfGlobalPointsDivider;
    ofParameter<float> pfRibbonEffectLevel;
    ofParameter<float> pfRibbonIdxPointsDivider;
    ofParameter<float> pfRibbonTimeDivider;
    
    
public:
    ofParameterGroup parameters;

};
