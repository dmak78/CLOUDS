//
// CLOUDS Interactive Documentary
//
// VISUAL SYSTEMS
//
// Welcome to the EMPTY CloudsVisualSystem
//
//
//

#pragma once

#include "CloudsVisualSystem.h"
#include "ofxJSONElement.h"
#include "Tweeter.h"
#include "ofxFTGL.h"
//--------------------------------------------------------------
//--------------------------------------------------------------
class CloudsVisualSystemTwitter : public CloudsVisualSystem
{
  public:
    
	//This determines your data path so name it at first!
	//ie getVisualSystemDataPath() uses this
    string getSystemName() {
		return "Twitter";
	}

	//These methods let us add custom GUI parameters and respond to their events
    void selfSetupGui();
    void selfGuiEvent(ofxUIEventArgs &e);
    
	//Use system gui for global or logical settings, for exmpl
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
	//use render gui for display settings, like changing colors
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);

	// selfSetup is called when the visual system is first instantiated
	// This will be called during a "loading" screen, so any big images or
	// geometry should be loaded here
    void selfSetup();

	// selfBegin is called when the system is ready to be shown
	// this is a good time to prepare for transitions
	// but try to keep it light weight as to not cause stuttering
    void selfBegin();

	// selfPresetLoaded is called whenever a new preset is triggered
	// it'll be called right before selfBegin() and you may wish to
	// refresh anything that a preset may offset, such as stored colors or particles
	void selfPresetLoaded(string presetPath);
    
	//do things like ofRotate/ofTranslate here
	//any type of transformation that doesn't have to do with the camera
    void selfSceneTransformation();
	
	//normal update call
	void selfUpdate();

	// selfDraw draws in 3D using the default ofEasyCamera
	// you can change the camera by returning getCameraRef()
    void selfDraw();
	
	// use this to draw the point cloud
	void selfDrawRGBD();
	
    // draw any debug stuff here
	void selfDrawDebug();

	//draws through RGBD camera;
//	void selfDrawRGBD();
	
	// or you can use selfDrawBackground to do 2D drawings that don't use the 3D camera
	void selfDrawBackground();
	void selfEnd();
    void selfExit();
    void selfKeyPressed(ofKeyEventArgs & args);
    void selfKeyReleased(ofKeyEventArgs & args);
    
    void selfMouseDragged(ofMouseEventArgs& data);
    void selfMouseMoved(ofMouseEventArgs& data);
    void selfMousePressed(ofMouseEventArgs& data);
    void selfMouseReleased(ofMouseEventArgs& data);
    
    void loadJSONData();
    void addUsersFromMentions();
    void createPajekNetwork();
    int getUserIdByName(string name);
    void updateMesh();
    
    void drawTweetsForDate(int index);
    vector<Tweeter> getTweetersForDate(int index);
    
    ofxJSONElement result;

    set<pair<int,int> > links;
    map<string,int> numberOfMentions;
    void parseClusterNetwork(string fileName);
    void loadMesh();
    Tweeter& getTweeterByID(vector<Tweeter>& tweeters, int _id );
    void CompareDates(Date d1,Date d2);

    vector<Date> dateIndex;
    map<string,int>dateIndexMap;
    
    string getDateAsString(Date d);
    
    
protected:
    ofTrueTypeFont listFont;
    ofColor listColor;
	
	ofxUISuperCanvas * listGui, * treeGui;
    ofx1DExtruder * listHue, * listSat, * listBri, * listAlpha;
    ofx1DExtruder * textHue, * textSat, * textBri, * textAlpha;
	ofx1DExtruder * lineHue, * lineSat, * lineBri, * lineAlpha;
    
    vector<Tweeter> tweeters;
    stringstream ss;
    
    ofVboMesh mesh;
    ofVboMesh linksMesh;
    ofVec3f min,max;
    ofEasyCam cam;
    
    ofImage sprite;
    ofShader clusterShader;
    float meshExpansion;
    float pointSize;
    ofxUISuperCanvas* clusterGui;
    
    
    
    
	
};