#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    osc.setup(12345);
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    fbo.allocate(1024, 720, GL_RGBA32F_ARB);

    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();
    alpha = 10;
}

//--------------------------------------------------------------
void ofApp::update(){

    //osc receiver
    while (osc.hasWaitingMessages()) {
        ofxOscMessage m;
        osc.getNextMessage(&m);
        if (m.getAddress() == "/minibee/data") {
            x = m.getArgAsFloat(1);
            y = m.getArgAsFloat(2);
            mapX = round(ofMap(x, 0.2, 0.7, 0, 1024));
            mapY = round(ofMap(y, 0, 1, 0, 720));
        }
    }

    ofEnableAlphaBlending();

    fbo.begin();
    fboCircleTest(mapX, mapY);
    fbo.end();
}
//--------------------------------------------------------------
void ofApp::fboCircleTest(int x, int y){

    //drawing a rectangle enables fbo fading
    ofFill();
    ofSetColor(255, 255, 255, alpha);
    ofDrawRectangle(0, 0, 1024, 720);

    //draw sens circle
    ofFill();
    ofSetColor(255, 255, 255);
    ofDrawCircle(x, y, 8);

}
//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    fbo.draw(0, 0);
    //  ofNoFill();
    //ofDrawRectangle(0,0, 1024, 720);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
