package
{
	import be.aboutme.nativeExtensions.suddenMotionSensor.SuddenMotionSensor;
	
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.AccelerometerEvent;
	
	[SWF(frameRate=60, width=800, height=600)]
	public class Main extends Sprite
	{
		
		private var suddenMotionSensor:SuddenMotionSensor;
		
		private var ball:Shape;
		
		public function Main()
		{
			stage.align = StageAlign.TOP_LEFT;
			stage.scaleMode = StageScaleMode.NO_SCALE;
			
			ball = new Shape();
			ball.graphics.beginFill(0xFF0000);
			ball.graphics.drawCircle(0, 0, 100);
			ball.graphics.endFill();
			addChild(ball);
			
			if(SuddenMotionSensor.isSupported)
			{
				suddenMotionSensor = new SuddenMotionSensor();
				suddenMotionSensor.setRequestedUpdateInterval(50);
				suddenMotionSensor.addEventListener(AccelerometerEvent.UPDATE, accelerometerUpdateHandler, false, 0, true);
			}
		}
		
		protected function accelerometerUpdateHandler(event:AccelerometerEvent):void
		{
			//create variable for the target position of the ball
			var targetX:Number = ball.x + event.accelerationX;
			var targetY:Number = ball.y - event.accelerationY;
			
			//make sure the target coordinates are inside the stage boundaries
			if(targetX < 0) targetX = 0;
			else if(targetX > stage.stageWidth) targetX = stage.stageWidth;
			
			if(targetY < 0) targetY = 0;
			else if(targetY > stage.stageHeight) targetY = stage.stageHeight;
			
			//add some easing to the movement
			
			ball.x += (targetX - ball.x) * .3;
			ball.y += (targetY - ball.y) * .3;
		}
	}
}