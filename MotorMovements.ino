int x_pos, y_pos;                   // holding (x,y) coord from bbox
int w, h;                           // holding horizontal(w) and vertical length(h)

// for wheel motors
int motor1pin1 = 2; // counter clock wise
int motor1pin2 = 3; // clock wise
int motor2pin1 = 4; // counter clock wise
int motor2pin2 = 5; // clock wise

void setup() {
  Serial.begin(9600);
  pinMode(motor1pin1, OUTPUT); // pin 1 counter clock wise
  pinMode(motor1pin2, OUTPUT); // pin 2 clock wise
  pinMode(motor2pin1, OUTPUT); // pin 1 counter clock wise
  pinMode(motor2pin2, OUTPUT); // pin 2 clock wise
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


    // left,foward 
    if(x_pos < 100 && h < 50)
    {
      //left
      digitalWrite(motor2pin2, HIGH); // clock wise 
      digitalWrite(motor1pin1, HIGH); // counter clock wise
      //foward
      digitalWrite(motor2pin2, HIGH); // clock wise 
      digitalWrite(motor1pin2, HIGH); // clock wise
      //speed
      analogWrite(10, 150);  // Set speed using PWM, motor1
      analogWrite(9, 150);  // Set speed using PWM, motor2
    }
    
    // right, foward
    else if(x_pos > 450 && h < 50)
    {
      //right
      digitalWrite(motor2pin1, HIGH); // counter clock wise 
      digitalWrite(motor1pin2, HIGH); // clock wise
      //foward
      digitalWrite(motor2pin2, HIGH); // clock wise 
      digitalWrite(motor1pin2, HIGH); // clock wise
      //speed 
      analogWrite(10, 150);  // Set speed using PWM, motor1
      analogWrite(9, 150);  // Set speed using PWM, motor2
    }

    // left turn 
    else if(x_pos < 175) 
    {
      digitalWrite(motor2pin2, HIGH); // clock wise 
      digitalWrite(motor1pin1, HIGH); // counter clock wise
      analogWrite(10, 150);  // Set speed using PWM, motor1
      analogWrite(9, 150);  // Set speed using PWM, motor2
    }
   
   // right turn 
    else if(x_pos > 300)
    {
      digitalWrite(motor2pin1, HIGH); // counter clock wise 
      digitalWrite(motor1pin2, HIGH); // clock wise
      analogWrite(10, 150);  // Set speed using PWM, motor1
      analogWrite(9, 150);  // Set speed using PWM, motor2
    }

    // foward 
    else if(h < 150)
    {
      digitalWrite(motor2pin2, HIGH); // clock wise 
      digitalWrite(motor1pin2, HIGH); // clock wise
      analogWrite(10, 150);  // Set speed using PWM, motor1
      analogWrite(9, 150);  // Set speed using PWM, motor2
    }

    // back
    else if(h > 300)
    {
      digitalWrite(motor2pin1, HIGH); // counter clock wise 
      digitalWrite(motor1pin1, HIGH); // counter clock wise
      analogWrite(10, 150);  // Set speed using PWM, motor1
      analogWrite(9, 150);  // Set speed using PWM, motor2
    }

    else
    {
      analogWrite(10, 0);  // Set speed using PWM, motor1
      analogWrite(9, 0);  // Set speed using PWM, motor2
      
      //Stop motor 1
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

      // Stop motor 2
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);
    }

  }
}




