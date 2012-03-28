//
//  SuddenMotionSensorAdapter.h
//  SuddenMotionSensorExtension
//
//  Created by Wouter Verweirder on 12/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SuddenMotionSensorExtension_SuddenMotionSensorAdapter_h
#define SuddenMotionSensorExtension_SuddenMotionSensorAdapter_h

#include <iostream>
#include <Adobe AIR/Adobe AIR.h>

enum sms_mode
{
    raw = 0,
    normal = 1,
    real = 2
};

class SuddenMotionSensorAdapter
{
    static void     *sensorThread(void *ptr);
public:
    SuddenMotionSensorAdapter();
    
    bool            isSupported();
    void            start();
    void            run();
    void            dispose();
    void            setUpdateInterval(int updateInterval);
    
    FREContext      context;
    
    
    pthread_attr_t  attr;
    pthread_t       posixThreadID;
    int             returnVal;
    bool            running;
private:
    int             g_type;
    int             g_updateInterval;
};

#endif
