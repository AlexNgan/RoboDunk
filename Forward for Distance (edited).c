#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port1,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port10,          rightMotor,    tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                              - Forward for Distance with Encoders -                                *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to move forward for 5 rotations of the left shaft encoder.       *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*
|*                                                                                                    *|
|*    MOTORS & SENSORS:          3+
                                                                     *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor   - Port 2    rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor   - Port 3    leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital - Port 1,2  rightEncoder        VEX Shaft Encoder     Right side                        *|
|*    Digital - Port 3,4  leftEncoder         VEX Shaft Encoder     Left side                         *|
\*----------------------------------------------------------------------------------------------------*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

// 20in = ~916 ticks

//Moves robot forwards, 370 ticks.
void ignition()
{

  for(int i = 0; i < 101; i = i + 10)
  {
		motor[rightMotor] = i;		  // Motor on port10 is run forward
		motor[leftMotor]  = i;		  // Motor on port1 is run forward
		wait1Msec(100);	        				// Robot runs previous code for 100 milliseconds before moving on
	}
}

//410 ticks.
void brakes()
{
	for(int i = 100; i >= 0; i = i - 10)
	{
		motor[rightMotor] = i;		  // Motor on port10 is run forward
		motor[leftMotor]  = i;		  // Motor on port1 is run forward
		wait1Msec(100);	        				// Robot runs previous code for 200 milliseconds before moving on
	}
}
//ignition + brakes on table = ~760 ticks
//~740 on track
void drive(int x)
{
	ignition();
	while(SensorValue[rightEncoder] < 500)
	{
		motor[rightMotor] = 120;		  // Motor on port10 is run forward
		motor[leftMotor]  = 100;		  // Motor on port1 is run forward
	}
	brakes();
}

//void turn90(int x)
//{
//		for(int i = 0; i < 111; i = i + 10)
//		{
//			motor[rightMotor] = i * x;		  // Motor on port10 is run forward
//			motor[leftMotor]  = i * -x;		  // Motor on port1 is run forward
//			wait1Msec(50);	        // Robot runs previous code for 50 milliseconds before moving on
//		}
//		for(int i = 110; i >= 0; i = i - 10)
//		{
//			motor[rightMotor] = i * x;		  // Motor on port10 is run forward
//			motor[leftMotor]  = i * -x;		  // Motor on port1 is run forward
//			wait1Msec(50);	        // Robot runs previous code for 50 milliseconds before moving on
//		}
//	}

//void turn180(int x)
//{
//		for(int i = 0; i < 111; i = i + 10)
//		{
//			motor[rightMotor] = i * x;		  // Motor on port10 is run forward
//			motor[leftMotor]  = i * -x;		  // Motor on port1 is run forward
//			wait1Msec(100);	        // Robot runs previous code for 50 milliseconds before moving on
//		}
//		for(int i = 110; i >= 0; i = i - 10)
//		{
//			motor[rightMotor] = i * x;		  // Motor on port10 is run forward
//			motor[leftMotor]  = i * -x;		  // Motor on port1 is run forward
//			wait1Msec(100);	        // Robot runs previous code for 50 milliseconds before moving on
//		}
//	}

void turnS(int x)
{
	while (SensorValue[rightEncoder]< 3500)
	{
		motor[rightMotor] = -31;
	}
}

task main()
{
	  wait1Msec(2000);  // 2 Second Delay

	  // Clear Encoders
	  SensorValue[rightEncoder] = 0;
	  SensorValue[leftEncoder] = 0;

		//drive(1);

}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
