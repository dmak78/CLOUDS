//
//  CloudsVisualSystem2DVideo.cpp
//

#include "CloudsVisualSystem2DVideo.h"

//--------------------------------------------------------------
void CloudsVisualSystem2DVideo::selfSetupGui()
{
    vidCam = ofCamera();
	playerGui = new ofxUISuperCanvas("VideoPlayer", gui);
	playerGui->copyCanvasStyle(gui);
	playerGui->copyCanvasProperties(gui);
	playerGui->setName("VideoPlayer");
	playerGui->setWidgetFontSize(OFX_UI_FONT_SMALL);
    playerGui->addLabel("VIDEOS");
    playerGui->addSpacer();
    playerGui->addRadio("MOVIE FILES",movieStrings);
    playerGui->addSpacer();
    playerGui->addButton("SET IN TIME", false);
    playerGui->addButton("SET OUT TIME", false);
    playerGui->addSlider("INTIME", 0, 1000, &inTime);
    playerGui->addSlider("OUTTIME", 0, 1000, &outTime);
    
	ofAddListener(playerGui->newGUIEvent, this, &CloudsVisualSystem2DVideo::selfGuiEvent);
	guis.push_back(playerGui);
	guimap[playerGui->getName()] = playerGui;
}

void CloudsVisualSystem2DVideo:: selfSetDefaults(){
    primaryCursorMode = CURSOR_MODE_INACTIVE;
    secondaryCursorMode =  CURSOR_MODE_INACTIVE;
}

//--------------------------------------------------------------
void CloudsVisualSystem2DVideo::selfGuiEvent(ofxUIEventArgs &e)
{
    if (e.getKind() == OFX_UI_WIDGET_TOGGLE){

		if( ((ofxUIToggle*)e.widget)->getValue()){
			loadMovieWithName( e.widget->getName() );
		}
		
//        ofxUIToggle* t = (ofxUIToggle*)e.widget;
//        cout<<t->getName()<<endl;
//        for(int i =0; i<movieStrings.size(); i++){
//            if (movieStrings[i] == t->getName()) {
//				cout << "Loading movie from GUI " << movieStrings[i] << endl;
//                loadMovieAtIndex(i);
//            }
//        }
    }
    if (e.getKind() == OFX_UI_WIDGET_BUTTON){
        
        if(e.getName() == "SET IN TIME"){
            inTime = player->getCurrentTime();
        }
        else if (e.getName() == "SET OUT TIME"){
            outTime = player->getCurrentTime();
        }
    }
    
}
//void CloudsVisualSystem2DVideo::loadMovieAtIndex(int index){
//    if(player->isPlaying()){
//        player->stop();
//    }
//	
//    cout << getVisualSystemDataPath(true) << " : " << movieStrings[index]<<endl;
//	loadedMoviePath = movieStrings[index];
//	
//    if(player->loadMovie(getVisualSystemDataPath(true)+"videos/"+ movieStrings[index])){
//        player->play();
//        bFileLoaded = false;
//    }
//    else{
//        cout<<"couldn't load the movie"<<endl;
//    }
//}
//

void CloudsVisualSystem2DVideo::loadMovieAtIndex(int index, bool reset){


    if( player != NULL && player->isPlaying()  ){
        player->stop();
    }
    player = ofPtr<ofxAVFVideoPlayer>(new ofxAVFVideoPlayer());
	loadedMoviePath = movieStrings[index];
    if(player->loadMovie(getVisualSystemDataPath(true)+"videos/"+ movieStrings[index])){


		
        player->play();
        bFileLoaded = false;
		
		if(reset){
			inTime = 0;
			outTime = 0;
		}
    }
    else{
        ofLogError("CloudsVisualSystem2DVideo::loadMovieAtIndex") << "couldn't load the movie";
    }
	
	receivedFrame = false;
}

//Use system gui for global or logical settings, for exmpl
void CloudsVisualSystem2DVideo::selfSetupSystemGui(){
    
}

void CloudsVisualSystem2DVideo::guiSystemEvent(ofxUIEventArgs &e){
	
}
//use render gui for display settings, like changing colors
void CloudsVisualSystem2DVideo::selfSetupRenderGui(){
    
}

void CloudsVisualSystem2DVideo::guiRenderEvent(ofxUIEventArgs &e){
	
}

//--------------------------------------------------------------
void CloudsVisualSystem2DVideo::selfSetup()
{
    //MA: changed ofGetWidth() to GetCanvasWidth() and ofGetHeight() to GetCanvasHeight()
    screenRect = ofRectangle(0,0, getCanvasWidth(), getCanvasHeight());
    videoRect = ofRectangle(0,0, getCanvasWidth(), getCanvasHeight());
    
    movieIndex = 0;
    
//    movieStrings.push_back("traffic_1.mov");
//    movieStrings.push_back("unionsq_1 - Wi-Fi_Crop.mov");
    movieStrings.push_back("Alice.mov");
    movieStrings.push_back("D3_AAPL.mov");
    movieStrings.push_back("D3_Dial.mov");
    movieStrings.push_back("D3_Radial.mov");
    movieStrings.push_back("OpenPaths.mov");
    movieStrings.push_back("Exoplanets.mp4");
    movieStrings.push_back("Cascade.mov");
    movieStrings.push_back("DataTimeline.mov");
    movieStrings.push_back("CordDiagram_videogames.mov");
    movieStrings.push_back("zipcode.mov");
    movieStrings.push_back("USMap.mov");

    movieStrings.push_back("GitHub2.mov");
    movieStrings.push_back("Gource.mov");

    
    movieStrings.push_back("FaceSub_lowSat.mov");
    movieStrings.push_back("PeopleStaring.mp4");
    movieStrings.push_back("FaceShift_noise.mov");
    movieStrings.push_back("FaceSub_lowSat.mov");
    movieStrings.push_back("JapaneseSlow2.mov");
    movieStrings.push_back("TeensSlow.mov");
    
    movieStrings.push_back("Kittenstep.mov");
    movieStrings.push_back("Code_Screenflow3.mov");
    
    movieStrings.push_back("networkFlow2.mov");
    movieStrings.push_back("DesignByNumbers.mov");
    movieStrings.push_back("TweakMode.mov");
    movieStrings.push_back("Logo1.mov");
    movieStrings.push_back("Logo2.mov");
    movieStrings.push_back("Flow_1.mov");
    movieStrings.push_back("Flow2_Blue.mov");
    movieStrings.push_back("Flow5_Blue.mov");
    
    movieStrings.push_back("Reas_network1.mov");
    movieStrings.push_back("Reas_Process13.mov");
    
    
    
    loadMovieAtIndex(movieIndex, true);
    
}

//--------------------------------------------------------------
void CloudsVisualSystem2DVideo::restart()
{
    
}

//--------------------------------------------------------------
void CloudsVisualSystem2DVideo::selfPresetLoaded(string presetPath)
{   
    
}


void CloudsVisualSystem2DVideo::loadMovieWithName(string name){
    //LOADING MOVIE
//    ofxUIRadio* r = (ofxUIRadio*)playerGui->getWidget("MOVIE FILES");
//    vector<ofxUIToggle*> t = r->getToggles();
    
//    string movieName;
//    for(int j = 0; j < t.size(); j++){
//        if(t[j]->getValue()) {
//            movieName = t[j]->getName();
//
	
	for(int i = 0; i < movieStrings.size(); i++){
		if (movieStrings[i] == name) {
			loadMovieAtIndex(i, false);
			break;
		}
	}
	
//			break;
//        }
//    }
}

// selfBegin is called when the system is ready to be shown
// this is a good time to prepare for transitions
// but try to keep it light weight as to not cause stuttering
void CloudsVisualSystem2DVideo::selfBegin(){
	player->play();
}

//do things like ofRotate/ofTranslate here
//any type of transformation that doesn't have to do with the camera
void CloudsVisualSystem2DVideo::selfSceneTransformation(){
	
}

//--------------------------------------------------------------
void CloudsVisualSystem2DVideo::selfUpdate()
{
    screenRect.width = getCanvasWidth();
    screenRect.height = getCanvasHeight();
    
    if(player->getWidth() > 0){
        videoRect.x = 0;
        videoRect.y = 0;
        videoRect.width = player->getWidth();
        videoRect.height = player->getHeight();
        //DONT NEED FOR 3D Drawing
        //        videoRect.scaleTo(screenRect);
    
    }
    if (! bFileLoaded) {
        if(player->getWidth() >0){
            //this is to set the intime once the video has loaded
            cout<<"setting player time to : "<<inTime<<endl;
            player->setTime(inTime);
            bFileLoaded = true;
        }
        
    }
    
    player->update();
    receivedFrame |= player->isFrameNew();
	
    if(timeline->getDurationInSeconds() != (outTime - inTime)){
        if(outTime-inTime > 0){
            timeline->setDurationInSeconds(outTime - inTime);
        }
        else{
     
        }

    }
    else{
     
    }
    
}

ofCamera& CloudsVisualSystem2DVideo::getCameraRef(){
    return vidCam;
    
}

//--------------------------------------------------------------
void CloudsVisualSystem2DVideo::selfDraw()
{
//    ofCamera& cam =getCameraRef();
    if(player->isLoaded() && receivedFrame){

        
        ofVec3f topLeft = vidCam.screenToWorld(screenRect.getTopLeft());
        ofVec3f bottomLeft = vidCam.screenToWorld(screenRect.getBottomLeft());
        ofVec3f topRight =vidCam.screenToWorld(screenRect.getTopRight());
        ofVec3f bottomRight =vidCam.screenToWorld(screenRect.getBottomRight());

        
        //create a mesh
        ofMesh mesh;
        
        
        //TOP LEFT
        //texture coordinates are in the image space
        mesh.addTexCoord(videoRect.getTopLeft());
        //vertices are in the screen space
        mesh.addVertex(topLeft);

        //BOTTOM LEFT
        mesh.addTexCoord(videoRect.getBottomLeft());
        mesh.addVertex(bottomLeft);

        
        //TOP RIGHT
        mesh.addTexCoord(videoRect.getTopRight());
        mesh.addVertex(topRight);
        
        //BOTTOM RIGHT
        mesh.addTexCoord(videoRect.getBottomRight());
        mesh.addVertex(bottomRight);

        
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
        
        vidCam.begin();
        
        //translate so that 0,0 is the center of the screen
        ofPushMatrix();
        //Extract the rotation from the current rotation
        ofVec3f axis;
        float angle;
        curRot.getRotate(angle, axis);
        
        //apply the quaternion's rotation to the viewport and draw the sphere
        ofRotate(angle, axis.x, axis.y, axis.z);
        player->getTextureReference().bind();
        mesh.draw();
        player->getTextureReference().unbind();
        
        ofPopMatrix();
        

        vidCam.end();
	}
    
    
}

// draw any debug stuff here
void CloudsVisualSystem2DVideo::selfDrawDebug(){
    
}

//--------------------------------------------------------------
void CloudsVisualSystem2DVideo::selfDrawBackground()
{
	if(player->isLoaded() && receivedFrame){
//		player->draw(videoRect.x, videoRect.y, videoRect.width, videoRect.height);
	}
	else {
		ofLogError("CloudsVisualSystem2DVideo::selfDrawBackground") << "Video not loaded: " << loadedMoviePath;
	}
}

//--------------------------------------------------------------
void CloudsVisualSystem2DVideo::render()
{
    
}

// this is called when your system is no longer drawing.
// Right after this selfUpdate() and selfDraw() won't be called any more
void CloudsVisualSystem2DVideo::selfEnd(){
       player->stop();
	
}
// this is called when you should clear all the memory and delet anything you made in setup
void CloudsVisualSystem2DVideo::selfExit(){
 
}

//events are called when the system is active
//Feel free to make things interactive for you, and for the user!
void CloudsVisualSystem2DVideo::selfKeyPressed(ofKeyEventArgs & args){
	
    if(args.key == 'i' ){
        cout<<"in time :"<<player->getCurrentTime()<<endl;
        inTime = player->getCurrentTime();
    }
    else if (args.key == 'o'){
        cout<< "out time :"<<player->getCurrentTime()<<endl;
        outTime = player->getCurrentTime();
    }
    else if (args.key == 'a'){
        cout<<timeline->getDurationInSeconds()<<endl;
    }
}
void CloudsVisualSystem2DVideo::selfKeyReleased(ofKeyEventArgs & args){

}

void CloudsVisualSystem2DVideo::selfMouseDragged(ofMouseEventArgs& data){
//    float x = GetCloudsInputX();
//    float y = GetCloudsInputY();
//    
//    
//    ofVec2f mouse(x,y);
//    ofQuaternion yRot((x-getCanvasWidth()/2)*.001, ofVec3f(0,1,0));
//    ofQuaternion xRot((y-getCanvasHeight()/2    )*.001, ofVec3f(-1,0,0));
////    ofQuaternion yRot((x-getCanvasHeight()/2)*.01, ofVec3f(0,1,0));
////    ofQuaternion xRot((y-getCanvasWidth()/2)*.01, ofVec3f(-1,0,0));
//    curRot *= yRot*xRot;
}

void CloudsVisualSystem2DVideo::selfMouseMoved(ofMouseEventArgs& data){
    float x = GetCloudsInputX();
    float y = GetCloudsInputY();

    ofQuaternion yRot((x-getCanvasWidth()/2)*.01, ofVec3f(0,1,0));
    ofQuaternion xRot((y-getCanvasHeight()/2)*0.01, ofVec3f(1,0,0));

    curRot *= yRot*xRot;

}

void CloudsVisualSystem2DVideo::selfMousePressed(ofMouseEventArgs& data){
	
}

void CloudsVisualSystem2DVideo::selfMouseReleased(ofMouseEventArgs& data){
	
}