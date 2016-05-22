#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    lineFollowerRight, sensorLineFollower)
#pragma config(Sensor, in2,    lineFollowerMid, sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerLeft, sensorLineFollower)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_inch)
#pragma config(Sensor, dgtl10, rightButton,    sensorTouch)
#pragma config(Sensor, dgtl11, leftButton,     sensorTouch)
#pragma config(Sensor, I2C_1,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, PIDControl, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, PIDControl, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++++++++++\
															 		  SwerveBot: Minefield Traversal
																 	Authors: Gloria Ngan and CJ Zhang

		Using an array of three infrared sensors mounted at the front of the robot, the Swervebot detects and
		follows guidelines around obstacles (cups). While following a line, the robot is able to determine if
		the line ends, meaning that it is about to fall off the course, and back up before this occurs.

																	 Robot Model: Modified Swervebot

	[I/O Port]          [Name]              [Type]                [Description]
	Motor Port 1        rightMotor          393 Motor             Right side motor
	Motor Port 10       leftMotor           393 Motor             Left side motor, Reversed
	I2C_1               rightIEM            Integrated Encoder    Encoder mounted on rightMotor
	I2C_2               leftIEM             Integrated Encoder    Encoder mounted on leftMotor
	Digital Port 8,9    sonar               Sonar Sensor          Sonar sensor mounted on the front.
-------------------------------------------------------------------------------------------------------------*/

//Method to completely stop the motors. This is called in other methods to pause the robot.
void stopRobot(){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

//Resets the encoders integrated into each motor.
void clearEncoders(){
	SensorValue[rightIEM] = 0;
	SensorValue[leftIEM] = 0;
	wait1Msec(1000);						//Pauses robot for one second.
}

//Function to execute a point turn to the right. The number of ticks needed are passed in the parameters.
void turnRight(int x){
	clearEncoders();
	while(SensorValue[leftIEM] < x){
			motor[leftMotor] = -40;
			motor[rightMotor] = 40;
	}
	stopRobot();
}

//Function to execute a point turn to the left. The number of ticks needed are passed in the parameters.
void turnLeft(int x){
	clearEncoders();
	while(-SensorValue[rightIEM] < x){
			motor[leftMotor] = 40;
			motor[rightMotor] = -40;
	}
	stopRobot();
}

//Function to drive. The number of ticks needed are passed in the parameters.
void drive(int x, int y){		//If y is pos 1, then robot drives forwards.
	clearEncoders();
	while((-SensorValue[rightIEM]* y) < x){
			motor[leftMotor] = -60 * y;
			motor[rightMotor] = -60 * y;
	}
	stopRobot();
}

//Drives forwards until a black line is detected.
void senseDrive(){
	while(SensorValue[lineFollowerRight] < 2700){
		motor[leftMotor] = -40;
		motor[rightMotor] = -40;
  }
  stopRobot();
}

//Function to follow line.
void lineFollow(){
while(1==1){
	// If a sensor other than the middle one sees dark, it means that
	// the robot is not aligned with the line. It must turn based on
	// which sensor detects the dark to realign.

	while(SensorValue[lineFollowerMid] < 2900){
	 // MID sensor sees dark:
   if(SensorValue[lineFollowerMid] > 2000){
     drive(20,1);
   }
   // RIGHT sensor sees dark:
   if(SensorValue[lineFollowerRight] > 2000){
     turnRight(20);
   }
   // LEFT sensor sees dark:
   if(SensorValue[lineFollowerLeft] > 2000){
     turnLeft(25);
   }
 }
 	stopRobot();
}
}

//--------------------------------------------------| MAIN |--------------------------------------------------

task main(){
	while(1==1){
		if(SensorValue[rightButton] == 1){
			////Drives up to first curve and aligns with it.
		 // senseDrive();
			//turnRight(100);

			//lineFollow();	//Follow curve around first mine.
			//drive(150,-1); //Backs up once edge has been detected.
			//turnRight(100); //90 deg turn.
			//drive(500,1);
			//turnRight(280);
			//drive(1000,1); //Drives across end of board.
			//turnRight(280);
			//senseDrive();

			//lineFollow();	//Follow curve around second line.
			//drive(110,-1); //Backs up once edge has been detected.
			//turnRight(100);
			//drive(500,1); //Drives to the endpoint.

		lineFollow();
		}
	}
}
