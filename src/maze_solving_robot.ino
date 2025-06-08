#include <NewPing.h>
#include <Servo.h>

// Pin Definitions for Ultrasonic Sensor
#define TRIG_PIN 10
#define ECHO_PIN 9

// Maximum distance for the ultrasonic sensor
#define MAX_DISTANCE 200

// Define MAX_SPEED for PWM (motor speed range from 0 to 255)
#define MAX_SPEED 255

// Motor Control Pins for L298N (two motors)
#define MLa 7   // Left motor 1st pin
#define MLb 2   // Left motor 2nd pin
#define MRa 4   // Right motor 1st pin
#define MRb 1   // Right motor 2nd pin
#define ENA 6   // Enable pin for left motor (PWM-capable)
#define ENB 3   // Enable pin for right motor (PWM-capable)

// Servo pin
#define servoPin 11
Servo Myservo;  // Create servo object for the ultrasonic sensor

// Other variables
boolean goesForward = false;
int distance = 100;  // Variable to store the distance measured
int speedSet = 0;    // Variable to set the speed of the motors

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);  // Create an instance of the NewPing library

// Setup function
void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Attach servo
  Myservo.attach(servoPin);
  Myservo.write(115);  // Center position for the servo
  delay(800);
  
  // Read initial distance from the ultrasonic sensor
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

  Serial.println("Robot Setup Complete");
}

// Loop function
void loop() {
  int distanceR = 0;
  int distanceL = 0;
  delay(40);

  // Print distance from ultrasonic sensor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If an obstacle is detected within 8 cm
  if (distance <= 8) {
    Serial.println("Obstacle detected! Stopping and moving backward...");
    moveStop();       // Stop the robot
    delay(100);
    moveBackward();   // Move backward to avoid obstacle
    delay(300);
    moveStop();       // Stop briefly
    delay(200);

    // Look right and left to determine the best direction to turn
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    // Print the distances for right and left directions
    Serial.print("Right distance: ");
    Serial.print(distanceR);
    Serial.print(" cm, Left distance: ");
    Serial.print(distanceL);
    Serial.println(" cm");

    // If the right side has more space, turn right; otherwise, turn left
    if (distanceR >= distanceL) {
      Serial.println("Turning right...");
      turnRight();
    } else {
      Serial.println("Turning left...");
      turnLeft();
    }

    // After turning, continue moving forward
    moveForward();
  } else {
    Serial.println("No obstacle detected, moving forward...");
    moveForward();  // Move forward if no obstacle is detected
  }

  distance = readPing();  // Read distance from the ultrasonic sensor
}

// Function to look right
int lookRight() {
  Myservo.write(50);  // Position the servo to look right
  delay(500);
  int distance = readPing();
  delay(100);
  Myservo.write(115);  // Reset the servo position
  return distance;
}

// Function to look left
int lookLeft() {
  Myservo.write(170);  // Position the servo to look left
  delay(500);
  int distance = readPing();
  delay(100);
  Myservo.write(115);  // Reset the servo position
  return distance;
}

// Function to read distance from the ultrasonic sensor
int readPing() {
  delay(70);
  int cm = sonar.ping_cm();  // Get distance in cm
  if (cm == 0) {
    cm = 250;  // If no reading or out of range, set distance to 250 cm
  }
  return cm;
}

// Function to stop all motors
void moveStop() {
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println("Motors stopped");
}

// Function to move the robot forward
void moveForward() {
  if (!goesForward) {
    goesForward = true;
    
    // Move left motor forward
    digitalWrite(MLa, HIGH);   // Left motor forward
    digitalWrite(MLb, LOW);    // Left motor forward direction

    // Move right motor forward
    digitalWrite(MRa, LOW);    // Right motor forward
    digitalWrite(MRb, HIGH);   // Right motor forward direction

    // Gradually increase speed with small increments
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 1) {
      analogWrite(ENA, speedSet);  // Set left motor speed
      analogWrite(ENB, speedSet);  // Set right motor speed
      delay(5);  // Wait a little between speed changes for smooth acceleration
    }

    Serial.println("Moving forward");
  }
}

// Function to move the robot backward
void moveBackward() {
  goesForward = false;
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);  // Backward direction for left motor
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);  // Backward direction for right motor

  // Gradually increase speed
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    analogWrite(ENA, speedSet);  // Set left motor speed
    analogWrite(ENB, speedSet);  // Set right motor speed
    delay(5);
  }

  Serial.println("Moving backward");
}

// Function to turn the robot right
void turnRight() {
  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);  // Left motor moves forward
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);  // Right motor moves backward
  delay(500);
  // Do not stop after turning; move forward immediately
  Serial.println("Turned right");
}

// Function to turn the robot left
void turnLeft() {
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);  // Left motor moves backward
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);  // Right motor moves forward
  delay(500);
  // Do not stop after turning; move forward immediately
  Serial.println("Turned left");
}
