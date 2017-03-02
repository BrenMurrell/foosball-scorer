/*
  Foosball scorer

*/

#define led1 13
#define led2 12
#define trigPin 11
#define echoPin 10
long duration = 0;
long distance = 0;
bool justScored = false;
bool gameOver = false;
int score = 0;
int loopDelay = 5;
// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
}

// the loop function runs over and over again forever
void loop() {
  //long duration;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ((duration/2) / 29.1 );
  if (duration < 400) {  // This is where the LED On/Off happens
    digitalWrite(led1,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(led2,LOW);
    loopDelay = 4000;
    if(justScored == false) {
      score = score + 1;
      if(score >= 10) {
        Serial.println("--- Someone just won ---"); 
        score = 10;
        gameOver = true;
      } else {
        Serial.println(score);
      }
    }
    justScored = true;
    
  }
  else {
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
    justScored = false;
    loopDelay = 5;
  }

  delay(loopDelay);   // wait for a second
  
}
