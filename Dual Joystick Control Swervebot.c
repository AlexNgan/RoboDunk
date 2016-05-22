#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393HighSpeed_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

task main ()
{
	while(1 == 1)
	{
			// While upper left trigger is held, the joystick values are halved for a slower speed.
    	if(vexRT[Btn5U] == 1){
    		motor[leftMotor]  = -vexRT[Ch2]/2;   // Left Joystick Y value
      	motor[rightMotor] = -vexRT[Ch3]/2;   // Right Joystick Y value
      	}

			// If trigger isn't held, the joystick values are directly mapped to the motors.
			else {
      	motor[leftMotor]  = -vexRT[Ch2];   // Left Joystick Y value
      	motor[rightMotor] = -vexRT[Ch3];   // Right Joystick Y value

		}
	}
}