int downPin = 13;
int inPin = 12;
int outPin = 11;
int upPin = 10; 

void setup() {
  pinMode(downPin,OUTPUT);
  pinMode(upPin,OUTPUT);
  pinMode(inPin,OUTPUT);
  pinMode(outPin,OUTPUT);
  digitalWrite(downPin,LOW);
  digitalWrite(upPin,LOW);
  digitalWrite(inPin,LOW);
  digitalWrite(outPin,LOW);

  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    char data = Serial.read();
    switch(data){
      case 'u':
        digitalWrite(upPin,HIGH);
        break;
      case 'd':
        digitalWrite(downPin,HIGH);
        break;
      case 'i':
        digitalWrite(inPin,HIGH);
        break;
      case 'o':
        digitalWrite(outPin,HIGH);
        break;
      case 'y':
        digitalWrite(upPin,LOW);
        break;
      case 's':
        digitalWrite(downPin,LOW);
        break;
      case 'k':
        digitalWrite(inPin,LOW);
        break;
      case 'p':
        digitalWrite(outPin,LOW);
        break;
      default:
        break;
    }
  }
}
