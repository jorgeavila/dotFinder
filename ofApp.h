#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include  "ofxGui.h"



class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void findSpotsPressed();
    void bSubPressed();
    
    
    ofVideoPlayer 		vidPlayer;
    
    
    ofxCvColorImage			colorImg;
    ofxPanel gui;
    ofxButton bSub;
    ofxButton findSpots;
    ofParameter<int> threshold;
    
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    ofxCvGrayscaleImage  grayMask;
    ofImage   mask;
    ofxCvColorImage colorMask;
    ofxCvGrayscaleImage     grayBlurred;
    ofxCvContourFinder 	contourFinder;
    
    ofxCvBlob          bArea;
    
    bool bHide;
    bool   bLearnBakground;
    float area;
    int blobs2;
    int cBlobs;
    
    
};
