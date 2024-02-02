#include <Servo.h>

Servo upDownServo;                 // Servo for up and down camera movement
Servo continuousRotationServo;     // Continuous rotation servo for side-to-side base movement
int x_key = A1;
int y_key = A0;
int x_pos;
int y_pos;
int upDownPosition = 90;
int speed = 0;                     // Adjust the speed as needed
int upDownServoPin = 9;            // Pin for up and down camera movement
int continuousRotationServoPin = 11; // Pin for continuous rotation servo

void setup() {
  Serial.begin(9600);
  upDownServo.attach(upDownServoPin);
  continuousRotationServo.attach(continuousRotationServoPin);
  pinMode(x_key, INPUT);
  pinMode(y_key, INPUT);
}

void loop() {
  x_pos = analogRead(x_key);

  if (x_pos < 300) {
    speed = -150;  // Set negative speed for one direction (adjust as needed)
  } else if (x_pos > 700) {
    speed = 150;   // Set positive speed for the other direction (adjust as needed)
  } else {
    speed = 0;    // Stop the continuous rotation servo if joystick is centered
  }

  continuousRotationServo.writeMicroseconds(1500 + (6*speed));  // Adjust 1500 as needed

  y_pos = analogRead(y_key);

  if (y_pos < 300) {
    upDownPosition = constrain(upDownPosition + 1, 0, 180);
    upDownServo.write(upDownPosition);
    delay(10);
  } else if (y_pos > 700) {
    upDownPosition = constrain(upDownPosition - 1, 0, 180);
    upDownServo.write(upDownPosition);
    delay(10);
  }
}
