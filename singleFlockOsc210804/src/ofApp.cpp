#include "ofApp.h"
#include "boid.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(239);
    gui.setup();
    osc.setup(PORT);
    gui.add(alignSlider.setup("alignSlider", 1, 0, 5));
    gui.add(cohesionSlider.setup("cohesionSlider", 1, 0, 5));
    gui.add(separationSlider.setup("separationSlider", 1, 0, 5));
    for (int i =0; i < 500; i++) {
        boid newB;
        newB.setup();
        flock.push_back(newB);
        // cout<<newB.velocity<<endl;
    }
 }

//--------------------------------------------------------------
void ofApp::update(){
    while (osc.hasWaitingMessages()) {
        ofxOscMessage message;
        osc.getNextMessage(message);
        if (message.getAddress() == "/code") {
            cout<<datax<<endl;
        }
        if (message.getAddress() == "/minibee/data") {
            if(message.getArgAsFloat(0) == 1) {
                datax = message.getArgAsFloat(1);
                datay = message.getArgAsFloat(2);
                dataz = message.getArgAsFloat(3);
                alignData = ofMap(datax, 0.46, 0.56, -1, 3);
                cohesionData = ofMap(datay, 0.45, 0.55, -1, 3);
                separationData = ofMap(dataz, 0.45, 0.55, 1, 3);
                cout<<datax<<endl;
            }


            //   cout<<datay<<endl;
        }
        // if (message.getAddress() == "/update") {
        //     uBool = true;
        // }
    }
    for (int i = 0; i < flock.size(); i++) {
        flock[i].almult = alignData;
        flock[i].comult = cohesionData;//Slider;
        flock[i].semult = separationData;
        // flock[i].alignRadius = radiusSlider;
    }

}
//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < flock.size(); i++) {
        flock[i].update();
        flock[i].draw(flock);
        flock[i].flock(flock);
        flock[i].edges();
    }
    gui.draw();
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
