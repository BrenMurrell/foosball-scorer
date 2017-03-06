/*
  Foosball scorer
  Author: Bren Murrell
*/
int dataPinRed = 12;
int latchPinRed = 11;
int clockPinRed = 13;
int dataPinBlue = 9;
int latchPinBlue = 8;
int clockPinBlue = 10;

#define trigPinBlue 6
#define echoPinBlue 7
#define trigPinRed 4
#define echoPinRed 5

long durationBlue = 4000;
long durationRed = 4000;
bool justScored = false;
bool gameOver = false;
int scoreBlue = 0;
int scoreRed = 0;
int loopDelay = 5;
int seq[14] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};


// the setup function runs once when you press reset or power the board
void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(trigPinRed, OUTPUT);
  pinMode(echoPinRed, INPUT);
  pinMode(trigPinBlue, OUTPUT);
  pinMode(echoPinBlue, INPUT);
  pinMode(dataPinRed, OUTPUT);
  pinMode(latchPinRed, OUTPUT);
  pinMode(clockPinRed, OUTPUT);
  pinMode(dataPinBlue, OUTPUT);
  pinMode(latchPinBlue, OUTPUT);
  pinMode(clockPinBlue, OUTPUT);
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");  
  digitalWrite(latchPinRed, LOW);
  shiftOut(dataPinRed, clockPinRed, MSBFIRST, seq[scoreRed]);
  digitalWrite(latchPinRed, HIGH);
  digitalWrite(latchPinBlue, LOW);
  shiftOut(dataPinBlue, clockPinBlue, MSBFIRST, seq[scoreBlue]);
  digitalWrite(latchPinBlue, HIGH);
}

// the loop function runs over and over again forever
void loop() {
  //long duration;
  
  delay(10);
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
  
  //Serial.println(durationBlue);
  //Serial.println(durationRed);
//  Serial.println(loopDelay);
//  Serial.println("--- done ---");
  if (durationBlue < 400 || durationRed < 400) {  // This is where the LED On/Off happens
    loopDelay = 4000;
    if(justScored == false) {
      if(durationBlue < 400) {
        scoreBlue = scoreBlue + 1;
        Serial.println("--- Blue Scored! ---");
        digitalWrite(latchPinBlue, LOW);
        shiftOut(dataPinBlue, clockPinBlue, MSBFIRST, seq[scoreBlue]);
        digitalWrite(latchPinBlue, HIGH);
        
      } else {
        scoreRed = scoreRed + 1;
        Serial.println("--- Red Scored! ---");
        digitalWrite(latchPinRed, LOW);
        shiftOut(dataPinRed, clockPinRed, MSBFIRST, seq[scoreRed]);
        digitalWrite(latchPinRed, HIGH);
        
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
    loopDelay = 0;
  } 
  
  delay(loopDelay);   // wait for a second
  
}

