#include "sceneB.hpp"

//--------------------------------------------------------------
void sceneB::setup(){
    
    ofSetVerticalSync(true);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(60);
    
    ofEnableDepthTest();
    
    glPointSize(3);
    
    myMesh = ofPlanePrimitive(1000, 1000, 100, 100).getMesh();
    
}

//--------------------------------------------------------------
void sceneB::update(){
    
    for (int i = 0; i < myMesh.getVertices().size(); i++) {
        ofVec3f point = myMesh.getVertices()[i] / 400.0;
//        float z = 300 * fftSmoothed[(i)%nBandsToGet];
        float z = 300; // 代替
        myMesh.setVertex(i, ofVec3f(myMesh.getVertices()[i].x, myMesh.getVertices()[i].y, z));
    }

    if (ofGetElapsedTimeMillis()%1000 >= 0 && ofGetElapsedTimeMillis()%1000 < 500) {
        myMesh.setMode(OF_PRIMITIVE_POINTS);
    } else {
        myMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }
    
}

//--------------------------------------------------------------
void sceneB::draw(){
    
    cam.begin();
    myMesh.setMode(OF_PRIMITIVE_LINES);

    myMesh.draw();
    ofPushMatrix();
    ofTranslate(0, 0, 100);
    myMesh.draw();
    ofTranslate(0, 0, 100);
    myMesh.draw();
    ofTranslate(0, 0, 100);
    myMesh.draw();
    ofTranslate(0, 0, 100);
    myMesh.draw();
    ofPopMatrix();
    cam.end();

    
}

//--------------------------------------------------------------
void sceneB::keyPressed(int key){
    
}

//--------------------------------------------------------------
void sceneB::keyReleased(int key){
    
}

//--------------------------------------------------------------
void sceneB::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void sceneB::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneB::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneB::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneB::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void sceneB::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void sceneB::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void sceneB::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void sceneB::dragEvent(ofDragInfo dragInfo){
    
}
