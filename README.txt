/*
 *  SuddenMotionSensor AIR native extension
 *
 *  Copyright (c) 2012 Wouter Verweirder. All rights reserved.
 *
 *  It uses UniMotion on the native side:
 *  UniMotion - Unified Motion detection for Apple portables.
 *  Copyright (c) 2006 Lincoln Ramsay. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1 as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation Inc. 59 Temple Place, Suite 330, Boston MA 02111-1307 USA
 */

The SuddenMotionSensor class enables you to access the Sudden Motion Sensor
in portable macs in your AIR applications.

It uses a native extension to give you this functionality.
The extension id for the native extension is: be.aboutme.nativeExtensions.suddenMotionSensor.SuddenMotionSensor

You can check if the SuddenMotionSensor is supported on your mac, set the update interval and listen for accelerometer events:

if(SuddenMotionSensor.isSupported)
{
	suddenMotionSensor = new SuddenMotionSensor();
	suddenMotionSensor.setRequestedUpdateInterval(50);
	suddenMotionSensor.addEventListener(AccelerometerEvent.UPDATE, accelerometerUpdateHandler, false, 0, true);
}