#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    osc.setup(PORT);
    gui.setup();
    gui.add(sizeSlider.setup("sizeSlider", 2, 1, 100));
    // gui.add(speedSlider.setup("speedSlider", 20, -10, 100));
    gui.add(maxPartSli.setup("maxPartSli", 1000, 100, 1000000));
    //gui.add(sinAddSl.setup("sinAddSl", 2, -100, 100));
    // gui.add(maxAge.setup"maxAge", )
    gui.add(locSlider.setup("locSlider", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(3)));

    ofSetFrameRate(60);
    ofBackground(0,0 , 20);
    ofEnableSmoothing();
    ofSetLineWidth(2);
    ofSetCircleResolution(128);

    maxParticles = maxPartSli;
    b_drawParticles = true;
    datax = 1;
    datay = 1;

    sumx = 0;
    sumy = 0;
    sumz = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    while (osc.hasWaitingMessages()) {
        ofxOscMessage message;
        osc.getNextMessage(message);
        if (arrayx.size()>9){
            arrayx.erase(arrayx.begin());
            arrayy.erase(arrayy.begin());
            arrayz.erase(arrayz.begin());
        }
        if (message.getAddress() == "/minibee/data") {
            datax = message.getArgAsFloat(1) * 1;
            datay = message.getArgAsFloat(2);
            dataz = message.getArgAsFloat(3);

            arrayx.push_back(datax);
            arrayy.push_back(datay);
            arrayz.push_back(dataz);
            sumx = sumx - arrayx[0];
            sumy = sumy - arrayy[0];
            sumz = sumz - arrayz[0];
            for (int i=1; i<arrayx.size()+1; i++) {
                sumx = sumx + arrayx[i-1];
                sumy = sumy + arrayy[i-1];
                sumz = sumz + arrayz[i-1];
            }
            previous = averagex;
            averagex = sumx/arrayx.size();
            averagey = sumy/arrayy.size();
            averagez = sumz/arrayz.size();
            averagex = ofMap(averagex, 0.4, 0.5, 0, ofGetWidth());
            averagey = ofMap(averagey, 0.4, 0.6, 0, ofGetHeight());
            averagez = ofMap(averagez, 0.3, 0.8, 0, ofGetHeight());
            sumx = 0;
            sumy = 0;
            sumz = 0;
            cout<<arrayy.size()<<endl;
            result = ofLerp(previous, averagex, 0.05);
        }
    }
    // loop through our particles vector updating each individual particle
    for (int i=0; i<particles.size(); i++){
        particles[i].update();
        particles[i].col.g += 1;//= 0.000001; // decrement the alpha value of each particle's colour
        //particles[i].siz += i/100;
        //    for (int i =0; i < particles.size(); i++) {
        //particles[i].update();
        float noisex = ofNoise((ofGetElapsedTimef() + i) + averagex/10); // locSlider->x);
        float noisey = ofNoise((ofGetElapsedTimef() + i) + averagey/10);//locSlider->y);
        float noisez = ofNoise((ofGetElapsedTimef() + i) + averagez/10);//locSlider->z);
        x = ofGetWidth() * noisex;
        y = ofGetHeight() * noisey;
        z = ofGetHeight() * noisez;
        //particles[i].location.set(x, y , 100);
    }
    // cout<<particles.size()<<endl;
    // if we have more than maxParticles in our vector of particles then erase the first one in the vector
    if (particles.size() >= maxParticles){
        particles.erase(particles.begin());
    }
    maxParticles = maxPartSli;
}

//--------------------------------------------------------------
void ofApp::draw(){
    // cam.begin();
    ofVec3f loc(averagex, averagey, averagez);
    ofColor green(200, 200, 255);
    if (b_drawParticles == true) {
        particle newParticle(loc, green, sizeSlider, speedSlider, sinAddSl);
        particles.push_back(newParticle);
    }



    for (int i=0; i<particles.size(); i++) {
        particles[i].draw();
    }
    //cam.end();
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
    mousex = x;
    mousey = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    b_drawParticles = true;
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
//--------------------------------------------------------------
particle::particle(ofVec3f startPoint, ofColor newCol, int size, int speedS, float sinadd){
    // constructor
    sinaddi = sinadd;
    speed = speedS;
    col = newCol;
    siz = size;
    location = startPoint;
    //direction.set(-1, 1, 1);
    // velocity.set(0, 1, 1);
    direction.set(sin(ofGetElapsedTimef()*0.9), cos(ofGetElapsedTimef()*-0.9),tan(ofGetElapsedTimef()*2));//ofRandom(-1, 0),ofRandom(-1, 0),ofRandom(-1, 0));
    velocity.set(ofNoise((ofGetElapsedTimef() *2) *10), ofNoise((ofGetElapsedTimef() *2) *10), ofNoise(50));//ofRandom(-speed,speed), ofRandom(-speed,speed), ofRandom(-speed,speed) );
}

//--------------------------------------------------------------
particle::~particle(){

}

//--------------------------------------------------------------
void particle::update(){
    location += (direction * velocity);//  * sin(ofGetElapsedTimef() + sinaddi) + ofSignedNoise(ofGetElapsedTimef()* sinaddi);
}

//--------------------------------------------------------------
void particle::draw(){
    ofPushStyle();
    ofFill();
    ofSetColor(col);
    ofDrawCircle(location, siz);
    ofPopStyle();
}
