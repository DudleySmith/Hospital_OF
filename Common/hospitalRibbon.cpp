//
//  hospitalRibbon.cpp
//  RibbonRenderer
//
//  Created by Dudley Smith on 10/02/2015.
//
//

#include "hospitalRibbon.h"

//--------------------------------------------------------------
void hospitalRibbon::update(float _dnSpeed){
    
    for(unsigned int i = 0; i < mPoints.size(); i++){
        mPoints[i].z -= _dnSpeed;
        //sumOfAllPoints += mPoints[i];
    }
    
}

//--------------------------------------------------------------
void hospitalRibbon::drawCamText(){
    if(mPoints.size()>0){
        ofDrawBitmapString(mCam, mPoints[mPoints.size()-1]);
    }
}

//--------------------------------------------------------------
void hospitalRibbon::drawCircles(ofColor _color, float _maxThickness
                                 ,int _nbCircles, float _circlesRadius
                                 ,float _radiusDephaser, float _freqDivider){

    if(mPoints.size()>0){
        
        ofPoint center = mPoints[mPoints.size()-1];
        
        // One big point to hide extremity
        ofPushStyle();
        ofSetColor(_color);
        ofFill();
        
        ofCircle(center, 1.25 * _maxThickness);
        ofPopStyle();
        
        // Concentric circles
        ofPushStyle();
        ofSetColor(_color);
        ofNoFill();
        
        for(int idxCircle=0; idxCircle<_nbCircles; idxCircle++){
            
            float radiusRatio = (float)idxCircle / (float)_nbCircles;
            float myOwnDivider = radiusRatio*_freqDivider;
            float radiusTimeRatio = fmod(mTimeStampf + radiusRatio*_radiusDephaser, myOwnDivider) / myOwnDivider;
            float lineWidth = 5 * fmod(mTimeStampf + radiusRatio*_radiusDephaser, myOwnDivider) / myOwnDivider;
            
            ofSetLineWidth(lineWidth);
            
            ofCircle(center, _circlesRadius * radiusTimeRatio);
            
        }
        ofPopStyle();
    }
    
 
}

//--------------------------------------------------------------
void hospitalRibbon::drawShape(ofColor _color
                               , float _minThickness, float _maxThickness
                               , int globalPointsDiv
                               , float _ribbonEffectLevel, float _ribbonIdxPointsDivider, float _ribbonTimeDivider){
    
    ofPushStyle();
    
    ofSetColor(_color);
    ofSetLineWidth(5);
    ofNoFill();
    
    //do the same thing from the first example...
    ofBeginShape();
    
    for(unsigned int i = 1; i < mPoints.size(); i++){
        
        if(i==1 || i==(mPoints.size()-1) || (i%globalPointsDiv == 1)){
            
        //find this point and the next point
        ofPoint thisPoint = mPoints[i-1];
        ofPoint nextPoint = mPoints[i];
        
        //get the direction from one to the next.
        //the ribbon should fan out from this direction
        ofPoint direction = (nextPoint - thisPoint);
        
        //get the distance from one point to the next
        float distance = direction.length();
        ofLogVerbose() << "Distance = " << ofToString(distance);
        
        //get the normalized direction. normalized vectors always have a length of one
        //and are really useful for representing directions as opposed to something with length
        ofPoint unitDirection = direction.normalized();
        
        //find both directions to the left and to the right
        ofPoint toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
        ofPoint toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
        
        //use the map function to determine the distance.
        //the longer the distance, the narrower the line.
        //this makes it look a bit like brush strokes
        
        // thickness depend on distance between point -> brush effect
        //float thickness = ofMap(distance, 0, 60, 20, 2, true);
        
        // thickness depend on distance between point -> brush effect
        float pointRatio = (float)i / (float)mPoints.size();
        float pointRatioInv = 1 - pointRatio;
        float thickness = ofMap(pointRatio*pointRatio, 0, 1, _minThickness, _maxThickness, true);
        
        //calculate the points to the left and to the right
        //by extending the current point in the direction of left/right by the length
        float ribbonPhase = (float)i / _ribbonIdxPointsDivider + ofGetElapsedTimef() / _ribbonTimeDivider;
        float ribbonEffect = pointRatioInv*_ribbonEffectLevel*sin(ribbonPhase*TWO_PI);
        
        ofPoint leftPoint = thisPoint+toTheLeft*thickness+toTheLeft*ribbonEffect;
        ofPoint rightPoint = thisPoint+toTheRight*thickness+toTheLeft*ribbonEffect;
        
        //add these mPoints to the triangle strip
            if (i==(mPoints.size()-1)) {
                ofVertex(leftPoint);
            }else{
                ofCurveVertex(leftPoint);
            }
//        ofNextContour();
        //ofCurveVertex(rightPoint);
        }
    }
    
    //end the shape
    ofEndShape();

    ofPopStyle();
    

    
}

//--------------------------------------------------------------
void hospitalRibbon::drawMesh(ofColor _color
                              , float _minThickness, float _maxThickness
                              , int globalPointsDiv
                              , float _ribbonEffectLevel, float _ribbonIdxPointsDivider, float _ribbonTimeDivider){
    
    ofPushStyle();
    
    ofSetColor(_color);
    
    //do the same thing from the first example...
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for(unsigned int i = 1; i < mPoints.size(); i++){
        if(i==1 || i==(mPoints.size()-1) || (i%globalPointsDiv == 1)){
        //find this point and the next point
        ofPoint thisPoint = mPoints[i-1];
        ofPoint nextPoint = mPoints[i];
        
        //get the direction from one to the next.
        //the ribbon should fan out from this direction
        ofPoint direction = (nextPoint - thisPoint);
        
        //get the distance from one point to the next
        float distance = direction.length();
        
        //get the normalized direction. normalized vectors always have a length of one
        //and are really useful for representing directions as opposed to something with length
        ofPoint unitDirection = direction.normalized();
        
        //find both directions to the left and to the right
        ofPoint toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
        ofPoint toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
        
        //use the map function to determine the distance.
        //the longer the distance, the narrower the line.
        //this makes it look a bit like brush strokes
        
        // thickness depend on distance between point -> brush effect
        //float thickness = ofMap(distance, 0, 60, 20, 2, true);
        
        // thickness depend on distance between point -> brush effect
        float pointRatio = (float)i / (float)mPoints.size();
        float pointRatioInv = 1 - pointRatio;
        float thickness = ofMap(pointRatio*pointRatio, 0, 1, _minThickness, _maxThickness, true);
        
        //calculate the mPoints to the left and to the right
        //by extending the current point in the direction of left/right by the length
        float ribbonPhase = (float)i / _ribbonIdxPointsDivider + ofGetElapsedTimef() / _ribbonTimeDivider;
        float ribbonEffect = pointRatioInv*_ribbonEffectLevel*sin(ribbonPhase*TWO_PI);
        
        ofPoint leftPoint = thisPoint+toTheLeft*thickness+toTheLeft*ribbonEffect;
        ofPoint rightPoint = thisPoint+toTheRight*thickness+toTheLeft*ribbonEffect;
        
        //add these mPoints to the triangle strip
        mesh.addVertex(ofPoint(leftPoint.x, leftPoint.y, leftPoint.z));
        mesh.addVertex(ofPoint(rightPoint.x, rightPoint.y, rightPoint.z));
        }
    }
    
    //end the shape
    mesh.draw();
    ofPopStyle();

    
}

//--------------------------------------------------------------
void hospitalRibbon::addPoint(ofPoint _p, string _cam, string _blobId){
    
    mPoints.push_back(_p);
    mTimeStampf = ofGetElapsedTimef();
    mCam = _cam;
    mBlobId = _blobId;
    
}

//--------------------------------------------------------------
bool hospitalRibbon::IsThereAPointNearToMe(ofPoint _p, float _matchingDistance){
    
    vector<ofPoint>::iterator onePoint;
    for (onePoint = mPoints.begin(); onePoint != mPoints.end(); onePoint++) {
        
        ofPoint entryPoint = _p;
        _p.z = 0;
        ofPoint testedPoint = *onePoint;
        testedPoint.z = 0;
        
        if (entryPoint.distance(testedPoint) <= _matchingDistance) {
            // Some point is near enough
            ofLogVerbose() << "Match Distance";
            return true;
        }
    }
    return false;

}