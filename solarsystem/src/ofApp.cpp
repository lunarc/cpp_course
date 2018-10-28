#include "ofApp.h"

#define FRAME_RATE 60

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(FRAME_RATE);
    ofEnableDepthTest();
    //ofEnableAntiAliasing();

    m_nPlanets = 1000;
    m_nSuns = 4;
    m_traceSize = 200;

    m_sphere.set(1.0, 10);
    m_globalLight.setPosition(0, 0, 0);
    m_globalLight.setDirectional();

    m_material.setDiffuseColor(ofColor(200, 100, 0));
    m_sunMaterial.setDiffuseColor(ofColor(200, 100, 0));
    m_sunMaterial.setEmissiveColor(ofColor(250, 150, 0));

    m_cam.setDistance(100);
    m_solarSystem = std::make_shared<SolarSystem>(m_nPlanets, m_nSuns);

    this->initSolarSystem();

    m_gui.setup();
    m_gui.add(m_planetCountSlider.setup("Number of planets", m_nPlanets, 0, 2000));
    m_gui.add(m_sunCountSlider.setup("Number of suns", m_nSuns, 1, 4));
    m_gui.add(m_traceSizeSlider.setup("Trace size", m_traceSize, 0, 1000));
    m_gui.add(m_planetRadiusMaxSlider.setup("Planet radius max", m_solarSystem->planetRadiusMax(), 10.0, 200.0));
    m_gui.add(m_planetRadiusMinSlider.setup("Planet radius min", m_solarSystem->planetRadiusMin(), 10.0, 200));
    m_gui.add(m_planetSpeedMaxSlider.setup("Planet speed max", m_solarSystem->planetSpeedMax(), 1.0, 100.0));
    m_gui.add(m_planetSpeedMinSlider.setup("Planet speed min", m_solarSystem->planetSpeedMin(), 1.0, 100.0));
    m_gui.add(m_planetMassMaxSlider.setup("Planet mass max", m_solarSystem->planetMassMax(), 0.1, 10.0));
    m_gui.add(m_planetMassMinSlider.setup("Planet mass min", m_solarSystem->planetMassMin(), 0.1, 10.0));

    m_planetCountSlider.addListener(this, &ofApp::planetCountChanged);
    m_sunCountSlider.addListener(this, &ofApp::sunCountChanged);
    m_traceSizeSlider.addListener(this, &ofApp::traceSizeChanged);
    m_planetRadiusMinSlider.addListener(this, &ofApp::planetRadiusMinChanged);
    m_planetRadiusMaxSlider.addListener(this, &ofApp::planetRadiusMaxChanged);
    m_planetSpeedMinSlider.addListener(this, &ofApp::planetSpeedMinChanged);
    m_planetSpeedMaxSlider.addListener(this, &ofApp::planetSpeedMaxChanged);
    m_planetMassMinSlider.addListener(this, &ofApp::planetMassMinChanged);
    m_planetMassMaxSlider.addListener(this, &ofApp::planetMassMaxChanged);

}

void ofApp::initSolarSystem()
{
    m_solarSystem->setSize(m_nPlanets, m_nSuns);
    m_solarSystem->init();

    m_traces.clear();
    m_traces.resize(m_nPlanets);
    m_lights.clear();
    m_lights.resize(m_solarSystem->sunCount());
}


void ofApp::planetCountChanged(int &value)
{
    m_nPlanets = value;
    this->initSolarSystem();
}

void ofApp::sunCountChanged(int &value)
{
    m_nSuns = value;
    this->initSolarSystem();
}

void ofApp::traceSizeChanged(int & value)
{
    m_traceSize = value;
    m_traces.clear();
    m_traces.resize(m_nPlanets);
}

void ofApp::planetRadiusMinChanged(float & value)
{
    m_solarSystem->setPlanetRadiusMin(value);
    this->initSolarSystem();
}

void ofApp::planetRadiusMaxChanged(float & value)
{
    m_solarSystem->setPlanetRadiusMax(value);
    this->initSolarSystem();
}

void ofApp::planetSpeedMinChanged(float & value)
{
    m_solarSystem->setPlanetSpeedMin(value);
    this->initSolarSystem();
}

void ofApp::planetSpeedMaxChanged(float & value)
{
    m_solarSystem->setPlanetSpeedMax(value);
    this->initSolarSystem();
}

void ofApp::planetMassMinChanged(float & value)
{
    m_solarSystem->setPlanetMassMin(value);
    this->initSolarSystem();
}

void ofApp::planetMassMaxChanged(float & value)
{
    m_solarSystem->setPlanetMassMax(value);
    this->initSolarSystem();
}

void ofApp::update()
{
    m_solarSystem->update(1.0/FRAME_RATE);
    m_nPlanets = m_planetCountSlider;
}

void ofApp::draw()
{
    ofEnableDepthTest();

    ofClear(ofColor::black);

    m_cam.begin();

    double x, y, z;

    ofDisableLighting();

    for (auto trace : m_traces)
    {
        ofSetColor(100, 50, 0);
        trace.draw();
    }

    ofEnableLighting();

    m_material.begin();

    for (auto light : m_lights)
        light.enable();

    for (int i=0; i<m_solarSystem->planetCount(); i++)
    {
        auto planet = m_solarSystem->planetAt(i);
        planet->location().getComponents(x, y, z);

        m_traces[i].addVertex(x, y, z);
        if (m_traces[i].size() > m_traceSize)
            m_traces[i].getVertices().erase(m_traces[i].begin());

        m_sphere.setPosition(x, y, z);
        m_sphere.setScale(planet->mass()*0.4);
        m_sphere.draw();
    }

    m_material.end();

    for (auto light : m_lights)
        light.disable();

    m_globalLight.enable();

    m_sunMaterial.begin();
    for (int i = 0; i < m_solarSystem->sunCount(); i++)
    {
        auto sun = m_solarSystem->sunAt(i);
        sun->location().getComponents(x, y, z);

        m_sphere.setPosition(x, y, z);
        m_sphere.setScale(sun->mass()*0.4);
        m_sphere.draw();
    }
    m_sunMaterial.end();

    m_globalLight.disable();

    m_cam.end();

    ofDisableLighting();
    ofDisableDepthTest();

    m_gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

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
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{ 

}
