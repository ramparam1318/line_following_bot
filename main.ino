// Pin Definitions 
#define sensor0 A0  // Leftmost sensor (corner) 
#define sensor1 A1  // Left middle sensor 
#define sensor2 A2  // Center sensor 
#define sensor3 A3  // Right middle sensor 
#define sensor4 A4  // Rightmost sensor (corner) 
 
#define leftMotorForward 9  // Left motor forward pin 
#define leftMotorBackward 8 // Left motor backward pin 
#define rightMotorForward 10 // Right motor forward pin 
#define rightMotorBackward 11 // Right motor backward pin 
 
void setup() { 
  pinMode(leftMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT); 
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(rightMotorBackward, OUTPUT); 
 
  pinMode(sensor0, INPUT); 
  pinMode(sensor1, INPUT); 
  pinMode(sensor2, INPUT); 
  pinMode(sensor3, INPUT); 
  pinMode(sensor4, INPUT); 
 
  Serial.begin(9600); 
} 
 
void loop() { 
    // or for black, 1 for white 
  int s0 = digitalRead(sensor0); 
  int s1 = digitalRead(sensor1); 
  int s2 = digitalRead(sensor2); 
  int s3 = digitalRead(sensor3); 
  int s4 = digitalRead(sensor4); 
 
  int sensorStates = (s0 << 4) | (s1 << 3) | (s2 << 2) | (s3 << 1) | s4; 
 
  switch (sensorStates) { 
    case 0b00100: // only the center sensor is on black --> move forward 
      moveForward(); 
      break; 
       
    case 0b01100: // left and center sensors on black  --> slightly turn right 
    case 0b00110: 
      turnRightSlight(); 
      break; 
 
    case 0b11000: // two leftmost sensors on black --> sharp right turn 
    case 0b01000: 
      turnRight(); 
      break; 
 
    case 0b00011: // right and center sensors on black --> slightly turn left 
    case 0b00101: 
      turnLeftSlight(); 
      break; 
 
    case 0b00001: // 2 rightmost sensors on black --> sharp left turn 
    case 0b00010: 
      turnLeft(); 
      break; 
 
    case 0b00000: // all 5 sensors on black  
      moveForward(); 
      break; 
 
    case 0b11111: // all 5 sensors on white 
      stopMoving(); 
      break; 
 
    default: // for temp 
      stopMoving(); 
      break; 
  } 
 
  delay(100); 
} 
 
void moveForward() { //move forward 
  digitalWrite(leftMotorForward, HIGH); 
  digitalWrite(leftMotorBackward, LOW); 
  digitalWrite(rightMotorForward, HIGH); 
  digitalWrite(rightMotorBackward, LOW); 
  Serial.println("Moving Forward"); 
} 
 
void turnRightSlight() { // slightly turn right 
  digitalWrite(leftMotorForward, HIGH); 
  digitalWrite(leftMotorBackward, LOW); 
  digitalWrite(rightMotorForward, LOW); 
  digitalWrite(rightMotorBackward, LOW); 
  Serial.println("Slight Turn Right"); 
} 
 
void turnRight() { // sharply turn right 
  digitalWrite(leftMotorForward, HIGH); 
  digitalWrite(leftMotorBackward, LOW); 
  digitalWrite(rightMotorForward, LOW); 
  digitalWrite(rightMotorBackward, HIGH); 
  Serial.println("Sharp Turn Right"); 
} 
 
void turnLeftSlight() {  //slightly turn left 
  digitalWrite(leftMotorForward, LOW); 
  digitalWrite(leftMotorBackward, LOW); 
  digitalWrite(rightMotorForward, HIGH); 
  digitalWrite(rightMotorBackward, LOW); 
  Serial.println("Slight Turn Left"); 
} 
 
void turnLeft() {  //sharply turn left 
  digitalWrite(leftMotorForward, LOW); 
  digitalWrite(leftMotorBackward, HIGH); 
  digitalWrite(rightMotorForward, HIGH); 
  digitalWrite(rightMotorBackward, LOW); 
  Serial.println("Sharp Turn Left"); 
} 
 
void stopMoving() {  //stop moving 
  digitalWrite(leftMotorForward, LOW); 
  digitalWrite(leftMotorBackward, LOW); 
  digitalWrite(rightMotorForward, LOW); 
  digitalWrite(rightMotorBackward, LOW); 
  Serial.println("Stopping"); 
}