int outputA = 6;
int outputB = 7;

int counter = 0;
int aState;
int aLastState;

void setup() {
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA); 
}

void loop() {
  aState = digitalRead(outputA);
  if(aState < aLastState){

    if(digitalRead(outputB) != aState){
      counter++;
    }
    else{
      counter--;
    }
    delay(100);
    Serial.print("Position: ");
    Serial.println(counter);
    
  }
  aLastState = aState;

}
