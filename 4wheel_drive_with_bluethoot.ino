// Pin definitions
#define TRIG 2
#define ECHO 3
#define MOTOR_LEFT_FORWARD 7
#define MOTOR_LEFT_BACKWARD 8
#define MOTOR_RIGHT_FORWARD 9
#define MOTOR_RIGHT_BACKWARD 10

char command;

void setup() {

  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);

  // Initial motor stop to ensure safe startup
  stopMotor();
}

void loop() {
  // Read the distance from the ultrasonic sensor
  float distance = readUltrasonicDistance(TRIG, ECHO);

  // Check for available Bluetooth commands
  if (Serial.available() > 0) {
    command = Serial.read();
  }

  if (distance > 5 && distance < 30) {
    command = 'c';
  }

  switch (command) {
    case 'w':
      moveForward();
      break;
    case 's':
      moveBackward();
      break;
    case 'a':
      turnLeft();
      break;
    case 'b':
      turnRight();
      break;
    case 'c':
      stopMotor();
      break;
  }
}

float readUltrasonicDistance(int trigPin, int echoPin) {
  // Trigger the ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  float distance = duration / 29.1 / 2;

  return distance;
}

void moveForward() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void moveBackward() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
}

void turnRight() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void turnLeft() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void stopMotor() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}
