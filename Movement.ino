#include <Servo.h>

double const DEG = PI / 180;  // used for convering radians to degrees

byte const rightWheelPin = 7;  // the number of the pin that the right wheel servo is
                               // connected to
                               
byte const leftWheelPin = 8;  // the number of the pin that the left wheel servo is
                              // connected to

int const RIGHT_WHEEL_FORWARD = 0;  // value of the right wheel servo to go forward full speed

int const RIGHT_WHEEL_BACKWARDS= 180;  // value of the right wheel servo to go barckwards full speed

int const LEFT_WHEEL_FORWARD = 180;  // value of the left wheel servo to go forward full speed

int const LEFT_WHEEL_BACKWARDS= 0;  // value of the left wheel servo to go backwards full speed

float const WHEEL_STOP = 90;  // stopping value of both left and right wheel servos

Servo rightWheel;  // servo of the right wheel

Servo leftWheel;  // servo of the left wheel

Servo cameraYaw;  // servo for rotating the camera left and right

Servo cameraPitch;  // servo for rotating the camera up and down

float speedScale;  // used to change the speed of the robot wheels. value is from 0.0 to 1.0

// Stop the right and left wheel servos
void moveStop()
{
  rightWheel.write(WHEEL_STOP);
  leftWheel.write(WHEEL_STOP);
}

// Rotate the robot in place to the left
void rotateLeft()
{
  rightWheel.write(RIGHT_WHEEL_FORWARD);
  leftWheel.write(LEFT_WHEEL_BACKWARDS);
}

// Rotate the robot in place to the right
void rotateRight()
{
  rightWheel.write(RIGHT_WHEEL_BACKWARDS);
  leftWheel.write(LEFT_WHEEL_FORWARD);
}

// Move the robot forward. arc is a value from -1.0 to 1.0 that determines
// the amount of turn to the left or right. 0 is straight forward. -1 is a sharp 
// turn left. 1 is a sharp turn right.
void moveForward(float arc)
{
  float lSpeed = WHEEL_STOP * speedScale;
  float rSpeed = WHEEL_STOP * speedScale;
  
  // if arc is 0, move the robot straight
  if(arc == 0)
  {
    rightWheel.write(WHEEL_STOP - rSpeed);
    leftWheel.write(WHEEL_STOP + lSpeed);
  }
  // if arc is positive, arc the robot's path to the right
  else if(arc > 0)
  {
    if(arc > 1)
      arc = 1;
    
    rSpeed = (float)rSpeed * arc;
    Serial.print("lSpeed="); Serial.println(lSpeed);
    Serial.print("rSpeed="); Serial.println(rSpeed);
    rightWheel.write(round(rSpeed));
    leftWheel.write(WHEEL_STOP + lSpeed);
  }
  // if arc is negative, arc the robot's path to the left
  else if(arc < 0)
  {
    if(arc < -1)
      arc = -1;
    
    lSpeed = lSpeed * arc;
    rightWheel.write(WHEEL_STOP - rSpeed);
    leftWheel.write(round(180 + lSpeed));
  } 
}

// Move the robot backwards. arc is a value from -1.0 to 1.0 that determines
// the amount of turn to the left or right. 0 is straight backwards. -1 is a sharp 
// turn left. 1 is a sharp turn right.
void moveBackwards(float arc)
{
  float lSpeed = WHEEL_STOP * speedScale;
  float rSpeed = WHEEL_STOP * speedScale;
  
  if(arc == 0)
  {
    rightWheel.write(WHEEL_STOP + rSpeed);
    leftWheel.write(WHEEL_STOP - lSpeed);
  }
  
  // if arc is positive, arc the robot's path to the right
  else if(arc > 0)
  {
    if(arc > 1)
      arc = 1;
    
    rSpeed = (float)rSpeed * arc;
    Serial.print("lSpeed="); Serial.println(lSpeed);
    Serial.print("rSpeed="); Serial.println(rSpeed);
    rightWheel.write(round(180 - rSpeed));
    leftWheel.write(WHEEL_STOP - lSpeed);
  }
  
  // if arc is negative, arc the robot's path to the left
  else if(arc < 0)
  {
    if(arc < -1)
      arc = -1;
    
    lSpeed = (float)lSpeed * arc;
    Serial.print("lSpeed="); Serial.println(lSpeed);
    Serial.print("rSpeed="); Serial.println(rSpeed);
    rightWheel.write(WHEEL_STOP + rSpeed);
    leftWheel.write(round(-lSpeed));
  } 
}
