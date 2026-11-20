// RC Bluetooth Module Car
// Board: Arduino UNO | Bluetooth: HC-05 | Driver: L298N (assumed)

#include <SoftwareSerial.h>

// HC-05 connections (software serial, so USB serial stays free)
const int BT_RX = 10;   // Arduino pin 10 <- HC-05 TX
const int BT_TX = 11;   // Arduino pin 11 -> HC-05 RX (use a voltage divider)
SoftwareSerial bluetooth(BT_RX, BT_TX);

// L298N motor driver pins
const int IN1 = 4;      // Left motor direction pin 1
const int IN2 = 5;      // Left motor direction pin 2
const int IN3 = 6;      // Right motor direction pin 1
const int IN4 = 7;      // Right motor direction pin 2

char command;           // Stores the character received from the phone

void setup() {
  bluetooth.begin(9600);          // HC-05 default baud rate

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopCar();                      // Start with the car stopped
}

void loop() {
  if (bluetooth.available() > 0) {    // Check if data has arrived
    command = bluetooth.read();       // Read one character

    switch (command) {
      case 'F': moveForward();  break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft();     break;
      case 'R': turnRight();    break;
      case 'S': stopCar();      break;
      default:  break;                // Ignore unknown characters
    }
  }
}

// Both motors forward
void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

// Both motors backward
void moveBackward() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

// Left motor backward, right motor forward: car turns left
void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

// Left motor forward, right motor backward: car turns right
void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

// All pins LOW: both motors stop
void stopCar() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);
}
