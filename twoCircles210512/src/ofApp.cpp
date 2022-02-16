#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    osc.setup(PORT);
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofSetCircleResolution(60);

    gui.setup();
    gui.add(shapes_num.set("number of shapes", 1, 1, 5));
    gui.add(radius.set("radius", 150, 1, ofGetHeight()/2));
    gui.add(pos.set("pos",
                    ofVec3f(0),
                    ofVec3f(0),
                    ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 1000)));
    gui.add(rot.set("rot",
                    ofVec3f(0),
                    ofVec3f(0),
                    ofVec3f(720, 720, 720)));
    gui.add(speed.set("speed", 0, 0, 0.1));
    gui.add(color_mode.set("color mode", 0));
    gui.add(after_img.set("after image", 48, 0, 255));
    shapeOne = false;
    shapeTwo = false;
    imgcount = 0;
    guidraw = true;
}

//--------------------------------------------------------------
void ofApp::update(){

    while (osc.hasWaitingMessages()) {
        ofxOscMessage message;
        osc.getNextMessage(message);
        if (message.getAddress() == "/minibee/data") {
            if (message.getArgAsFloat(0) == 1) {
                cout<<message.getArgAsFloat(0)<<endl;
                datax = ofMap(message.getArgAsFloat(1), 0.2, 0.6, 0, 720);
                datay = ofMap(message.getArgAsFloat(2), 0.3, 0.6, 0, 720);
                dataz = ofMap(message.getArgAsFloat(3), 0.3, 0.6, 0, 720);
                speedx = ofMap(message.getArgAsFloat(1), 0.1, 0.8, 0, 0.01);
                pos1.x = ofMap(message.getArgAsFloat(1), 0.2, 0.6, 0, ofGetWidth());
                pos1.y = ofMap(message.getArgAsFloat(2), 0.2, 0.6, 0, ofGetHeight());
                pos1.z = ofMap(message.getArgAsFloat(3), 0.2, 0.6, -500, 500);
                rott.set(datax, datay, dataz);
                radius = ofMap(message.getArgAsFloat(1), 0.45, 0.55, 1, 150);
                shapeOne = true;
            }
            else if (message.getArgAsFloat(0) == 2) {
                cout<<message.getArgAsFloat(0)<<endl;
                datax2 = ofMap(message.getArgAsFloat(1), 0.2, 0.6, 0, 720);
                datay2 = ofMap(message.getArgAsFloat(2), 0.2, 0.6, 0, 720);
                dataz2 = ofMap(message.getArgAsFloat(3), 0.2, 0.6, 0, 720);
                pos2.x = ofMap(message.getArgAsFloat(1), 0.2, 0.6, 0, ofGetWidth());
                pos2.y = ofMap(message.getArgAsFloat(2), 0.2, 0.6, 0, ofGetHeight());
                pos2.z = ofMap(message.getArgAsFloat(3), 0.2, 0.6, -500, 500);
                speedx2 = ofMap(message.getArgAsFloat(1), 0.2, 0.6, 0, 0.02);
                rott2.set(datax2, datay2, dataz2);
                shapeTwo = true;
            }

        }
    }
    // while (shapes.size() != shapes_num){
    if (shapes.size() < 1 && shapeOne == true) {
        MyShape s;
        shapes.push_back(s);
    }
    if (shapes2.size() < 1 && shapeTwo == true) {
        MyShape s2;
        shapes2.push_back(s2);
    }


    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].update();
        shapes[i].setRadius(radius);
        shapes[i].setPosAmp(pos1);
        shapes[i].setRotAmp(rott);
        shapes[i].setSpeedAmp(speedx);
        shapes[i].setColorMode(color_mode);

    }
    for (int i = 0; i < shapes2.size(); i++) {
        shapes2[i].update();
        shapes2[i].setRadius(radius);
        shapes2[i].setPosAmp(pos2);
        shapes2[i].setRotAmp(rott2);
        shapes2[i].setSpeedAmp(speedx2);
        shapes2[i].setColorMode(color_mode);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].draw();
        //shapes2[i].draw();
    }
    for (int i = 0; i < shapes2.size(); i++) {
        shapes2[i].draw();
    }

    ofPopMatrix();

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    ofFill();
    ofSetColor(0, after_img);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    if(guidraw) {
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){

        img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
        img.save("pic" + ofToString(imgcount) + ".png", OF_IMAGE_QUALITY_BEST);
        imgcount++;
    }

    if (key == 'g') {
        guidraw = false;
    }
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
