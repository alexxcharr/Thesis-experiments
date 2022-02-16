#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define PORT 12345
class particle{
    // our particle class
public:
    particle(ofVec3f startPoint, ofColor col, int size, int speedS, float sinadd);
    ~particle();
    void update();
    void draw();
    ofVec3f location, direction, velocity;
    int siz;
    ofColor col;
    float speed;
    float sinaddi;


};


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

    int mousex;
    int mousey;

    ofxPanel gui;

    ofxFloatSlider speedSlider;
    ofxFloatSlider sinAddSl;
    ofxIntSlider sizeSlider;
    ofxIntSlider maxPartSli;
    // ofxIntSlider maxAge;

    ofxVec3Slider locSlider;

    // for our particle system
    vector<particle> particles;
    int maxAge, maxParticles;

    bool b_drawParticles;
    ofEasyCam cam;
    float x, y, z;

    //data vars
    vector<float> arrayx, arrayy, arrayz;
    float sumx, sumy, sumz, averagex, averagey, averagez;
    float datax, datay, dataz;
    float mapx, mapy;
    float previous, result;

};
