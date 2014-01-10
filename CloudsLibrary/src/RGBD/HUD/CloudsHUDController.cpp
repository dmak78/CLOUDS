//
//  CloudsHUDController.cpp
//  CloudsPointcloudViewer
//
//  Created by James George on 12/14/13.
//
//

#include "CloudsHUDController.h"
#include "CloudsGlobal.h"
#include "CloudsInput.h"
#include "CloudsClip.h"
#include "CloudsSpeaker.h"

CloudsHUDController::CloudsHUDController(){
	hudGui = NULL;
    bIsHudOpen = false;
    bSkipAVideoFrame = false;
    bDrawHud = true;
    bDrawHome = true;
	
    scaleAmt = 1.0;
}

void CloudsHUDController::setup(){
	buildLayerSets();
    calculateFontSizes();
	
	home.setup();
}

void CloudsHUDController::actBegan(CloudsActEventArgs& args){
//	bDrawHud = true;
}

void CloudsHUDController::actEnded(CloudsActEventArgs& args){
	animateOff( CLOUDS_HUD_FULL );
}

void CloudsHUDController::clipBegan(CloudsClipEventArgs& args){
	respondToClip(args.chosenClip);
}

void CloudsHUDController::visualSystemBegan(CloudsVisualSystemEventArgs& args){
	bDrawHud = false;
}

void CloudsHUDController::visualSystemEnded(CloudsVisualSystemEventArgs& args){
	bDrawHud = true;
}

void CloudsHUDController::questionAsked(CloudsQuestionEventArgs& args){
//    populateQuestion( args.question, true);
}

void CloudsHUDController::topicChanged(CloudsTopicEventArgs& args){

}

void CloudsHUDController::preRollRequested(CloudsPreRollEventArgs& args){
	
}

void CloudsHUDController::respondToClip(CloudsClip& clip){
	
//	cout << "ID's on clip " << clip.name << " and fcp id? " << clip.fcpFileId << endl;
//	cout << "Clip is " <<  clip.getLinkName() << endl;
//	cout << "speaker: " << speaker.firstName << " " << speaker.lastName << endl;
	
// LOWER THIRD
	CloudsSpeaker speaker = CloudsSpeaker::speakers[ clip.person ];
    populateLowerThird(speaker.firstName, speaker.lastName, speaker.location2, speaker.title, speaker.byline1, true );
    
// PROJECT EXAMPLE
	if(clip.hasProjectExample && clip.projectExample.exampleVideos.size() ){
		CloudsProjectExample example = clip.projectExample;
        string videoPath = example.exampleVideos[ (int)ofRandom(0, example.exampleVideos.size()) ];
        populateProjectExample( videoPath, example.creatorName, "", example.title, true );
	}
	else{
        animateOff(CLOUDS_HUD_PROJECT_EXAMPLE);
    }
}

void CloudsHUDController::questionHoverOn(string question){
	populateQuestion(question,true);
}

void CloudsHUDController::questionHoverOff(){
	animateOff( CLOUDS_HUD_QUESTION );
}

void CloudsHUDController::populateMap( string leftBox, string rightBox, bool forceOn){
    hudLabelMap["TopicTextBoxLeft"]->setText( leftBox );
    hudLabelMap["TopicTextBoxRight"]->setText( rightBox );
    
    if( forceOn ){
        animateOn( CLOUDS_HUD_MAP );
    }
}

void CloudsHUDController::populateQuestion( string question, bool forceOn ){
	if(hudLabelMap["QuestionTextBox"]->getText() == question){
		return;
	}
	else if(question == ""){
		animateOff( CLOUDS_HUD_QUESTION );
	}
	else{
		hudLabelMap["QuestionTextBox"]->setText( question );
		
		if( forceOn ){
			animateOn( CLOUDS_HUD_QUESTION );
		}
	}
}

void CloudsHUDController::populateLowerThird( string firstName, string lastName, string title, string location, string textbox, bool forceOn ) {
    hudLabelMap["BylineFirstNameTextBox_1_"]->setText( firstName );
    hudLabelMap["BylineLastNameTextBox"]->setText( lastName );
    hudLabelMap["BylineTopicTextBoxTop"]->setText( title );
    hudLabelMap["BylineTopicTextBoxBottom"]->setText( location );
    hudLabelMap["BylineBodyCopyTextBox"]->setText( textbox );
    
    if( forceOn ){
        animateOn( CLOUDS_HUD_LOWER_THIRD );
    }
}

void CloudsHUDController::populateProjectExample(string videoPath, string textLeft, string textRight, string textTop, bool forceOn) {
    if( videoPlayer.isPlaying() ){
        videoPlayer.stop();
    }
    
    if( ofFile(videoPath).exists() ){
        videoPlayer.loadMovie(videoPath);
        videoPlayer.play();
        
        bSkipAVideoFrame = true;
        
        hudLabelMap["ProjectExampleTextboxLeft"]->setText( textLeft );
        hudLabelMap["ProjectExampleTextboxRight"]->setText( textRight );
        hudLabelMap["ProjectExampleTextBoxTop"]->setText( textTop );
        
        if( forceOn ){
            animateOn( CLOUDS_HUD_PROJECT_EXAMPLE );
        }
    }else{
        cout << "CloudsHUDController :: Project example video does not exist: " << videoPath << endl;
    }
}

void CloudsHUDController::buildLayerSets(){
	
	//configure layers
	CloudsHUDLayerSet currentLayer;

	currentLayer = CLOUDS_HUD_QUESTION;
    
    CloudsHUDLayer* lowerThirdLayer = new CloudsHUDLayer();
    lowerThirdLayer->parseDirectory(GetCloudsDataPath() + "HUD/SVG/CLOUDS_HUD_LOWER_THIRD");
    layerSets[CLOUDS_HUD_LOWER_THIRD].push_back( lowerThirdLayer );
    allLayers.push_back( lowerThirdLayer );
    
    CloudsHUDLayer* questionLayer = new CloudsHUDLayer();
    questionLayer->parseDirectory(GetCloudsDataPath() + "HUD/SVG/CLOUDS_HUD_QUESTION");
    layerSets[CLOUDS_HUD_QUESTION].push_back( questionLayer );
    allLayers.push_back( questionLayer );
    
    CloudsHUDLayer* mapLayer = new CloudsHUDLayer();
    mapLayer->parseDirectory(GetCloudsDataPath() + "HUD/SVG/CLOUDS_HUD_MAP");
    layerSets[CLOUDS_HUD_MAP].push_back( mapLayer );
    allLayers.push_back( mapLayer );
    
    CloudsHUDLayer* projectExampleLayer = new CloudsHUDLayer();
    projectExampleLayer->parseDirectory(GetCloudsDataPath() + "HUD/SVG/CLOUDS_HUD_PROJECT_EXAMPLE");
    layerSets[CLOUDS_HUD_PROJECT_EXAMPLE].push_back( projectExampleLayer );
    allLayers.push_back( projectExampleLayer );
    
    for( int i=0; i<allLayers.size(); i++ ){
        allLayers[i]->duration = 1.5;
        allLayers[i]->delayTime = ofRandomuf();
        
        allLayers[i]->startPoint = ofVec2f(allLayers[i]->svg.getWidth(),0);
        allLayers[i]->endPoint   = ofVec2f(0,allLayers[i]->svg.getHeight());
    }
    
    home.bounds = lowerThirdLayer->svg.getMeshByID("HomeButtonFrame")->bounds;
    home.bounds.scaleFromCenter(1.5);
    
    svgVideoBounds = projectExampleLayer->svg.getMeshByID("ProjectExampleFrame")->bounds;
	videoBounds = svgVideoBounds;
    
    hudBounds.set( 0, 0, allLayers[0]->svg.getWidth(), allLayers[0]->svg.getHeight() );
    
//	cout << "HUD BOUNDS " << hudBounds.width << " / " << hudBounds.height << endl;
//    cout << "SCREEN " << ofGetScreenWidth() << " / " << ofGetScreenHeight() << endl;
}

void CloudsHUDController::calculateFontSizes(){
    // temporary allocate
    int minFontSize = 1;
    int maxFontSize = 70;
    
    for(int i = minFontSize; i < maxFontSize; i++){
        ofxFTGLFont *tmp = new ofxFTGLFont();
        tmp->loadFont( GetCloudsDataPath() + "font/Blender-THIN.ttf", i );
        tempFontList.push_back( tmp );
    }

    
    BylineBodyCopyTextBox       = getLayoutForLayer("BylineBodyCopyTextBox", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    BylineFirstNameTextBox      = getLayoutForLayer("BylineFirstNameTextBox_1_", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    BylineLastNameTextBox       = getLayoutForLayer("BylineLastNameTextBox", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    BylineTopicTextBoxBottom    = getLayoutForLayer("BylineTopicTextBoxBottom", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    BylineTopicTextBoxTop       = getLayoutForLayer("BylineTopicTextBoxTop", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    ResetButtonTextBox          = getLayoutForLayer("ResetButtonTextBox", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    QuestionTextBox             = getLayoutForLayer("QuestionTextBox", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    TopicTextBoxLeft            = getLayoutForLayer("TopicTextBoxLeft", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    TopicTextBoxRight           = getLayoutForLayer("TopicTextBoxRight", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    ProjectExampleTextboxLeft   = getLayoutForLayer("ProjectExampleTextboxLeft", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    ProjectExampleTextboxRight  = getLayoutForLayer("ProjectExampleTextboxRight", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    ProjectExampleTextBoxTop    = getLayoutForLayer("ProjectExampleTextBoxTop", GetCloudsDataPath() + "font/Blender-THIN.ttf");
    
    // cleanup!
    for( int i=0; i<tempFontList.size(); i++ ){
        delete tempFontList[i];
    }
    tempFontList.clear();
}

ofxFTGLSimpleLayout* CloudsHUDController::getLayoutForLayer( string layerName, string fontPath ) {
    for( int i=0; i<allLayers.size(); i++ ){
        SVGMesh* textMesh = allLayers[i]->svg.getMeshByID( layerName );
        
        if( textMesh != NULL ){
            textMesh->visible = false;
            
            float maxHeight = textMesh->bounds.height;
            int fontSize = getFontSizeForMesh( textMesh );
            
//            cout << "The correct font size is " << fontSize << " << endl;
            
            // make a layout
            ofxFTGLSimpleLayout *newLayout = new ofxFTGLSimpleLayout();
            newLayout->loadFont( fontPath, fontSize );
            newLayout->setLineLength( 999 );
            
            if( layerName == "BylineBodyCopyTextBox" ){         // this is the main body copy in the lower thirds
                newLayout->loadFont( fontPath, floor(fontSize/4.5) );
                newLayout->setLineLength( textMesh->bounds.width );
            }
            
            // make a label
            CloudsHUDLabel *newLabel = new CloudsHUDLabel();
            newLabel->setup( newLayout, textMesh->bounds );
            hudLabelMap[layerName] = newLabel;
            
            return newLayout;
        }
    }
    
    return NULL;
}

int CloudsHUDController::getFontSizeForMesh( SVGMesh* textMesh ){
    if( !textMesh ){
        ofLogError("CloudsHUDController :: Text box not found");
        return 0;
    }
    
    int fontSize = 0;
    float textBoxHeight = textMesh->bounds.height;
    
    for( int k=0; k<tempFontList.size()-1; k++){
        if( tempFontList[k]->getStringBoundingBox("W",0,0).height <= textBoxHeight && tempFontList[k+1]->getStringBoundingBox("W",0,0).height > textBoxHeight ){
            fontSize = 1 + k;
            break;
        }
    }
    
    return fontSize;
}

void CloudsHUDController::update(){
	for(int i = 0; i < allLayers.size(); i++){
		allLayers[i]->update();
	}
    
    float xScale = ofGetWindowWidth()/hudBounds.width;
    float yScale = ofGetWindowHeight()/hudBounds.height;
    
    scaleAmt = (xScale < yScale) ? xScale : yScale;

    home.hudScale = scaleAmt;
	home.update();
    
    if( videoPlayer.isPlaying() ){
        if( videoPlayer.isFrameNew() ){
            bSkipAVideoFrame = false;
            
            videoBounds.set(0, 0, videoPlayer.getWidth(), videoPlayer.getHeight() );
            videoBounds.scaleTo( svgVideoBounds );
        }
        videoPlayer.update();
    }
    
    if( home.wasHomeOpened() ){
        if( !bIsHudOpen ){
            animateOn( CLOUDS_HUD_FULL );
        }else{
            animateOff();
        }
    }
}

void CloudsHUDController::setHomeEnabled(bool enable){
	bDrawHome = enable;
}

void CloudsHUDController::draw(){
    
    if( !bDrawHud )
        return;
    
	ofPushStyle();
	ofPushMatrix();
	ofEnableAlphaBlending();
	
    ofVec2f hudSize(hudBounds.width*scaleAmt, hudBounds.height*scaleAmt);
    ofTranslate( (ofGetWindowSize() - hudSize ) * 0.5 );
    ofScale( scaleAmt, scaleAmt );
    
    if( videoPlayer.isPlaying() ){
        ofSetColor(255, 255, 255, 255*0.7);
        if( !bSkipAVideoFrame ){
            videoPlayer.draw( videoBounds.x, videoBounds.y, videoBounds.width, videoBounds.height );
        }
        ofSetColor(255, 255, 255, 255);
    }
    
	drawLayer(CLOUDS_HUD_QUESTION);
	
//	cout << "drawing question: " << hudLabelMap["QuestionTextBox"]->getText() << endl;
	
	drawLayer(CLOUDS_HUD_LOWER_THIRD);
	drawLayer(CLOUDS_HUD_PROJECT_EXAMPLE);
	drawLayer(CLOUDS_HUD_MAP);
    
    for( map<string, CloudsHUDLabel*>::iterator it=hudLabelMap.begin(); it!= hudLabelMap.end(); ++it ){
        (it->second)->draw();
    }
    
	if(bDrawHome){
		home.draw();
	}
	
	ofPopMatrix();
	ofPopStyle();
}

void CloudsHUDController::drawLayer(CloudsHUDLayerSet layer){
	for(int i = 0; i < layerSets[layer].size(); i++){
		layerSets[layer][i]->draw();
	}
}

void CloudsHUDController::animateOn(CloudsHUDLayerSet layer){
    //bIsHudOpen = true;
	
    if(hudOpenMap[layer]){
		return;
	}
	
    if( layer == CLOUDS_HUD_FULL ){
        for( int i=0; i<layerSets.size(); i++ ){
            for(int k = 0; k < layerSets[(CloudsHUDLayerSet)i].size(); i++){
                layerSets[(CloudsHUDLayerSet)i][k]->start();
				hudOpenMap[(CloudsHUDLayerSet)i] = true;
            }
        }
    }
    else {
        for(int i = 0; i < layerSets[layer].size(); i++){
            layerSets[layer][i]->start();
			hudOpenMap[layer] = true;
        }
		hudOpenMap[layer] = true;	
    }
	
	
}

void CloudsHUDController::animateOff(CloudsHUDLayerSet layer){
	//bIsHudOpen = false;
	if(!hudOpenMap[layer]){
		return;
	}

    if( videoPlayer.isPlaying() ){
        videoPlayer.stop();
        videoPlayer.close();
    }
    
    if( layer == CLOUDS_HUD_FULL ){
        for( int i=0; i<layerSets.size(); i++ ){
            for(int k = 0; k < layerSets[(CloudsHUDLayerSet)i].size(); i++){
                layerSets[(CloudsHUDLayerSet)i][k]->close();
				hudOpenMap[(CloudsHUDLayerSet)i] = false;
            }
        }
    }
    else{
        for(int i = 0; i < layerSets[layer].size(); i++){
            layerSets[layer][i]->close();
			hudOpenMap[layer] = false;
        }
    }
    
    // animate out text, this is sub-optimal
    if( layer == CLOUDS_HUD_FULL ){
        for( map<string, CloudsHUDLabel*>::iterator it=hudLabelMap.begin(); it!= hudLabelMap.end(); ++it ){
            (it->second)->animateOut();
        }
    }else if( layer == CLOUDS_HUD_LOWER_THIRD ){
        hudLabelMap["BylineFirstNameTextBox_1_"]->animateOut();
        hudLabelMap["BylineLastNameTextBox"]->animateOut();
        hudLabelMap["BylineTopicTextBoxTop"]->animateOut();
        hudLabelMap["BylineTopicTextBoxBottom"]->animateOut();
        hudLabelMap["BylineBodyCopyTextBox"]->animateOut();
    }else if( layer == CLOUDS_HUD_PROJECT_EXAMPLE ){
        hudLabelMap["ProjectExampleTextboxLeft"]->animateOut();
        hudLabelMap["ProjectExampleTextboxRight"]->animateOut();
        hudLabelMap["ProjectExampleTextBoxTop"]->animateOut();
    }else if( layer == CLOUDS_HUD_MAP ){
        
    }else if( layer == CLOUDS_HUD_QUESTION ){
        hudLabelMap["QuestionTextBox"]->animateOut();
    }
}

void CloudsHUDController::saveGuiSettings(){
	
}

void CloudsHUDController::toggleGuis(){
	
}

