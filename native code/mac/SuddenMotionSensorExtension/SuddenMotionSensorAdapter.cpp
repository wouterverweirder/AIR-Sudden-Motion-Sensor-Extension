//
//  SuddenMotionSensorAdapter.cpp
//  SuddenMotionSensorExtension
//
//  Created by Wouter Verweirder on 12/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "SuddenMotionSensorAdapter.h"
#include "unimotion.h"

SuddenMotionSensorAdapter::SuddenMotionSensorAdapter()
{
    //printf("SuddenMotionSensorAdapter::SuddenMotionSensorAdapter\n");
    g_type = detect_sms();
    running = false;
    g_updateInterval = 100;
    //printf("SuddenMotionSensorAdapter::SuddenMotionSensorAdapter: %i\n", g_type);
}

bool SuddenMotionSensorAdapter::isSupported()
{
    //printf("SuddenMotionSensorAdapter::isSupported\n");
    //printf("g_type: %i\n", g_type);
    return (g_type > 0);
}

void SuddenMotionSensorAdapter::setUpdateInterval(int updateInterval)
{
    g_updateInterval = updateInterval;
}

void SuddenMotionSensorAdapter::start()
{
    //printf("SuddenMotionSensorAdapter::start\n");
    if(!running)
    {
        returnVal = pthread_attr_init(&attr);
        returnVal = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        
        running = true;
        
        int threadError = pthread_create(&posixThreadID, &attr, sensorThread, (void *) this);
        printf("thread create code: %i\n", threadError);
    }
}

void * SuddenMotionSensorAdapter::sensorThread(void *self)
{
    SuddenMotionSensorAdapter *adapter = (SuddenMotionSensorAdapter *) self;
    adapter->run();
    return NULL;
}

void SuddenMotionSensorAdapter::run()
{
    while(running)
    {
        //read sensor data
        char buffer [50];
        int xInt, yInt, zInt;
        read_sms_raw(g_type, &xInt, &yInt, &zInt);
        sprintf(buffer, "%i;%i;%i", xInt, yInt, zInt);
        
        const uint8_t* statusCode = (const uint8_t*) "update";
        const uint8_t* level = (const uint8_t*) buffer;
        FREDispatchStatusEventAsync(context, statusCode, level);
        usleep(1000 * g_updateInterval);
    }
}

void SuddenMotionSensorAdapter::dispose()
{
    //printf("SuddenMotionSensorAdapter::dispose\n");
    if(running)
    {
        running = false;
        int threadError = pthread_join(posixThreadID, NULL);
        printf("thread join code: %d\n", threadError);
    }
    context = NULL;
}