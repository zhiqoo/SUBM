#include "sceneD.hpp"

//--------------------------------------------------------------
void sceneD::setup(){
    
    ofSetCircleResolution(150);
    
    ofSetColor(239);
    ofFill();
    ofSetLineWidth(2);
    
    nBandsToGet = 360;
    
}

//--------------------------------------------------------------
void sceneD::update(){
    ofSeedRandom(39);
    
}

//--------------------------------------------------------------
void sceneD::draw(){
    
    auto center = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    
    span = 3+1000000*fft[260];
//    span = 20; // 代替
    if (span < 6) {
        span = 6;
    } else if (span > 50) {
        span = 300;
    }
    std::cout << span << endl;
    for (auto radius = 50; radius < 350; radius += span) {
        
        vector<ofVec2f> inner, outer;
        int deg_start = ofRandom(360);
        int deg_width = (int)(ofRandom(0, 360) + ofGetFrameNum() * ofRandom(1, 5)) % 720;
        if (deg_width < 360) {
            
            for (auto deg = deg_start; deg <= deg_start + deg_width; deg++) {
                
                inner.push_back(center + ofVec2f((radius - span * 0.5) * cos(deg * DEG_TO_RAD), (radius - span * 0.5) * sin(deg * DEG_TO_RAD)));
                outer.push_back(center + ofVec2f((radius + span * 0.5) * cos(deg * DEG_TO_RAD), (radius + span * 0.5) * sin(deg * DEG_TO_RAD)));
            }
        }
        else {
            
            for (auto deg = deg_start + deg_width - 360; deg <= deg_start + 360; deg++) {
                
                inner.push_back(center + ofVec2f((radius - span * 0.5) * cos(deg * DEG_TO_RAD), (radius - span * 0.5) * sin(deg * DEG_TO_RAD)));
                outer.push_back(center + ofVec2f((radius + span * 0.5) * cos(deg * DEG_TO_RAD), (radius + span * 0.5) * sin(deg * DEG_TO_RAD)));
            }
        }
        
        reverse(inner.begin(), inner.end());
        
        ofBeginShape();
        ofVertices(outer);
        ofVertices(inner);
        ofEndShape(true);
    }
    
}

//--------------------------------------------------------------
void sceneD::keyPressed(int key){
    
}

//--------------------------------------------------------------
void sceneD::keyReleased(int key){
    
}

//--------------------------------------------------------------
void sceneD::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void sceneD::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneD::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneD::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneD::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void sceneD::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void sceneD::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void sceneD::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void sceneD::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void sceneD::getFft(float *fftSmoothed){
    
    for (int i = 0; i < 360; i++) {
        fft[i] = fftSmoothed[i];
    }
    
}
