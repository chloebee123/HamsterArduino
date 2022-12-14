/*
 * Chloe Belletti and Slade Brooks
 * itschloebelletti@gmail.com - spbrooks4@gmail.com
 * 4 da hamster
 */

#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <EEPROM.h>

// initializing counter 
volatile int counter = 0;

// initializing scores
float dailyMiles = 0;
float Highscore = 0;
float totalMiles = 0;
float tempMiles = 0;

// setup LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

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

  // begin serial and LCD
  Serial.begin(9600);
  //lcd.begin(16, 2);
  //lcd.backlight();
  
  // Hall effect sensor as input
  pinMode(HEpin, INPUT); 
  
  setTime(EEPROM.read(3), 0, 0, 2, 8, 2022); // setting time
  
  // Interrupt which increments counter on sensor input
  attachInterrupt(digitalPinToInterrupt(HEpin), boop, RISING); 
}

void loop() {
  UpdateCount();
  Serial.print(counter);
  // check if wheel has moved
  if (dailyMiles > tempMiles) {
    tempMiles = 0;
    // LCD displaying
    //lcd.backlight();
    lcd.display();
    UpdateCount();
    lcd.print("High Score:\n");
    lcd.print(Highscore);
    delay(5000);
    lcd.clear();
    UpdateCount();
    lcd.print("Total Miles:\n");
    lcd.print(totalMiles);
    delay(5000);
    lcd.clear();
    UpdateCount();
    lcd.print("Miles Today:\n");
    lcd.print(dailyMiles);
    delay(5000);
    counter = 0;
    //lcd.backlight();
  }
  
  // reset daily stuff every 24hrs
  if (hour() == 23) 
    DailyReset();   
  }

void boop() {
  counter += 1;
  digitalWrite(HEpin, LOW);
}

void DailyReset () { // reset counter and store highscores/other data
  // saving Highscore val:
  if (dailyMiles > Highscore)
    Highscore = dailyMiles;
  
  EEPROM.write(2, Highscore);

  // saving total Miles
  EEPROM.write(1, totalMiles);

  // resetting others
  counter = 0;
  dailyMiles = 0;
}

/*void UpdateLCD() { // updates  and displays lcd 
  // slade
}*/

void UpdateCount() { // updates daily / total vals to system and resets tmp and counter
  tempMiles = dailyMiles;
  dailyMiles = dailyMiles + (counter * rev / 63360);
  totalMiles = totalMiles + (counter * rev / 63360);
  //counter = 0;
  
  // saving dailyMiles val
  EEPROM.write(0, dailyMiles);

  // saving totalMiles
  EEPROM.write(1, totalMiles);

  // saving time
  EEPROM.write(3, hour());
  
}
