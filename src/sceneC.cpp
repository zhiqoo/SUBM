#include "sceneC.hpp"

//--------------------------------------------------------------
void sceneC::setup(){
    
    ofSetVerticalSync(false);
    ofDisableAlphaBlending();
    
    cam.setupPerspective();
    
    //パーティクルの数を設定
    particleNum = 300000;
    texRes = ceil(sqrt(particleNum)); // 解像度一辺と切り上げ
    
    // レンダリング用シェーダーの読み込み
    render.load("shaders/render");
    
    // アップデート用シェーダーの読み込み
    updatePos.load("","shaders/update.frag");
    
    // パーティクルの初期設定
    particles.setMode(OF_PRIMITIVE_POINTS);
    for(int i=0;i<texRes;i++){
        for(int j=0;j<texRes;j++){
            int index = i * texRes + j;
            if(index < particleNum){
                particles.addVertex(ofVec3f(0,0,0));
                particles.addTexCoord(ofVec2f(i, j)); // Fboのテクスチャー内で、データを読み出す位置を設定
                particles.addColor(ofFloatColor(1.0,1.0,1.0,0.5));
            }
        }
    }
    
    // パーティクルの座標・加速度の保存用Fbo
    // RGBA32Fの形式で2つのColorbufferを用意
    pingPong.allocate(texRes, texRes, GL_RGBA32F, 2);
    
    // パーティクルの位置と経過時間の初期設定
    float *posAndAge = new float[texRes * texRes * 4];
    for (int x = 0; x < texRes; x++){
        for (int y = 0; y < texRes; y++){
            int i = texRes * y + x;
            posAndAge[i*4 + 0] = ofRandom(-1.0,1.0);
            posAndAge[i*4 + 1] = ofRandom(-1.0,1.0);
            posAndAge[i*4 + 2] = ofRandom(-1.0,1.0);
            posAndAge[i*4 + 3] = 0;
        }
    }
    //pingPongBufferに初期値を書き込み
    pingPong.src->getTextureReference(0).loadData(posAndAge, texRes, texRes, GL_RGBA);
    delete [] posAndAge;
    
    // パーティクルの速度と生存期間の初期設定
    float *velAndMaxAge = new float[texRes * texRes * 4];
    for (int x = 0; x < texRes; x++){
        for (int y = 0; y < texRes; y++){
            int i = texRes * y + x;
            velAndMaxAge[i*4 + 0] = 0.0;
            velAndMaxAge[i*4 + 1] = 0.0;
            velAndMaxAge[i*4 + 2] = 0.0;
            velAndMaxAge[i*4 + 3] = ofRandom(1, 150);
        }
    }
    
    //pingPongBufferに初期値を書き込み
    pingPong.src->getTextureReference(1).loadData(velAndMaxAge, texRes, texRes, GL_RGBA);
    delete [] velAndMaxAge;
    
    r = 5000;
    theta = 0;
    phy = 0.2;
    
}

//--------------------------------------------------------------
void sceneC::update(){
    
    float time = ofGetElapsedTimef();
    
    // パーティクルの発生位置を更新
    prevEmitterPos = emitterPos;
    emitterPos = 300 * ofVec3f(ofSignedNoise(time, 0, 0),ofSignedNoise(0, time, 0),ofSignedNoise(0, 0, time));
    //    emitterPos = ofVec3f(ofGetElapsedTimef(), 0, 0);
    
    // パーティクルの位置を計算
    pingPong.dst->begin();
    
    // 複数バッファの書き出しを有効化
    pingPong.dst->activateAllDrawBuffers();
    ofClear(0);
    updatePos.begin();
    
    // パーティクルの位置と経過時間
    updatePos.setUniformTexture("u_posAndAgeTex", pingPong.src->getTextureReference(0), 0);
    
    // パーティクルの速度と生存期間
    updatePos.setUniformTexture("u_velAndMaxAgeTex", pingPong.src->getTextureReference(1), 1);
    updatePos.setUniform1f("u_time", time);
    updatePos.setUniform1f("u_timestep", 0.5);
    updatePos.setUniform1f("u_scale", 0.005);
    updatePos.setUniform3f("u_emitterPos", emitterPos.x, emitterPos.y, emitterPos.z);
    updatePos.setUniform3f("u_prevEmitterPos", prevEmitterPos.x, prevEmitterPos.y, prevEmitterPos.z);
    pingPong.src->draw(0, 0);
    updatePos.end();
    pingPong.dst->end();
    pingPong.swap();
    
//    volume = ofSoundGetSpectrum(nBandsToGet);
//
//    for (int i = 0; i < nBandsToGet; i++) {
//        fftSmoothed[i] *= 0.96f;
//        if (fftSmoothed[i] < volume[i]) {
//            fftSmoothed[i] = volume[i];
//        }
//    }
//
//    theta += 0.1 * fftSmoothed[120];
//    phy += 0.1 * fftSmoothed[40];
    
}

//--------------------------------------------------------------
void sceneC::draw(){
    
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnablePointSprites();
    cam.begin();
    cam.setDistance(5000);
    ofVec3f v = ofVec3f(r*sin(theta)*cos(phy), r*sin(theta)*sin(phy), r*cos(theta));
    cam.setPosition(v);
    cam.setTarget(ofVec3f(0, 0, 0));
    std::cout << theta << endl;
    //    cam.setTarget(emitterPos);
    render.begin();
    
    // パーティクルの位置と経過時間
    render.setUniformTexture("u_posAndAgeTex", pingPong.src->getTextureReference(0), 0);
    particles.draw();
    render.end();
    cam.end();
    ofDisablePointSprites();
    ofPopStyle();
    
}

//--------------------------------------------------------------
void sceneC::keyPressed(int key){
    
}

//--------------------------------------------------------------
void sceneC::keyReleased(int key){
    
}

//--------------------------------------------------------------
void sceneC::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void sceneC::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneC::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneC::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sceneC::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void sceneC::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void sceneC::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void sceneC::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void sceneC::dragEvent(ofDragInfo dragInfo){
    
}
