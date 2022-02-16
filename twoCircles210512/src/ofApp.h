#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "MyShape.h"

#define PORT 12345
class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxOscReceiver osc;
    float datax, datay, dataz, datax2, datay2, dataz2;
    float speedx, speedx2;

    ofxPanel gui;
    ofVec3f rott, rott2;
    ofVec3f pos1, pos2;
    bool shapeOne, shapeTwo;

    ofParameter<float> radius;

    ofParameter<int> shapes_num;
    int old_num;

    ofParameter<ofVec3f> pos;
    ofParameter<ofVec3f> rot;
    ofParameter<float> speed;
    ofParameter<int> after_img;
    ofParameter<bool> color_mode;
    //ofxToggle color_mode;

    vector<MyShape> shapes;
    vector<MyShape> shapes2;

    ofFbo image;
    bool guidraw;
    ofImage img;
    int imgcount;
};
