#pragma once

#include "ofMain.h"

#include <vector>

class ofApp : public ofBaseApp {
private:
	ofLight m_light;
	ofEasyCam m_cam;
	ofSpherePrimitive m_sphere;
	ofMaterial m_sphereMaterial;

	std::vector<ofVec3f> m_positions;
	std::vector<float> m_size;
	std::vector<ofColor> m_colors;
	std::vector<ofVec3f> m_speed;

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
};
