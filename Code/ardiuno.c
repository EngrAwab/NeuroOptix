#include <Servo.h>

int motorA_IN1 = 2;
int motorA_IN2 = 3;
int motorB_IN3 = 5;
int motorB_IN4 = 4;
int motorC_IN1 = 6;
int motorC_IN2 = 7;
int motorD_IN3 = 9;
int motorD_IN4 = 8;

// Define servo pins
int servo1Pin = 10;
int servo2Pin = 11;

// Create servo objects
Servo servo1;
Servo servo2;

int angle1 = 90; // Initial angle for servo 1
int angle2 = 90; // Initial angle for servo 2

void setup() {
  pinMode(motorA_IN1, OUTPUT);
  pinMode(motorA_IN2, OUTPUT);
  pinMode(motorB_IN3, OUTPUT);
  pinMode(motorB_IN4, OUTPUT);
  pinMode(motorC_IN1, OUTPUT);
  pinMode(motorC_IN2, OUTPUT);
  pinMode(motorD_IN3, OUTPUT);
  pinMode(motorD_IN4, OUTPUT);


  // Attach servos to their respective pins
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  // Initialize serial communication
  Serial.begin(9600);

  // Set initial position for servo 1
  servo1.write(angle1);
}

void loop() {
  // Check if data is available to read from serial port
  if (Serial.available() > 0) {
    // Read the incoming byte
    char command = Serial.read();

case 'F': // Move forward
        digitalWrite(motorA_IN1, HIGH);
        digitalWrite(motorA_IN2, LOW);
        digitalWrite(motorB_IN3, LOW);
        digitalWrite(motorB_IN4, HIGH);
        digitalWrite(motorC_IN1, HIGH);
        digitalWrite(motorC_IN2, LOW);
        digitalWrite(motorD_IN3, LOW);
        digitalWrite(motorD_IN4, HIGH);
        
        break;
      case 'B': // Move backward
        digitalWrite(motorA_IN1, LOW);
        digitalWrite(motorA_IN2, HIGH);
        digitalWrite(motorB_IN3, HIGH);
        digitalWrite(motorB_IN4, LOW);
        digitalWrite(motorC_IN1, LOW);
        digitalWrite(motorC_IN2, HIGH);
        digitalWrite(motorD_IN3, HIGH);
        digitalWrite(motorD_IN4, LOW);
        break;

case 'R': // Turn RIGHT
        digitalWrite(motorA_IN1, HIGH);
        digitalWrite(motorA_IN2, LOW);
        digitalWrite(motorD_IN3, HIGH);
        digitalWrite(motorD_IN4, LOW);
        digitalWrite(motorB_IN3, LOW);
        digitalWrite(motorB_IN4, HIGH);
        digitalWrite(motorC_IN1, LOW);
        digitalWrite(motorC_IN2, HIGH);
        break;
      case 'L': // Turn right
        digitalWrite(motorA_IN1, LOW);
        digitalWrite(motorA_IN2, HIGH);
        digitalWrite(motorD_IN3, LOW);
        digitalWrite(motorD_IN4, HIGH);
        digitalWrite(motorB_IN3, HIGH);
        digitalWrite(motorB_IN4, LOW);
        digitalWrite(motorC_IN1, HIGH);
        digitalWrite(motorC_IN2, LOW);
        break;
      case 'S': // Stop
        digitalWrite(motorA_IN1, LOW);
        digitalWrite(motorA_IN2, LOW);
        digitalWrite(motorB_IN3, LOW);
        digitalWrite(motorB_IN4, LOW);
        digitalWrite(motorC_IN1, LOW);
        digitalWrite(motorC_IN2, LOW);
        digitalWrite(motorD_IN3, LOW);
        digitalWrite(motorD_IN4, LOW);
        break;


    // Perform actions based on the received command
    switch (command) {
      case '1':
    // Move servo 1 counterclockwise
    angle1 -= 45;
    if (angle1 < 0) angle1 = 0; // Ensure angle stays within valid range
    servo1.write(angle1);
    break;
case '2':
    // Move servo 1 clockwise
    angle1 += 45;
    if (angle1 > 180) angle1 = 180; // Ensure angle stays within valid range
    servo1.write(angle1);
    break;
      case '3':
        // Move servo 2 clockwise
        angle2 += 45;
        if (angle2 > 180) angle2 = 0; // Wrap around if angle exceeds 180
        servo2.write(angle2);
        Serial.print("Servo 2 angle: ");
        Serial.println(angle2);
        break;
      case '4':
        // Move servo 2 counterclockwise
        angle2 -= 45;
        if (angle2 < 0) angle2 = 180; // Wrap around if angle is less than 0
        servo2.write(angle2);
        Serial.print("Servo 2 angle: ");
        Serial.println(angle2);
        break;
      case '5':
        // Move servo 2 in the same direction
        angle2 += 45;
        if (angle2 > 180) angle2 = 0; // Wrap around if angle exceeds 360
        servo2.write(angle2);
        Serial.print("Servo 2 angle: ");
        Serial.println(angle2);
        break;
      case '6':
        // Move servo 2 to position -270 degrees
        angle2 = -270;
        servo2.write(angle2);
        Serial.print("Servo 2 angle: ");
        Serial.println(angle2);
        break;
      default:
        break;
    }
  }
}
