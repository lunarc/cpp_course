#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    for (int i=0; i<400; i++)
    {
        m_points.push_back(ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));
        m_colors.push_back(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 128));
        m_radius.push_back(double(ofRandom(5,30)));

        ofVec2f v(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0));
        v.normalize();

        v = v * 0.2;

        m_speed.push_back(v);
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    for (auto i=0; i<m_points.size(); i++)
    {
        m_points[i].x += m_speed[i].x;
        m_points[i].y += m_speed[i].y;

        if (m_points[i].x>ofGetWidth())
            m_points[i].x = 0.0;

        if (m_points[i].x<0.0)
            m_points[i].x = ofGetWidth();

        if (m_points[i].y>ofGetHeight())
            m_points[i].y = 0.0;

        if (m_points[i].y<0.0)
            m_points[i].y = ofGetHeight();
    }    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);

    for (auto i=0; i<m_points.size(); i++)
    {
        ofSetColor(m_colors[i]);
        ofDrawCircle(m_points[i].x, m_points[i].y, m_radius[i]);
    }
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
