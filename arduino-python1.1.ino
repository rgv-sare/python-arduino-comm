#include <Servo.h>                  // needed to work with servos

Servo upDownServo;                 // Servo for up and down camera movement
Servo leftRightServo;     // Continuous rotation servo for side-to-side base movement
float upDownPosition = 80;           // initial position of upDown servo
float leftRightPos = 90;           // initial position of leftRightServo servo
int leftRightServoPin = 3; // Pin for continuous rotation servo
int upDownServoPin = 12;            // Pin for up and down camera movement
int x_pos, y_pos;                   // holding (x,y) coord from bbox
int w, h;                           // holding horizontal(w) and vertical length(h)

// loop only ran once, creates the connections we declared
void setup() {
  upDownServo.attach(upDownServoPin); // attaches servo with the passed input pin
  leftRightServo.attach(leftRightServoPin); // attaches servo with the passed input pin
  Serial.begin(9600);              // starts communication for arduino to communicate w/ USB port, 9600 is speed
  upDownServo.write(upDownPosition);
  leftRightServo.write(leftRightPos);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); // Read data until newline character
    // Parse data
    int values[4];
    int i = 0;
    char* ptr = strtok((char*)data.c_str(), ",");
    while (ptr != NULL) {
      values[i++] = atoi(ptr);
      ptr = strtok(NULL, ",");
    }
    x_pos = values[0];
    y_pos = values[1];
    w = values[2];
    h = values[3];

    // left and right movement
    if (x_pos > 350) {
      leftRightPos = constrain(leftRightPos + 1, 0, 180);
      leftRightServo.write(leftRightPos);
      delay(10);
    }
    else if (x_pos < 200) {
      leftRightPos = constrain(leftRightPos - 1, 0, 180);
      leftRightServo.write(leftRightPos);
      delay(10);
    }
    // up and down movement
    if (y_pos < 120) {
      upDownPosition = constrain(upDownPosition - 1, 0, 180);
      upDownServo.write(upDownPosition);
      delay(10);
    }

    else if (y_pos > 150) {
      upDownPosition = constrain(upDownPosition + 1, 0, 180);
      upDownServo.write(upDownPosition);
      delay(10);
    }
  }
}