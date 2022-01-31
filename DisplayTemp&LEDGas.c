// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"


// Digital pin 8 will be called 'pin8'
int pin8 = 8;
// Digital pin 0 will be called 'pin0'
int pin0 = 0;
// Analog pin 0 will be called 'sensor'
int sensor = A0;
// Set the initial sensorValue to 0
int sensorValue = 0;

// set the DHT Pin
#define DHTPIN 7

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  dht.begin();

  

  // Print a message to the LCD.
  lcd.print("Temp:  Humidity:");

  // Initialize the digital pin 8 as an output
  pinMode(pin8, OUTPUT);
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
}

void loop() {
  delay(500);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // read humidity
  float h = dht.readHumidity();
  //read temperature in Fahrenheit
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(f)) {
    lcd.print("ERROR");
    return;
  }

  lcd.print(f);
  lcd.setCursor(7,1);
  lcd.print(h);

  // Read the input on analog pin 0 (named 'sensor')
  sensorValue = analogRead(sensor);
  // Print out the value you read
  Serial.println(sensorValue, DEC);
  // If sensorValue is greater than 500
  if (sensorValue > 500) {
    // Activate digital output pin 8 - the LED will light up
    digitalWrite(pin8, HIGH);
    Serial.print("more than 500 ppm detected");
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
  }
  else {
    // Activate digital output pin 0 - the LED will light up
    digitalWrite(pin0, HIGH);
    Serial.print("less than 500 ppm detected");
  }

  
}
