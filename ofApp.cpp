#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	
    
    vidPlayer.loadMovie("3backTest.mov");
    mask.loadImage("filter.png");
    vidPlayer.play();
    bHide = true;
    
    
    //gui
    ofxGuiSetFont("Questrial-Regular.ttf",7,true,true);
	ofxGuiSetTextPadding(10);
	ofxGuiSetDefaultWidth(150);
	ofxGuiSetDefaultHeight(20);
    gui.setup("panel");
    gui.add(findSpots.setup("Find"));
    findSpots.addListener(this,&ofApp::findSpotsPressed);  //find Spots button

    
    //cv video
    grayMask.allocate(320,240);
    colorImg.allocate(320,240);
    grayImage.allocate(320,240);
    grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
    
    
    
    /////---------Draw mask--------- /////
    
    //for (int i = 0; i < 320; i++){
    //for (int j = 0; j < 240; j++)
    //{
    // if (i / 10 % 2 == 0) mask.getPixels()[ j * 320 + i] = 255;
    //    else mask.getPixels()[ j * 320 + i] = 0;
    
    //  }
    //}
    //mask.flagImageChanged();
    
    
	
}





//--------------------------------------------------------------
void ofApp::update(){
	
    
    
    
    
    ofBackground(100,100,100);
    bool bNewFrame = false;
    
    //mask
    colorMask.setFromPixels(mask.getPixelsRef());
    grayMask = colorMask;
    
    
    //cv video
    vidPlayer.update();
    bNewFrame = vidPlayer.isFrameNew();
    
    
    
    colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
    
    
    
    grayImage = colorImg;
    
    
    grayBlurred = grayImage;  //blurry image to skip noise
    

    for (int i = 0; i < 50; i++){
        grayBlurred.blur();
    }
    
    // take the abs value of the difference between background and incoming and then threshold:
    grayDiff.absDiff(grayImage, grayBlurred);
    grayDiff *= grayMask;
    
    grayDiff.invert();
    
    grayDiff.threshold(243);
    //blueIRO240
    //redIRO250
    //back test 240
    
    
    
  
    
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
   ofBackgroundHex(0x080808);
	
	ofSetHexColor(0xffffff);
    colorImg.draw(670,60,320,240);
	//grayImage.draw(320,20);
	grayDiff.draw(10,60,640,480);
   // grayMask.draw(10,60,640,480);
	//grayBlurred.draw(30,600);
    

    
	ofFill();
	//ofRect(360,540,320,240);
	// we could draw the whole contour finder
	contourFinder.draw(10,60,640,480);
    
	
    
	// finally, a report:
	ofSetHexColor(0xa1f5ff);
	stringstream reportStr;
	reportStr
    << "num blobs found " << contourFinder.nBlobs << endl;
    
    ofDrawBitmapStringHighlight(reportStr.str(), 50, 600, 0X080808);
    
    
    if( bHide ){
        gui.draw();
    }
    
}


void ofApp::findSpotsPressed(){
    
    //for (int i = 0; i < 15; i++){
    
    
	contourFinder.findContours(grayDiff, 0, (640*480)/18000, 400, false);
    
    
}









//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
