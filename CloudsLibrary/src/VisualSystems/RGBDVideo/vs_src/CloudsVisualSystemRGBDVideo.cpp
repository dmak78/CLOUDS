
#include "CloudsVisualSystemRGBDVideo.h"
#include "CloudsGlobal.h"

//--------------------------------------------------------------
CloudsVisualSystemRGBDVideo::CloudsVisualSystemRGBDVideo(){
	videoPathField = NULL;
	movieLoaded = false;
}

//--------------------------------------------------------------
string CloudsVisualSystemRGBDVideo::getSystemName(){
	return "RGBDVideo";
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::selfSetup(){
	
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::selfBegin(){

}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::selfSetupGuis(){
	
	ofxUISuperCanvas *g = new ofxUISuperCanvas("RGBDVideo", gui);
    g->copyCanvasStyle(gui);
    g->copyCanvasProperties(gui);
    g->setPosition(guis[guis.size()-1]->getRect()->x+guis[guis.size()-1]->getRect()->getWidth()+1, 0);
	
    g->setName("VideoSettings");
    g->setWidgetFontSize(OFX_UI_FONT_SMALL);

    videoPathField = g->addTextInput("VideoPath", "");
	g->addButton("Load Video", false);
	
    g->autoSizeToFitWidgets();

	ofAddListener(g->newGUIEvent, this, &CloudsVisualSystemRGBDVideo::selfGuiEvent);
	
    guis.push_back(g);
    guimap[g->getName()] = g;
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::selfUpdate(){
	if(movieLoaded){
		player.update();
	}
}

void CloudsVisualSystemRGBDVideo::selfDrawBackground(){
}

void CloudsVisualSystemRGBDVideo::selfDrawDebug(){

}

void CloudsVisualSystemRGBDVideo::selfSceneTransformation(){
	
}

void CloudsVisualSystemRGBDVideo::selfDraw(){
	if(movieLoaded){
		
		rgbdPixelToPixelShader.begin();
		rgbdPixelToPixelShader.setUniform2f("depthPP", videoIntrinsics.depthPP.x,videoIntrinsics.depthPP.y );
		rgbdPixelToPixelShader.setUniform2f("depthFOV", videoIntrinsics.depthFOV.x,videoIntrinsics.depthFOV.y );
		rgbdPixelToPixelShader.setUniform2f("depthFOV", videoIntrinsics.depthFOV.x,videoIntrinsics.depthFOV.y );
		rgbdPixelToPixelShader.setUniform1f("minDepth", videoIntrinsics.depthRange.min);
		rgbdPixelToPixelShader.setUniform1f("maxDepth", videoIntrinsics.depthRange.max);
		rgbdPixelToPixelShader.setUniform1f("scale", 1.0);
		rgbdPixelToPixelShader.setUniform1f("offset", 0.0);

		mesh.draw();
		
		rgbdPixelToPixelShader.end();
		
	}
}

void CloudsVisualSystemRGBDVideo::selfExit(){
	
}

void CloudsVisualSystemRGBDVideo::selfPresetLoaded(string presetPath){
	playMovie( videoPathField->getTextString() );
}

bool CloudsVisualSystemRGBDVideo::playMovie(string filePath){
	movieLoaded = false;
	if( filePath != "" && ofFile(getDataPath() + "rgbdmovies/" + filePath).exists() ){
		
		if(!player.loadMovie(filePath)){
			ofLogError("CloudsVisualSystemRGBDVideo::selfPresetLoaded") << "Video File " << filePath << " Failed to load";
			return false;
		}
		
		ofxXmlSettings intrinsicsXml;
		string xmlFilePath = ofFilePath::removeExt(filePath) + ".xml";
		if(!intrinsicsXml.load(xmlFilePath)){
			ofLogError("CloudsVisualSystemRGBDVideo::selfPresetLoaded") << "XML File " << xmlFilePath << " Failed to load";
			return false;
		}
		
		videoIntrinsics.depthFOV.x = intrinsicsXml.getValue("depth:fovx", 0.);
		videoIntrinsics.depthFOV.y = intrinsicsXml.getValue("depth:fovy", 0.);
		videoIntrinsics.depthRange.min = intrinsicsXml.getValue("depth:minDepth", 0.);
		videoIntrinsics.depthRange.max = intrinsicsXml.getValue("depth:maxDepth", 0.);
		//TODO: read from xml
		videoIntrinsics.depthPP.x = 320;
		videoIntrinsics.depthPP.y = 240;
		player.play();
		movieLoaded = true;
		return true;
	}
	return false;
}

void CloudsVisualSystemRGBDVideo::selfEnd(){
}

void CloudsVisualSystemRGBDVideo::selfKeyPressed(ofKeyEventArgs & args){

}

void CloudsVisualSystemRGBDVideo::selfKeyReleased(ofKeyEventArgs & args){
	
}

void CloudsVisualSystemRGBDVideo::selfMouseDragged(ofMouseEventArgs& data){
	
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::selfMouseMoved(ofMouseEventArgs& data){
	
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::selfMousePressed(ofMouseEventArgs& data){
	
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::selfMouseReleased(ofMouseEventArgs& data){
	
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::selfSetupGui(){
	
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::selfGuiEvent(ofxUIEventArgs &e){
	
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::selfSetupSystemGui(){
	
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::guiSystemEvent(ofxUIEventArgs &e){
}

void CloudsVisualSystemRGBDVideo::selfSetupRenderGui(){
//	rdrGui->addButton("regenerate", false);
//	rdrGui->addSlider("speed", 1, 20, &speed);
	
}

//--------------------------------------------------------------
void CloudsVisualSystemRGBDVideo::guiRenderEvent(ofxUIEventArgs &e){

}
