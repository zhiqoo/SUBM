#include "sceneA.hpp"

//--------------------------------------------------------------
void sceneA::setup(){
    
    ofSetColor(239);
    
    numParticles = 1200; // particlesの数
    distParticles = 130; // 線を描画する距離の閾値
    
    r = 1200;
    theta = 0;
    phy = 0.2;
    
    nBandsToGet = 360;
    
}

//--------------------------------------------------------------
void sceneA::update(){
    
    ofSeedRandom(39);
    
    theta += 0.1 * fft[120];
    phy += 0.1 * fft[40];
    
}

//--------------------------------------------------------------
void sceneA::draw(){
    
    cam.setTarget(ofVec3f(0, 0, 0));
    ofVec3f v = ofVec3f(r*sin(theta)*cos(phy), r*sin(theta)*sin(phy), r*cos(theta));
    cam.setPosition(v);
    std::cout << theta << endl;

    cam.begin();

    vector<ofPoint> points;
    vector<int> sizes;
    for (int i = 0; i < numParticles; i++) {
        ofPoint point(ofMap(ofNoise(fft[i%nBandsToGet]*0.4, ofRandom(100), ofGetFrameNum() * 0.0005), 0, 1, -ofGetWidth(), ofGetWidth()),
                      ofMap(ofNoise(fft[i%nBandsToGet]*0.4, ofRandom(100), ofGetFrameNum() * 0.0005), 0, 1, -ofGetWidth(), ofGetWidth()),
                      ofMap(ofNoise(fft[i%nBandsToGet]*0.4, ofRandom(100), ofGetFrameNum() * 0.0005), 0, 1, -ofGetWidth(), ofGetWidth()));
        points.push_back(point);
        sizes.push_back(1);
    }

    for (int out_index = 0; out_index < points.size(); out_index++) {
        for (int in_index = out_index + 1; in_index < points.size(); in_index++) {
            if (points[out_index].distance(points[in_index]) < distParticles) {
                ofSetColor(239, 100);
                //                std::cout << points[out_index].distance(points[in_index]) << endl;

                if (fft[30]*3000 > 39) {
                    ofSetColor(fft[30]*3000, 255 - round(points[out_index].distance(points[in_index]))*2);
                    ofDrawLine(points[out_index], points[in_index]);
                } else {
                    ofSetColor(39, 255 - round(points[out_index].distance(points[in_index]))*2);
                    ofDrawLine(points[out_index], points[in_index]);
                }
                //                ofSetColor(lineColor, 255 - round(points[out_index].distance(points[in_index]))*2);
                //                ofDrawLine(points[out_index], points[in_index]);


                //                std::cout << fftSmoothed[100]*1000 << endl;

                sizes[out_index]++;
                sizes[in_index]++;
            }
        }
    }

    for (int i = 0; i < points.size(); i++) {
        ofSetColor(255, sizes[i]*40);
        ofDrawSphere(points[i], sizes[i]*fft[200]*10);
    }
    cam.end();
    
}

//--------------------------------------------------------------
void sceneA::keyPressed(int key){
    
}

//--------------------------------------------------------------
void sceneA::keyReleased(int key){
    
}

//--------------------------------------------------------------
void sceneA::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void sceneA::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneA::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneA::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneA::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void sceneA::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void sceneA::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void sceneA::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void sceneA::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void sceneA::getFft(float *fftSmoothed){
    
    for (int i = 0; i < 360; i++) {
        fft[i] = fftSmoothed[i];
    }
    
}
