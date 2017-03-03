/*
  Foosball scorer
  Author: Bren Murrell
*/

#define trigPinBlue 11
#define echoPinBlue 10
#define trigPinRed 5
#define echoPinRed 6
long durationBlue = 4000;
long durationRed = 4000;
bool justScored = false;
bool gameOver = false;
int scoreBlue = 0;
int scoreRed = 0;
int loopDelay = 5;
// the setup function runs once when you press reset or power the board
void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(trigPinRed, OUTPUT);
  pinMode(echoPinRed, INPUT);
  pinMode(trigPinBlue, OUTPUT);
  pinMode(echoPinBlue, INPUT);
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
}

// the loop function runs over and over again forever
void loop() {
  //long duration;
  digitalWrite(trigPinBlue, LOW);
  
  delay(2);
  digitalWrite(trigPinBlue, HIGH);
  
  delay(10);
  digitalWrite(trigPinBlue, LOW);
  
  durationBlue = pulseIn(echoPinBlue, HIGH);
  
  digitalWrite(trigPinRed, LOW);
  delay(2);
  digitalWrite(trigPinRed, HIGH);
  delay(10);
  digitalWrite(trigPinRed, LOW);

  
  durationRed = pulseIn(echoPinRed, HIGH);
//  Serial.println(durationBlue);
//  Serial.println(durationRed);
//  Serial.println(loopDelay);
//  Serial.println("--- done ---");
  if (durationBlue < 400 || durationRed < 400) {  // This is where the LED On/Off happens
    loopDelay = 4000;
    if(justScored == false) {
      if(durationBlue < 400) {
        scoreBlue = scoreBlue + 1;
        Serial.println("--- Blue Scored! ---");
      } else {
        scoreRed = scoreRed + 1;
        Serial.println("--- Red Scored! ---");
      }
      //Serial.println("--- Blue ---");
      Serial.println(scoreBlue);
      //Serial.println("--- Red ---");
      Serial.println(scoreRed);
    } 
    justScored = true;
  }
  else {
    if(justScored == true) {
      Serial.println("--- Ball released ---");
    }
    justScored = false;
    loopDelay = 5;
  }
  

  delay(loopDelay);   // wait for a second
  
}

