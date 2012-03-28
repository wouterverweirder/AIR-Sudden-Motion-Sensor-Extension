// ADOBE SYSTEMS INCORPORATED
//  Copyright 2011 Adobe Systems Incorporated
//  All Rights Reserved.
//
// NOTICE: Adobe permits you to use, modify, and distribute this file in accordance with the
// terms of the Adobe license agreement accompanying it.  If you have received this file from a
// source other than Adobe, then your use, modification, or distribution of it requires the prior
// written permission of Adobe.

#include <stdlib.h>
#include <stdio.h>

#include "SuddenMotionSensorExtension.h"
#include "SuddenMotionSensorAdapter.h"
#include "unimotion.h"

// Symbols tagged with EXPORT are externally visible.
// Must use the -fvisibility=hidden gcc option.
#define EXPORT __attribute__((visibility("default")))

extern "C"
{
    
    FREObject SMS_isSupported(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
    {
        ////printf("SMS_isSupported\n");
        SuddenMotionSensorAdapter *adapter;
        FREGetContextNativeData(ctx, (void**)&adapter);
        
        FREObject retVal;
        bool success = adapter->isSupported();
		FRENewObjectFromBool(success, &retVal);
		return retVal;
    }
    
    FREObject SMS_startListening(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
    {
        ////printf("SMS_startListening\n");
        SuddenMotionSensorAdapter *adapter;
        FREGetContextNativeData(ctx, (void**)&adapter);
        adapter->start();
        return NULL;
    }
    
    FREObject SMS_stopListening(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
    {
        ////printf("SMS_stopListening\n");
        SuddenMotionSensorAdapter *adapter;
        FREGetContextNativeData(ctx, (void**)&adapter);
        adapter->dispose();
        return NULL;
    }
    
    FREObject SMS_setRequestedUpdateInterval(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
    {
        ////printf("SMS_setRequestedUpdateInterval\n");
		uint32_t updateInterval;
		FREGetObjectAsUint32(argv[0], &updateInterval);
        if(updateInterval < 50)
        {
            updateInterval = 50;
        }
        SuddenMotionSensorAdapter *adapter;
        FREGetContextNativeData(ctx, (void**)&adapter);
        adapter->setUpdateInterval(updateInterval);
        return NULL;
    }
    
    void contextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctions, const FRENamedFunction** functions)
    {
        //printf("contextInitializer\n");
		*numFunctions = 4;
        
		FRENamedFunction* func = (FRENamedFunction*) malloc(sizeof(FRENamedFunction) * (*numFunctions));
        
        func[0].name = (const uint8_t*) "isSupported";
		func[0].functionData = NULL;
		func[0].function = &SMS_isSupported;
        
        func[1].name = (const uint8_t*) "startListening";
		func[1].functionData = NULL;
		func[1].function = &SMS_startListening;
        
        func[2].name = (const uint8_t*) "stopListening";
		func[2].functionData = NULL;
		func[2].function = &SMS_stopListening;
        
        func[3].name = (const uint8_t*) "setRequestedUpdateInterval";
		func[3].functionData = NULL;
		func[3].function = &SMS_setRequestedUpdateInterval;
        
        
        SuddenMotionSensorAdapter *adapter = new SuddenMotionSensorAdapter();
        FRESetContextNativeData(ctx, (void *)adapter);
        (*adapter).context = ctx;
		
		*functions = func;
	}
    
	void contextFinalizer(FREContext ctx)
    {
        //printf("contextFinalizer\n");
        SuddenMotionSensorAdapter *adapter;
        FREGetContextNativeData(ctx, (void**)&adapter);
        adapter->dispose();
		return;
	}
    
    EXPORT
	void initializer(void** extData, FREContextInitializer* ctxInitializer, FREContextFinalizer* ctxFinalizer)
    {
		*ctxInitializer = &contextInitializer;
		*ctxFinalizer = &contextFinalizer;
	}
    
    EXPORT
	void finalizer(void* extData)
    {
		return;
	}
}