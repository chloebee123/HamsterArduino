#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <EEPROM.h>

// initializing counter 
volatile int counter = 0;

// initializing scores
float dailyMiles = 0;
float Highscore = 0;
float totalMiles = 0;


const float pi = 3.1415926535;
const float rev = 9 * pi; // inches of distance per revolution

// initializing pins
const int HEpin = 2, LCDrx = 0, LCDtx = 1;


void setup() {
  // getting dailyMiles data stored in R0
  dailyMiles = EEPROM.read(0);
  // getting totalMiles data stored in R1
  totalMiles = EEPROM.read(1);
  // getting highscore data stored in R2
  Highscore = EEPROM.read(2);
  
  Serial.begin(9600);
  
  // Hall effect sensor as input
  pinMode(HEpin, INPUT); 
  
  setTime(5, 27, 30, 2, 8, 2022); // setting time
  
  // Interrupt which increments counter on sensor input
  attachInterrupt(digitalPinToInterrupt(HEpin), boop, RISING); 
}

void loop() {
  Serial.print("Daily Miles: ");
  Serial.println(dailyMiles);
  Serial.print("Counter: ");
  Serial.println(counter);
  delay(1000);
  UpdateCount();
}

void boop() {
  counter += 1;
  digitalWrite(HEpin, LOW);
}

void DailyReset () { // reset counter and store highscores/other data
  // saving Highscore val:
  if (dailyMiles > Highscore) {
    Highscore = dailyMiles;
  }
  EEPROM.write(2, Highscore);

  // saving total Miles
  EEPROM.write(1, totalMiles);

  // resetting others
  counter = 0;
  dailyMiles = 0;
  
}

void UpdateLCD() { // updates lcd 
  // slade
}

void UpdateCount() { // updates daily / total vals to system and resets tmp and counter
  dailyMiles = dailyMiles + (counter * rev  );//63360);
  totalMiles = totalMiles + (counter * rev / 63360);
  counter = 0;
  
  // saving dailyMiles val
  EEPROM.write(0, dailyMiles);

  // update totalMiles
  EEPROM.write(1, totalMiles);
  
}
