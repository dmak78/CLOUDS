//
//  CloudsVisualSystemColony.h
//  VSColony
//
//  Created by Patricio Gonzalez Vivo on 6/26/13.
//
//

#pragma once

#include "CloudsVisualSystem.h"

#include "gCell.h"

class CloudsVisualSystemColony : public CloudsVisualSystem {
public:
    
    string getSystemName();
    
    void selfSetup();
    void selfSetupGuis();
    
    void selfAutoMode();
    void selfUpdate();
    void selfDrawBackground();
    void selfDraw();
    void selfDrawDebug();
    void selfSceneTransformation();
    void selfPostDraw();
    
    void selfExit();
    void selfBegin();
    void selfEnd();
    
    void selfKeyPressed(ofKeyEventArgs & args);
    void selfKeyReleased(ofKeyEventArgs & args);
    
    void mouseDragged(ofMouseEventArgs & args);
    void mouseMoved(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    
    void selfSetupGui();
    void selfGuiEvent(ofxUIEventArgs &e);
    
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);
    
	void loadShader();
    void reallocateFramebuffers();
    
private:
    
    //much geometry
    ofVboMesh   vbo;
    ofShader    noiseShader;
    ofShader    cellShader;
    ofShader    levelSet;
    ofShader    billboard;
    
    //wow video
    ofFbo fbo;
    ofTexture sprite;
    
    //lol data
    colonyPartitionMap pMap;
    vector< cellPtr > cells;

    float   noiseZoom;
    int newbornCount;
    
    bool reset; //TODO: used?
    
    /*  PARAMS */
    cellParams params;
    float numInitialCells; //float because ints won't work in gui
};
