#define wireFeedDirPin    6
#define wireFeedSpeedPin  7
#define stepper1EnablePin 33
#define stepper1DirPin    29
#define stepper1PulPin    25
#define stepper2EnablePin 49
#define stepper2DirPin    45
#define stepper2PulPin    41
#define relay1Pin         30
#define relay2Pin         26
#define relay3Pin         22
#define sensorPin         A13

bool relay1 = false;
bool relay2 = false;
bool relay3 = false;

void setup() {
  Serial.begin(9600);
  pinMode(wireFeedDirPin, OUTPUT);
  pinMode(wireFeedSpeedPin, OUTPUT);
  pinMode(stepper1EnablePin, OUTPUT);
  pinMode(stepper1DirPin, OUTPUT);
  pinMode(stepper1PulPin, OUTPUT);
  pinMode(stepper2EnablePin, OUTPUT);
  pinMode(stepper2DirPin, OUTPUT);
  pinMode(stepper2PulPin, OUTPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(stepper1EnablePin, LOW);
  digitalWrite(stepper2EnablePin, LOW);  
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);
  digitalWrite(relay3Pin, LOW);
}

void loop() {
  if(Serial.available() > 0){
    char command = Serial.read();
    switch(command){
      case 'c':
        cutWireBallScrew(true);
        break;
      case 'v':
        cutWireBallScrew(false);
        break;
      case 'j':
        cutWirePneumatic(true);
        break;
      case 'n':
        cutWirePneumatic(false);
        break; 
      case 'f':
        runForward();
        delay(500);
        stopFeeder();
        break;
      case 'b':
        runBackward();
        delay(500);
        stopFeeder();
        break;
      case 's':
        stopFeeder();
        break;
      case 'q':
        oneRotation1();
        break;
      case 'w':
        oneRotation2();
        break;
      case 'z':
        fourRotation1and2DOWN();
        break;
      case 'y':
        fourRotation1and2UP();
        break;
      case 'm':
        readSensor();
        break;
      case '1':
        if(relay1 == false){
          digitalWrite(relay1Pin, HIGH);
          //Serial.println("Relay 1 ON"); 
        }
        else{
          digitalWrite(relay1Pin, LOW);
          //Serial.println("Relay 1 OFF");
        }
        relay1 = !relay1;
        delay(1000);
        break;
      case '2':
        if(relay2 == false){
          digitalWrite(relay2Pin, HIGH);
          //Serial.println("Relay 2 ON"); 
        }
        else{
          digitalWrite(relay2Pin, LOW);
          //Serial.println("Relay 2 OFF");
        }
        delay(500);
        relay2 = !relay2;
        break; 
      case '3':
        if(relay3 == false){
          digitalWrite(relay3Pin, HIGH);
          //Serial.println("Relay 3 ON"); 
        }
        else{
          digitalWrite(relay3Pin, LOW);
          //Serial.println("Relay 3 OFF");
        }
        delay(500);
        relay3 = !relay3;
        break;
      default:
        stopFeeder();
        break;
    }
  }
}

void runForward(){
  analogWrite(wireFeedSpeedPin, 25);
  digitalWrite(wireFeedDirPin, LOW);
  //Serial.println("Wire Feeder Moving Forward");
  return;
}

void runBackward(){
  analogWrite(wireFeedSpeedPin, 25);
  digitalWrite(wireFeedDirPin, HIGH);
  //Serial.println("Wire Feeder Moving Backward");
  return;
}

void stopFeeder(){
  analogWrite(wireFeedSpeedPin, 0);
  digitalWrite(wireFeedDirPin, LOW);
  //Serial.println("Stopping Wire Feeder");
  return;
}

void oneRotation1(){
  digitalWrite(stepper1DirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepper1PulPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepper1PulPin,LOW); 
    delayMicroseconds(500); 
  }
  //Serial.println("Moving 1 rotation for stepper 1");
  return;
}

void oneRotation2(){
  digitalWrite(stepper2DirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepper2PulPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepper2PulPin,LOW); 
    delayMicroseconds(500); 
  }
  //Serial.println("Moving 1 rotation for stepper 2");
  return;
}

void fourRotation1and2DOWN(){
  digitalWrite(stepper1DirPin,HIGH);
  digitalWrite(stepper2DirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 2*200; x++) {
    digitalWrite(stepper2PulPin,HIGH); 
    delayMicroseconds(300); 
    digitalWrite(stepper2PulPin,LOW); 
    delayMicroseconds(300); 
        digitalWrite(stepper1PulPin,HIGH); 
    delayMicroseconds(300); 
    digitalWrite(stepper1PulPin,LOW); 
    delayMicroseconds(300); 
  }
  //Serial.println("Moving 4 rotations for stepper 1 and 2 Down");
  return;  
}

void fourRotation1and2UP(){
  digitalWrite(stepper1DirPin,LOW);
  digitalWrite(stepper2DirPin,LOW); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 2*200; x++) {
    digitalWrite(stepper2PulPin,HIGH); 
    delayMicroseconds(300); 
    digitalWrite(stepper2PulPin,LOW); 
    delayMicroseconds(300); 
        digitalWrite(stepper1PulPin,HIGH); 
    delayMicroseconds(300); 
    digitalWrite(stepper1PulPin,LOW); 
    delayMicroseconds(300); 
  }
  //Serial.println("Moving 4 rotations for stepper 1 and 2 UP");
  return;  
}

void readSensor(){
  int haha = analogRead(sensorPin);
  double val = map(haha,340,388,8750,7250);
  /*Serial.print("Sensor value = ");
  Serial.println(haha);
  Serial.print("Measured value = ");
  Serial.print(val/1000);
  Serial.println(" (in)");*/
  //Serial.print("Wire Length = ");
  Serial.print("l = ");
  Serial.println(7.4-val/1000);
  //Serial.println(" (in)");
  return;
}

void cutWireBallScrew(bool feedWire){
  unsigned long t1 = millis();
  fourRotation1and2DOWN();
  fourRotation1and2DOWN();
  digitalWrite(relay2Pin, HIGH);
  //Serial.println("Relay 2 ON"); 
  delay(500);
  digitalWrite(relay3Pin, HIGH);
  //Serial.println("Relay 3 ON"); 
  delay(500);
  readSensor();
  digitalWrite(relay3Pin, LOW);
  //Serial.println("Relay 3 OFF");
  delay(500);
  digitalWrite(relay2Pin, LOW);
  //Serial.println("Relay 2 OFF");
  delay(500);
  if(feedWire){
      runForward();
  }
  fourRotation1and2UP();
  if(feedWire){
     stopFeeder(); 
  }
  fourRotation1and2UP();
  Serial.print("t = ");
  Serial.println((millis()-t1)/1000);
  return;
}

void cutWirePneumatic(bool feedWire){
  digitalWrite(relay1Pin, HIGH);
  delay(500);
  digitalWrite(relay2Pin, HIGH);
  //Serial.println("Relay 2 ON"); 
  delay(500);
  digitalWrite(relay3Pin, HIGH);
  //Serial.println("Relay 3 ON"); 
  delay(500);
  readSensor();
  digitalWrite(relay3Pin, LOW);
  //Serial.println("Relay 3 OFF");
  delay(500);
  digitalWrite(relay2Pin, LOW);
  //Serial.println("Relay 2 OFF");
  delay(500);
  if(feedWire){
     runForward();
     delay(500);
     stopFeeder();
  }
  digitalWrite(relay1Pin, LOW);
  delay(500);
  return;
}
