#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(Sensor, in1,    Right,          sensorLineFollower)
#pragma config(Sensor, in2,    Middle,         sensorLineFollower)
#pragma config(Sensor, in3,    Left,           sensorLineFollower)
#pragma config(Sensor, dgtl1,  Encoder,        sensorQuadEncoder)
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           armMotor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           liftMotor1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftMotor2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armMotor1,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           liftMotor3,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           liftMotor4,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................
int threshold = 55;

//lift arm slightly
	motor[liftMotor1] = -60;
	motor[liftMotor2] = -60;
	motor[liftMotor3] = -60;
	motor[liftMotor4] = -60;
	wait1Msec(500);
	motor[liftMotor1] = 0;
	motor[liftMotor2] = 0;
	motor[liftMotor3] = 0;
	motor[liftMotor4] = 0;

	motor[armMotor] = -60;
	motor[armMotor1] = -60;
	wait1Msec(500);
	motor[armMotor] = 0;
	motor[armMotor1] = 0;

	while(SensorValue(Middle) > 40)
	{
		motor[leftMotor] = 120;
   	motor[rightMotor] = 120;


  }
  //while(encoderCount < 500){
  // RIGHT sensor sees dark:
    if(SensorValue(Right) < threshold)
    {
      // counter-steer right:
      motor[leftMotor]  = 63;
      motor[rightMotor] = 0;
    }
    // CENTER sensor sees dark:
    if(SensorValue(Middle) < threshold)
    {
      // go straight
      motor[leftMotor]  = 63;
      motor[rightMotor] = 63;
    }
    // LEFT sensor sees dark:
    if(SensorValue(Left) < threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = 0;
      motor[rightMotor] = 63;
    }
//} end encoder count down
  // Remove this function call once you have "real" code.
  //AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  // User control code here, inside the loop
/*
  while (true)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // Remove this function call once you have "real" code.
    //UserControlCodePlaceholderForTesting();
  }
  */

int threshold = 5;
int threshold2 = 100;

float speedMod = 1;

  while(true)
  {
  clearLCDLine(0);                    // Clear line 1 (0) of the LCD
  clearLCDLine(1);                    // Clear line 2 (1) of the LCD
  displayLCDPos(0,0);                 // Set the LCD cursor to Line 'l' and Index 'i'
  string value;
  sprintf(value,"%1.2f%c",(sensorValue(Encoder)));
  displayNextLCDString(value);   // Display "Hello from"

  bLCDBacklight = true;               // Turn on LCD Backlight


    //Driving Motor Control
    /*motor[leftMotor] = vexRTCh3] / 2;//old direct drive
    motor[rightMotor] = vexRT[Ch2] / 2;*/

    if(vexRT[Btn6U])
    {
    	speedMod = 0.5;
    }
    else
    {
    	speedMod = 1;
    }
    if(vexRT[Btn6D])
    {
    	if (abs(vexRT[Ch3])>=abs(vexRT[Ch2]))
    	{
    		motor[leftMotor] = speedMod * vexRT[Ch3];
    		motor[rightMotor] = speedMod * vexRT[Ch3];
    	}
    	else
    	{
    		motor[leftMotor] = speedMod * vexRT[Ch2];
    		motor[rightMotor] = speedMod * vexRT[Ch2];
    	}
  }
  else
  {

     if(abs(vexRT[Ch3]) < threshold)         // If the left joystick is greater than or less than the threshold:
    {
      motor[leftMotor]  = 3*speedMod*(vexRT[Ch3]);   // Left Joystick Y value / 2.
    }
    else if (abs(vexRT[Ch3])< threshold2)
    {
        motor[leftMotor] = speedMod*((vexRT[Ch3])/3+40/3*(vexRT[Ch3])/abs(vexRT[Ch3]));
    }
    else
    {
        motor[leftMotor]  = speedMod*((vexRT[Ch3])*80.166/27 - (249+2/3)*(vexRT[Ch3])/abs(vexRT[Ch3]));
    }


    if(abs(vexRT[Ch2]) < threshold)         // If the right joystick is greater than or less than the threshold:
    {
      motor[rightMotor] = 3*speedMod*(vexRT[Ch2]);   // Right Joystick Y value / 2.
    }
     else if (abs(vexRT[Ch2])< threshold2)
    {
        motor[rightMotor] = speedMod*((vexRT[Ch2])/3+40/3*(vexRT[Ch2])/abs(vexRT[Ch2]));
    }
    else
    {
        motor[rightMotor] = speedMod*((vexRT[Ch2])*80.166/27 - (249+2/3)*(vexRT[Ch2])/abs(vexRT[Ch2]));
    }


    //Arm Control
    if(vexRT[Btn5U] == 1)
    {
      motor[armMotor] = 127;
      motor[armMotor1] = 127;
    }
    else if(vexRT[Btn5D] == 1)
    {
      motor[armMotor] = -127;
      motor[armMotor1] = -127;
    }
    else
    {
    	motor[armMotor] = 0;
      motor[armMotor1] = 0;
    }
    //lift control
   if(vexRT[Btn8D] == 1)
    {
      motor[liftMotor4] = 127;
      motor[liftMotor1] = 127;
      motor[liftMotor2] = 127;
      motor[liftMotor3] = 127;
    }
    else if(vexRT[Btn8U] == 1)
    {
      motor[liftMotor4] = -127;
      motor[liftMotor1] = -127;
      motor[liftMotor2] = -127;
      motor[liftMotor3] = -127;
    }
    else
    {
    	motor[liftMotor4] = 0;
      motor[liftMotor1] = 0;
      motor[liftMotor2] = 0;
      motor[liftMotor3] = 0;
      // if lift encoder > 240, set to 40 in order to hold position
    }
  }
  }
}