package be.aboutme.nativeExtensions.suddenMotionSensor
{
	import flash.desktop.NativeApplication;
	import flash.events.AccelerometerEvent;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.events.StatusEvent;
	import flash.external.ExtensionContext;
	
	/**
	 * The SuddenMotionSensor class dispatches events based on activity detected by the device's
	 * sudden motion sensor. This data represents the device's location or movement along a
	 * 3-dimensional axis. When the device moves, the sensor detects this movement and returns
	 * acceleration data. The SuddenMotionSensor class provides methods to query whether or not
	 * sudden motion sensor is supported, and also to set the rate at which acceleration events
	 * are dispatched.
	 */ 
	[Event(name="update", type="flash.events.AccelerometerEvent")]
	public class SuddenMotionSensor extends EventDispatcher
	{
		
		/**
		 * The isSupported property is set to true if the sudden motion sensor
		 * is availableon the device, otherwise it is set to false.
		 */ 
		public static function get isSupported():Boolean
		{
			var extContext:ExtensionContext = ExtensionContext.createExtensionContext("be.aboutme.nativeExtensions.suddenMotionSensor.SuddenMotionSensor", null);
			var supported:Boolean = extContext.call("isSupported");
			extContext = null;
			return supported;
		}
		
		private var extContext:ExtensionContext; 
		
		/**
		 * Creates a new SuddenMotionSensor instance
		 */ 
		public function SuddenMotionSensor()
		{
			extContext = ExtensionContext.createExtensionContext("be.aboutme.nativeExtensions.suddenMotionSensor.SuddenMotionSensor", null);
			NativeApplication.nativeApplication.addEventListener(Event.EXITING, nativeApplicationExitHandler, false, 0, true);
			extContext.addEventListener(StatusEvent.STATUS, statusHandler, false, 0, true);
			extContext.call("startListening");
		}
		
		/**
		 * The setRequestedUpdateInterval method is used to set the desired time interval for updates.
		 * The time interval is measured in milliseconds. Any change in the update interval affects all
		 * registered listeners. You can use the SuddenMotionSensor class without calling the
		 * setRequestedUpdateInterval() method.
		 */ 
		public function setRequestedUpdateInterval(interval:uint):void
		{
			extContext.call("setRequestedUpdateInterval", interval);
		}
		
		protected function nativeApplicationExitHandler(event:Event):void
		{
			extContext.call("stopListening");
			extContext = null;
		}
		
		protected function statusHandler(event:StatusEvent):void
		{
			switch(event.code)
			{
				case "update":
					var split:Array = event.level.split(";");
					dispatchEvent(new AccelerometerEvent(AccelerometerEvent.UPDATE, false, false, 0, split[0], split[1], split[2]));
					break;
			}
		}
	}
}