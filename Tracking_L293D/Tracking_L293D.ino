

// load lib AFMotor
#include <AFMotor.h>

#define MOTOR_SPEED 255  // values between 0 (min) and 255 (max)
#define SENSOR_SENSITIVITY 400  // below this value the sensor has not touched the line  
#define SENSOR_LEFT 19  // left sensor A0
#define SENSOR_RIGHT 14   // right sensor A5
#define MOTOR_LEFT 4
#define MOTOR_RIGHT 1

int sensorValueRight = 0; // variable to store the value coming from the sensor
int sensorValueLeft = 0;

// Define motor ports
AF_DCMotor motorRight(1); 
AF_DCMotor motorLeft(4); 


enum directions { forward = 1, backward, left, right, stopped };

int moveMotor(){
  switch(moveDirection())
  {
    case forward:
          // clockwise direction
          motorLeft.run(FORWARD); 
          // counterclockwise direction
          motorRight.run(BACKWARD); 
      break;
    case backward:
          motorLeft.run(BACKWARD); 
          motorRight.run(FORWARD);  
      break;
    case right:
          motorLeft.run(FORWARD); 
          motorRight.run(FORWARD);
          
          motorLeft.run(FORWARD); 
          motorRight.run(RELEASE);
      break;
    case left:
          motorLeft.run(BACKWARD); 
          motorRight.run(BACKWARD);
          motorLeft.run(RELEASE); 
          motorRight.run(BACKWARD);
      break;
    case stopped:
          motorRight.run(RELEASE); 
          motorLeft.run(RELEASE); 
      break;         
  }
}

int moveDirection(){
  sensorValueRight = analogRead (SENSOR_LEFT);
  sensorValueLeft = analogRead (SENSOR_RIGHT);

  Serial.println("Right:");
  Serial.println(sensorValueRight, DEC);

  Serial.println("Left:");
  Serial.println(sensorValueLeft, DEC);

  if(sensorValueRight < SENSOR_SENSITIVITY && sensorValueLeft < SENSOR_SENSITIVITY){  // not touch line
     return forward; 
  }else if(sensorValueRight > SENSOR_SENSITIVITY && sensorValueLeft > SENSOR_SENSITIVITY){  // both sensor touch line (must stop)
     return stopped; 
  }else if(sensorValueRight < SENSOR_SENSITIVITY){  // Turn right (left sensor triggered)
     return right; 
  } 

  // Turn left
  return left; 
}
 
void setup ()
{
  // Define speed for both motor dc
  motorRight.setSpeed(MOTOR_SPEED); 
  motorLeft.setSpeed(MOTOR_SPEED); 

 // Set sensor pin as input 
 pinMode(SENSOR_LEFT, INPUT);
 pinMode(SENSOR_RIGHT, INPUT);
 Serial.begin (9600);
}
 
void loop ()
{
 moveMotor();
 delay(50);
 motorRight.run(RELEASE); 
 motorLeft.run(RELEASE); 
 delay(50);
}
