#pragma once

#include <memory>
#include <vector>

#include "ofMain.h"
#include "ofxGui.h"

#include "solarsystem.h"

class ofApp : public ofBaseApp {
private:
    int m_nPlanets;
    int m_nSuns;
    int m_traceSize;

    ofEasyCam m_cam;
    ofSpherePrimitive m_sphere;
    ofLight m_globalLight;
    ofMaterial m_material;
    ofMaterial m_sunMaterial;

    ofxPanel m_gui;
    ofxIntSlider m_planetCountSlider;
    ofxIntSlider m_sunCountSlider;
    ofxIntSlider m_traceSizeSlider;
    ofxFloatSlider m_planetRadiusMaxSlider;
    ofxFloatSlider m_planetRadiusMinSlider;
    ofxFloatSlider m_planetSpeedMaxSlider;
    ofxFloatSlider m_planetSpeedMinSlider;
    ofxFloatSlider m_planetMassMaxSlider;
    ofxFloatSlider m_planetMassMinSlider;

    std::vector<ofLight> m_lights;
    std::vector<ofPolyline> m_traces;
    std::shared_ptr<SolarSystem> m_solarSystem;

public:
    void setup();
    void update();
    void draw();

    void initSolarSystem();

    void planetCountChanged(int &value);
    void sunCountChanged(int &value);
    void traceSizeChanged(int &value);

    void planetRadiusMinChanged(float &value);
    void planetRadiusMaxChanged(float &value);
    void planetSpeedMinChanged(float &value);
    void planetSpeedMaxChanged(float &value);
    void planetMassMinChanged(float &value);
    void planetMassMaxChanged(float &value);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

};
