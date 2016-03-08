/*
 *  BaseEngine.h
 *
 *  Created by jason van cleave on 2/10/14.
 *  Copyright 2014 jasonvancleave.com. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

#include <IL/OMX_Core.h>
#include <IL/OMX_Component.h>
#include <IL/OMX_Index.h>
#include <IL/OMX_Image.h>
#include <IL/OMX_Video.h>
#include <IL/OMX_Broadcom.h>

#include "OMXCameraSettings.h"
#include "OMXCameraUtils.h"

class BaseEngine: public ofThread
{
public:
	BaseEngine();
	
	virtual void setup(OMXCameraSettings omxCameraSettings) = 0;
	void stopRecording();
	
	OMX_HANDLETYPE camera;
	
	bool isOpen;
	virtual int getFrameCounter() = 0;
    
    
    OMXCameraSettings& getSettings();
    
protected:
	
    OMXCameraSettings omxCameraSettings;
	void configureCameraResolution();
	void configureEncoder();
	
	OMX_HANDLETYPE splitter;
	OMX_HANDLETYPE encoder;
	OMX_HANDLETYPE render;
	
	
	bool didWriteFile;
	
	int recordingBitRate;
	float numMBps;
	
	bool stopRequested;
	bool isStopping;
	int isKeyframeValid;
	bool doFillBuffer;
	bool bufferAvailable;
	
	void threadedFunction();
	void writeFile();
	
	ofBuffer recordingFileBuffer;
	OMX_BUFFERHEADERTYPE* encoderOutputBuffer;
	
	int recordedFrameCounter;
	
	static OMX_ERRORTYPE 
    splitterEventHandlerCallback(OMX_HANDLETYPE, 
                                 OMX_PTR, 
                                 OMX_EVENTTYPE, 
                                 OMX_U32, 
                                 OMX_U32, OMX_PTR){return OMX_ErrorNone;};

	static OMX_ERRORTYPE 
    encoderEventHandlerCallback(OMX_HANDLETYPE, 
                                OMX_PTR, 
                                OMX_EVENTTYPE, 
                                OMX_U32, OMX_U32, 
                                OMX_PTR){return OMX_ErrorNone;};
	static OMX_ERRORTYPE 
    encoderEmptyBufferDone(OMX_IN OMX_HANDLETYPE, 
                           OMX_IN OMX_PTR, 
                           OMX_IN OMX_BUFFERHEADERTYPE*){return OMX_ErrorNone;};
	
	static OMX_ERRORTYPE 
    renderEventHandlerCallback(OMX_HANDLETYPE, 
                               OMX_PTR, 
                               OMX_EVENTTYPE, 
                               OMX_U32, 
                               OMX_U32, 
                               OMX_PTR){return OMX_ErrorNone;};
	static OMX_ERRORTYPE 
    renderEmptyBufferDone(OMX_IN OMX_HANDLETYPE, 
                          OMX_IN OMX_PTR, 
                          OMX_IN OMX_BUFFERHEADERTYPE*){return OMX_ErrorNone;};
    
	static OMX_ERRORTYPE 
    renderFillBufferDone(OMX_IN OMX_HANDLETYPE, 
                         OMX_IN OMX_PTR, 
                         OMX_IN OMX_BUFFERHEADERTYPE*){return OMX_ErrorNone;};
	
};