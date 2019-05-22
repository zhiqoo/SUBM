#include "sceneE.hpp"

//--------------------------------------------------------------
void sceneE::setup(){
    
    ofSetLineWidth(2);
    ofEnableDepthTest();
    
    ico_sphere = ofIcoSpherePrimitive(300, 2);
    
    r = 1200;
    theta = 0;
    phy = 0.2;
    
    radius = 300;
    
}

//--------------------------------------------------------------
void sceneE::update(){
    
//    radius = (int)(300 + 300000 * fftSmoothed[300]);
    radius = 300; // 代替
    if (radius > 1000) {
        radius = 1000;
    }
    
    ico_sphere = ofIcoSpherePrimitive(radius, 2);
    this->triangles = ico_sphere.getMesh().getUniqueFaces();
    
}

//--------------------------------------------------------------
void sceneE::draw(){
    
    this->cam.begin();
    ofRotateY(ofGetFrameNum() * 0.4);
    ofRotateX(ofGetFrameNum() * 0.3);
    
    cam.setTarget(ofVec3f(0, 0, 0));
    ofVec3f v = ofVec3f(r*sin(theta)*cos(phy), r*sin(theta)*sin(phy), r*cos(theta));
    cam.setDistance(1200);
    //    cam.setPosition(v);
    
    auto threshold = 0.65f;
    for (auto& triangle : this->triangles) {
        
        auto base_location_a = glm::vec3(triangle.getVertex(0).x, triangle.getVertex(0).y, triangle.getVertex(0).z);
        auto base_location_b = glm::vec3(triangle.getVertex(1).x, triangle.getVertex(1).y, triangle.getVertex(1).z);
        auto base_location_c = glm::vec3(triangle.getVertex(2).x, triangle.getVertex(2).y, triangle.getVertex(2).z);
        auto base_avg = (base_location_a + base_location_b + base_location_c) / 3;
        
        // 隣接する図形同士で重なる部分が出てくるので調整値の分だけ縮める
        float t = ofGetElapsedTimef()*117.8/60.0;
        float x = sin(t*2*PI);
        if (x < 0.4) {
            x = 0.4;
        } else if (x > 0.95) {
            x = 0.95;
        }
        
        base_location_a = (base_location_a - base_avg) * x + base_avg;
        base_location_b = (base_location_b - base_avg) * x + base_avg;
        base_location_c = (base_location_c - base_avg) * x + base_avg;
        
//        auto noise_value = ofNoise(fftSmoothed[340] * 100, base_avg.y * 0.005, base_avg.z * 0.005, ofGetFrameNum() * 0.0025);
        auto noise_value = ofNoise(base_avg.x * 0.005, base_avg.y * 0.005, base_avg.z * 0.005, ofGetFrameNum() * 0.0025); // 代替
        if (noise_value >= threshold) {
            
            auto tmp_location_a = glm::normalize(base_location_a) * ofMap(noise_value, threshold, 1.0, 300, 470);
            auto tmp_location_b = glm::normalize(base_location_b) * ofMap(noise_value, threshold, 1.0, 300, 450);
            auto tmp_location_c = glm::normalize(base_location_c) * ofMap(noise_value, threshold, 1.0, 300, 430);
            
            ofFill();
            ofSetColor(39);
            ofBeginShape();
            ofVertex(tmp_location_a);
            ofVertex(tmp_location_b);
            ofVertex(tmp_location_c);
            ofEndShape(true);
            
            ofBeginShape();
            ofVertex(base_location_a);
            ofVertex(base_location_b);
            ofVertex(tmp_location_b);
            ofVertex(tmp_location_a);
            ofEndShape(true);
            
            ofBeginShape();
            ofVertex(base_location_b);
            ofVertex(base_location_c);
            ofVertex(tmp_location_c);
            ofVertex(tmp_location_b);
            ofEndShape(true);
            
            ofBeginShape();
            ofVertex(base_location_c);
            ofVertex(base_location_a);
            ofVertex(tmp_location_a);
            ofVertex(tmp_location_c);
            ofEndShape(true);
            
            ofNoFill();
            ofSetColor(239);
            ofBeginShape();
            ofVertex(tmp_location_a);
            ofVertex(tmp_location_b);
            ofVertex(tmp_location_c);
            ofEndShape(true);
            
            ofBeginShape();
            ofVertex(base_location_a);
            ofVertex(base_location_b);
            ofVertex(tmp_location_b);
            ofVertex(tmp_location_a);
            ofEndShape(true);
            
            ofBeginShape();
            ofVertex(base_location_b);
            ofVertex(base_location_c);
            ofVertex(tmp_location_c);
            ofVertex(tmp_location_b);
            ofEndShape(true);
            
            ofBeginShape();
            ofVertex(base_location_c);
            ofVertex(base_location_a);
            ofVertex(tmp_location_a);
            ofVertex(tmp_location_c);
            ofEndShape(true);
        }
        else {
            
            ofFill();
            ofSetColor(39);
            ofBeginShape();
            ofVertex(base_location_a);
            ofVertex(base_location_b);
            ofVertex(base_location_c);
            ofEndShape(true);
            
            ofNoFill();
            ofSetColor(239);
            ofBeginShape();
            ofVertex(base_location_a);
            ofVertex(base_location_b);
            ofVertex(base_location_c);
            ofEndShape(true);
        }
    }
    
    this->cam.end();
    
}

//--------------------------------------------------------------
void sceneE::keyPressed(int key){
    
}

//--------------------------------------------------------------
void sceneE::keyReleased(int key){
    
}

//--------------------------------------------------------------
void sceneE::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void sceneE::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneE::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneE::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneE::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void sceneE::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void sceneE::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void sceneE::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void sceneE::dragEvent(ofDragInfo dragInfo){
    
}
