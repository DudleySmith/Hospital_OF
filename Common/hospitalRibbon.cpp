//
//  hospitalRibbon.cpp
//  RibbonRenderer
//
//  Created by Dudley Smith on 10/02/2015.
//
//

#include "hospitalRibbon.h"

//--------------------------------------------------------------
void hospitalRibbon::update(){
    
    for(unsigned int i = 0; i < points.size(); i++){
        points[i].z -= 0.5;
        //sumOfAllPoints += points[i];
    }
    
}


//--------------------------------------------------------------
void hospitalRibbon::draw(ofColor _color){
    
    drawMesh(_color);
    
    ofColor oppositColor = _color;
    oppositColor.setHueAngle(_color.getHueAngle() + 180);
    drawShape(oppositColor);
    
}
//--------------------------------------------------------------
void hospitalRibbon::drawShape(ofColor _color){
    
    ofPushStyle();
    
    ofSetColor(_color);
    ofNoFill();
    
    ofBeginShape();
    ofCurveVertices(points);
    ofEndShape();

    ofPopStyle();
    
}

//--------------------------------------------------------------
void hospitalRibbon::drawMesh(ofColor _color){
    
    ofPushStyle();
    
    ofSetColor(_color);
    
    //do the same thing from the first example...
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    ofPoint thisPoint;
    ofPoint nextPoint;
    
    for(unsigned int i = 1; i < points.size(); i++){
        
        //find this point and the next point
        thisPoint = points[i-1];
        nextPoint = points[i];
        
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
        float pointRatio = (float)i / (float)points.size();
        float thickness = ofMap(pointRatio*pointRatio, 0, 1, 2, 20, true);
        
        //calculate the points to the left and to the right
        //by extending the current point in the direction of left/right by the length
        ofPoint leftPoint = thisPoint+toTheLeft*thickness;
        ofPoint rightPoint = thisPoint+toTheRight*thickness;
        
        //add these points to the triangle strip
        mesh.addVertex(ofPoint(leftPoint.x, leftPoint.y, leftPoint.z));
        mesh.addVertex(ofPoint(rightPoint.x, rightPoint.y, rightPoint.z));
        
        ofCurveVertex(thisPoint);
        
    }
    
    //end the shape
    mesh.draw();
    ofPopStyle();
    
    
    ofPopStyle();
    
}

//--------------------------------------------------------------
void hospitalRibbon::addPoint(ofPoint _p){
    
    points.push_back(_p);
    mTimeStampf = ofGetElapsedTimef();
    
}