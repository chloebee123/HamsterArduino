#include <LiquidCrystal.h>
#include <TimeLib.h>

volatile int counter = 0, miles = 0, dailyHighscore = 0;
const double pi = 3.1415926535;
const double rev = 9 * pi; // inches of distance per revolution
const int HEpin = 2, LCDrx = 0, LCDtx = 1;



void setup() {
  Serial.begin(9600);
  pinMode(HEpin, INPUT); // Hall effect sensor as input
  setTime(5, 27, 30, 2, 8, 2022); // setting time
  attachInterrupt(digitalPinToInterrupt(HEpin), boop, RISING); // Interrupt which increments counter on sensor input
}

void loop() {
  Serial.print("Total Revolutions: ");
  Serial.println(counter);
  delay(100);
}

void boop() {
  counter += 1;
  digitalWrite(HEpin, LOW);
}

void DailyReset () { // reset counter and store highscores/other data
  
}

void UpdateLCD() { // updates lcd every five seconds
  
}

void Revs2Miles(counter, rev){
  
}
