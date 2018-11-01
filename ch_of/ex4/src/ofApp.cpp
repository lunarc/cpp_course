#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofEnableDepthTest();
    ofEnableLighting();

    m_light.setup();
    m_light.setPosition(0, 0, -1.0);

    m_sphereMaterial.setDiffuseColor(ofFloatColor::yellow);
    m_sphereMaterial.setShininess(0.02);    

    m_sphere.setRadius(1.0);
    m_cam.setDistance(30.0);

    for (auto i=0; i<100; i++)
    {
        m_positions.push_back(
            ofVec3f(ofRandom(-10.0, 10.0), ofRandom(-10.0, 10.0), ofRandom(-10.0, 10.0)));
        m_size.push_back(ofRandom(0.5, 2.0));
        m_colors.push_back(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));

        ofVec3f speed(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0));
        speed.normalize();
        speed *= 0.1;
        m_speed.push_back(speed);
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    for (auto i=0; i<m_positions.size(); i++)
    {
        m_positions[i] += m_speed[i];

        if (m_positions[i].x>10.0)
            m_positions[i].x=-10.0;
        if (m_positions[i].x<-10.0)
            m_positions[i].x=10.0;
        if (m_positions[i].y>10.0)
            m_positions[i].y=-10.0;
        if (m_positions[i].y<-10.0)
            m_positions[i].y=10.0;
        if (m_positions[i].z>10.0)
            m_positions[i].z=-10.0;
        if (m_positions[i].z<-10.0)
            m_positions[i].z=10.0;
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    m_light.enable();

    m_light.setParent(m_cam);
    
    m_cam.begin();
    
    for (auto i=0; i<m_positions.size(); i++)
    {
        m_sphereMaterial.begin();
        m_sphereMaterial.setDiffuseColor(m_colors[i]);

        m_sphere.setPosition(
            m_positions[i].x,
            m_positions[i].y,
            m_positions[i].z);

        m_sphere.setRadius(m_size[i]);
        m_sphere.draw();
        m_sphereMaterial.end();
    }


    m_cam.end();    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
