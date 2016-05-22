#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl8,  ultraIn,        sensorDigitalIn)
#pragma config(Sensor, dgtl9,  ultraOut,       sensorDigitalOut)
#pragma config(Sensor, dgtl11, rightButton,    sensorTouch)
#pragma config(Sensor, dgtl12, leftButton,     sensorTouch)
#pragma config(Sensor, I2C_1,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, PIDControl, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, PIDControl, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++\
																	Authors: Gloria Ngan and CJ Zhang
	This is a program to navigate a maze with the swervebot and return to the starting zone, making
	a 360 deg point turn.

Robot Model(s): Modified Squarebot

[I/O Port]          [Name]              [Type]                [Description]
Motor Port 1        rightMotor          393 Motor             Right side motor
Motor Port 10       leftMotor           393 Motor             Left side motor, Reversed
I2C_1               rightIEM            Integrated Encoder    Encoder mounted on rightMotor
I2C_2               leftIEM             Integrated Encoder    Encoted mounted on leftMotor
----------------------------------------------------------------------------------------------------*/

//NOTE: 627 ticks is one full wheel rotation.
//			Left motor is faster than the right one.
//FORMULA FOR TICKS: T = (distance/12.57)(627)

//Clear the encoders associated with the left and right motors.
void resetEncoder(){
	SensorValue[rightIEM] = 0;
	SensorValue[leftIEM] = 0;
	wait1Msec(1000);
}

//Stops robot. This method is called at the end of the others to ensure that it pauses.
void stopRobot(){
	motor[rightMotor] = 0;
	motor[leftMotor]	= 0;
	wait1Msec(1000);
}

//Code to drive the robot forwards or back in a straight line.
void drive(int x, int y, int z){		//x is for number of ticks, y is for speed, z is for auto correction
	y = -y;
	//Acceleration code(reduces probability of robot moving off from a straight line.
	for(int i = 0; i <= y; i = i + 10){
		motor[rightMotor] = i + z;		// Motor on port10 is run forward
		motor[leftMotor]  = i;		  	// Motor on port1 is run forward
		wait1Msec(200);	        		// Robot runs previous code for 100 milliseconds before moving on
	}

	//Auto-correction code that programs the robot to move in straight line.
	while (SensorValue[leftIEM] < x){
		motor[rightMotor] = y;
		motor[leftMotor] = y;
	}

	//Deceleration code increments the speed of the motors downward to ensure a smooth stop.
	for(int i = y; i >= 0; i = i - 10){
		motor[rightMotor] = i + z;		//Add z to adjust for discrepancy in motor speed.
		motor[leftMotor]  = i;
		wait1Msec(200);
	}

	//Stops the robot and resets encoders at the end of the function.
	stopRobot();
	resetEncoder();
}

//Function for a 90 deg swing turn towards the left.
void swingTurnLeft(){
	//Clears encoders to ensure the robot turns properly.
	resetEncoder();
	while (SensorValue[rightIEM] > -450){
		motor[rightMotor] = -60;
		motor[leftMotor]= 0;
	}
	stopRobot();
}

//Function for a 90 deg swing turn towards the right.
void swingTurnRight(){
	//Clears encoders to ensure the robot turns properly.
	resetEncoder();
	while (SensorValue[leftIEM] < 450){
		motor[rightMotor] = 0;
		motor[leftMotor]= -50;
	}
	stopRobot();
}

//A method to execute a 360 deg point turn.
void pointTurn(){
	resetEncoder();
	while (SensorValue[leftIEM] < 450){
		motor[rightMotor] = 50;
		motor[leftMotor]= -50;
	}
	stopRobot();
}

task main
{
	//Constant to be passed as arguments for the methods.
	int b = 40;		//Speed for driving.

	while(1==1){
		//Only runs code when button is pressed.
		if(SensorValue[rightButton] == 1){
				//Drive around first cup.
				drive(930,b,0);
				swingTurnRight();

				//Around second cup.
				drive(1070,b,1.5);
				swingTurnRight();

				//Drives across halfpoint.
				drive(1200,b,1);
				swingTurnLeft();

				//Drives to far end of the board.
				drive(650,b,-1);
				swingTurnLeft();

				//Crosses to second lane of the board.
				drive(500,b,-2);
				swingTurnLeft();

				//Drives back to start.
				drive(1500,50,-1);
				swingTurnLeft();

				//Drives into starting area and makes a 360 deg turn.
				drive(600,b,0);
				pointTurn();
		}
	}
}
