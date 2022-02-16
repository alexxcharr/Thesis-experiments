#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    osc.setup(PORT);
    ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){
    while (osc.hasWaitingMessages()) {
        ofxOscMessage message;
        osc.getNextMessage(message);
        if (message.getAddress() == "/minibee/data") {
            datax = ofMap(message.getArgAsFloat(1), 0.3, 0.6, 0, 100);
            posx = ofMap(message.getArgAsFloat(1), 0.3, 0.6, 30, ofGetWidth()/2 + 200);
            cout<<array.size()<<endl;
            array.push_back(posx);
        }
    }
    if (array.size()>2) {
        array.erase(array.begin());
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);

    for (int i = 1; i < array.size(); i++) {
        ofSetColor(0);
        ofRect(ofLerp(array[i-1] * 0.9, array[i] * 0.1, 0.5), ofGetHeight()/2 , 100, 100);//datax, datax);
        //ofRect(ofGetWidth()/2 - 200, ofGetHeight()/2, ofLerp(array[i-1], array[i], 0.4), ofLerp(array[i-1], array[i], 0.5));
        // ofRect(ofGetWidth()/2 + 200, ofGetHeight()/2 , datax, datax);
    }

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
