#pragma once

// #include "ofMain.h"
// #include "ofApp.h"

class boid{

public:
    void setup();
    ofVec2f align(std::vector<boid> flock);
    ofVec2f cohesion(std::vector<boid> flock);
    ofVec2f separation(std::vector<boid> flock);
    void flock(std::vector<boid> flock);
    void update();
    void draw(std::vector<boid> flock);
    void edges();

    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    float maxForce;
    float maxSpeed;
    float semult, comult, almult;
};
extern boid bo;
