#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofEnableDepthTest();
    ofEnableLighting();

    m_light.setup();
    m_light.setPosition(0, 0, -1.0);
    m_boxMaterial.setDiffuseColor(ofFloatColor::red);
    m_boxMaterial.setShininess(0.02);    
    m_sphereMaterial.setDiffuseColor(ofFloatColor::yellow);
    m_sphereMaterial.setShininess(0.02);    

    m_box.set(10.0, 10.0, 10.0);
    m_sphere.setRadius(5.0);
    m_cam.setDistance(30.0);
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    m_light.enable();

    m_light.setParent(m_cam);
    
    m_cam.begin();
    
    m_boxMaterial.begin();
    m_box.setPosition(-5.0, 0.0, 0.0);
    m_box.draw();
    m_boxMaterial.end();

    m_sphereMaterial.begin();
    m_sphere.setPosition(5.0, 0.0, 0.0);
    m_sphere.draw();
    m_sphereMaterial.end();

    m_cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

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
