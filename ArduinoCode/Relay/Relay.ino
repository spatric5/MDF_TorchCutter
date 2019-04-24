#define relayPin 7

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

bool relayOn = false;

void loop() {
  if(Serial.available() > 0){
    char command = Serial.read();
    switch(command){
      case 'r':
        if(relayOn == true){
          digitalWrite(relayPin, HIGH);
          Serial.println("Relay ON");
        }
        else{
          digitalWrite(relayPin, LOW);
          Serial.println("Relay OFF");
        }
        relayOn = !relayOn;
      default:
        break;
    }
  }
}
