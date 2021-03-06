#pragma once
#include <sapi.h>  
#include <sphelper.h> 
#include <Synchapi.h>
#include <algorithm>
#include <functional> 
#include <cctype>
#include <locale>

#include "ofxGui.h"

#include "2552software.h"
#include "kinect2552.h"
#include "timeline.h"
#include "draw.h"

class ofApp : public ofBaseApp{

	public:
		ofApp():ofBaseApp(){};

		void setup();
		void update();
		void draw();

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void keyPressed(int key);
		void exit();

		// audio
		void audioOut(ofSoundBuffer &outBuffer);
		//in
		void audioIn(float * input, int bufferSize, int nChannels);
		// audio

		// these items need to go some where else, maybe the App
		Software2552::KinectBodies bodies;
		Software2552::KinectFaces faces;
		Software2552::KinectAudio audio;
		Software2552::Kinect2552 myKinect;

		Software2552::Timeline timeline;

		void ofApp::drawScene(bool isPreview){
	
	ofEnableDepthTest();

	if (false) { // keep to learn how to tie to kinect
		ofPushStyle();
		ofSetColor(150, 100, 100);
		ofDrawGrid(1.0f, 5.0f, true);
		
		ofSetColor(255);
		
		//--
		//draw camera preview
		//
		headTrackedCamera.transformGL();
		
		ofPushMatrix();
		ofScale(0.002f, 0.002f, 0.002f);
		ofNode().draw();
		ofPopMatrix();
		
		ofMultMatrix(headTrackedCamera.getProjectionMatrix().getInverse());
		
		ofNoFill();
		ofDrawBox(2.0f);
		
		headTrackedCamera.restoreTransformGL();
		//
		//--
		
		//--
		//draw window preview
		//
		window.clear();
		window.addVertex(windowTopLeft);
		window.addVertex(windowBottomLeft);
		window.addVertex(windowBottomRight);
		window.setMode(OF_PRIMITIVE_LINE_STRIP);
		window.draw();
		glPointSize(3.0f);
		window.drawVertices();
		//
		//--
        ofPopStyle();
	}
	
	ofPushStyle();
	ofNoFill();
	ofColor col(200,100,100);
	for (float z = 0.0f; z > -40.0f; z-= 0.1f){
		col.setHue(int(-z * 100.0f + ofGetElapsedTimef() * 10.0f) % 360);
		ofSetColor(col);
		ofDrawRectangle(-windowWidth / 2.0f, -windowHeight / 2.0f, z, windowWidth, windowHeight);
	}
	ofPopStyle();
	
	ofPushStyle();
	ofEnableSmoothing();
	ofSetColor(255);
	ofSetLineWidth(5.0f);
	ofBeginShape();
	for (unsigned int i=0; i<headPositionHistory.size(); i++) {
		ofPoint vertex(headPositionHistory[i].x, headPositionHistory[i].y, -float( headPositionHistory.size() - i ) * 0.05f);
		ofCurveVertex(vertex);
	}
	ofEndShape(false);
	ofPopStyle();
	
	ofDisableDepthTest();
}

		ofLight	light;
		ofEasyCam camera;
		ofVideoPlayer test;
		ofMaterial material;
		int   appFPS;
		float sequenceFPS;
		bool  bFrameIndependent;
		
		void circleResolutionChanged(int & circleResolution);
		void ringButtonPressed();
		bool bHide;
		ofxFloatSlider radius;
		ofxColorSlider color;
		ofxVec2Slider center;
		ofxIntSlider circleResolution;
		ofxToggle filled;
		ofxButton twoCircles;
		ofxButton ringButton;
		ofxLabel screenSize;
		
		int years;
		ofxPanel gui;

		ofSoundPlayer ring;
		ofImage backgroundImage;
		// example only, but a good one, SceneAnimator sa;
		
		ofPlanePrimitive plane;
		ofCamera cam;
		float angle;
		ofVec3f previous, current;
		ofEasyCam easyCam;

		deque<ofVec3f> pathVertices;
		ofMesh pathLines;
		ofCamera headTrackedCamera;
		float windowWidth;
		float windowHeight;
		ofVec3f windowTopLeft;
		ofVec3f windowBottomLeft;
		ofVec3f windowBottomRight;
		float viewerDistance;

		deque<ofPoint> headPositionHistory;

		ofVboMesh window;
};
