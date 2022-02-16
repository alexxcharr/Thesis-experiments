#include "ofApp.h"
#include "boid.h"


void boid::setup() {
    position.set(ofRandomWidth(), ofRandomHeight());
    // velocity.set(ofRandom(-0.05, 0.05), ofRandom(-0.05, 0.05));
    // velocity.scale(0.15);
    acceleration.set(0,0);
    float angle = ofRandom(TWO_PI);
    velocity.set(cos(angle), sin(angle));
    maxForce = 0.03;
    maxSpeed = 2;
}

ofVec2f boid::align(std::vector<boid> flock) {
    int perceptionRadius = 50;
    // ofVec2f steering(0, 0);
    ofVec2f sum(0, 0);
    int total = 0;
    for (int i = 0; i < flock.size(); i++) {
        float d = position.distance(flock[i].position);
        if (d > 0 && d < perceptionRadius) {
            // steering += flock[i].velocity;
            sum += flock[i].velocity;
            total++;
        }
    }
    if (total>0) {
        sum /= (float(total));
        sum.normalize();
        sum *= maxSpeed;
        ofVec2f steer = sum - velocity;
        steer.limit(maxForce);
        return steer;
    } else {
        return ofVec2f(0, 0);
    }
        // steering.scale(maxSpeed);
        // steering = steering - velocity;
        // steering.limit}(maxForce);

    //cout<<steering<<endl;
    // return steering;
}


ofVec2f boid::cohesion(std::vector<boid> flock) {
    int perceptionRadius = 1000;
    // ofVec2f steering(0, 0);
    ofVec2f sum = ofVec2f(0,0);
    int total = 0;
    for (int i = 0; i < flock.size(); i++) {
        float d = position.distance(flock[i].position);
        if (d > 0 && d < perceptionRadius) {
            // steering += flock[i].position;
            sum += flock[i].position;
            total++;
        }
    }
    if (total>0) {
        sum /= (float(total));
        ofVec2f desired = sum - position;
        desired.normalize();
        desired *= maxSpeed;
        ofVec2f steer = desired - velocity;
        steer.limit(maxForce);
        return steer;
        // steering = steering/total;
        // steering = steering - position;
        // steering.scale(maxSpeed);
        // steering = steering - velocity;
        // steering.limit(0.1);
        // steering = steering * 0.1;
        // return sum;
    }else {
        return ofVec2f(0,0);
    }
    // cout<<steering<<endl;
    // return steering;
}


ofVec2f boid::separation(std::vector<boid> flock) {
    int perceptionRadius = 30;
    ofVec2f steering(0, 0);
    int total = 0;
    for (int i = 0; i < flock.size(); i++) {
        float d = position.distance(flock[i].position);
        if (d>0 && d < perceptionRadius) {
            ofVec2f diff = position - flock[i].position;
            diff.normalize();
            diff /= d;
            steering += diff;//flock[i].position;
            total++;
        }
    }
    if (total>0) {
        steering /= (float(total));
        // steering.scale(maxSpeed);
        // steering = steering - velocity;
        // steering.limit(maxForce);
    }
    if (steering.length() > 0) {
        steering.normalize();
        steering *= maxSpeed;
        steering -= velocity;
        steering.limit(maxForce);
    }
    //cout<<steering<<endl;
    return steering;
}

void boid::flock(std::vector<boid> flock) {
    ofVec2f alignment = align(flock);
    ofVec2f coh = cohesion(flock);
    ofVec2f sep = separation(flock);
    alignment = alignment * almult;
    coh = coh * comult;
    sep = sep * almult;
    acceleration += alignment;
    acceleration += coh;
    acceleration += sep;

}


void boid::update() {
    position += velocity;
    velocity += acceleration;
    velocity.limit(maxSpeed);
    acceleration = acceleration * 0;
}


void boid::draw(std::vector<boid> flock) {
    ofSetColor(39);
    ofDrawCircle(position, 2);
    vector<glm::vec3> locations;
    for (int i = 0; i < flock.size()-1; i++) {
        //locations.push_back(position);
        float d = position.distance(flock[i].position);
        if (d>5 && d <10 ) {
            ofDrawCircle(position, 2);
            // ofDrawLine(position, flock[i].position);
        }
    }
}

void boid::edges() {
    if (position.x >= ofGetWidth()) {
        position.x = 0;
    }else if (position.x <= 0) {
        position.x = ofGetWidth();
    }
    if (position.y >= ofGetHeight()) {
        position.y = 0;
    }else if (position.y <= 0) {
        position.y = ofGetHeight();
    }
}
