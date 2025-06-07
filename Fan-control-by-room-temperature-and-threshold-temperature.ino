#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int potPin = A0;
const int fanPin = 3; // Connect the fan to this pin

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address and dimensions

void setup() {
  dht.begin();
  pinMode(fanPin, OUTPUT);
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Temp Fan Control");
  lcd.setCursor(0, 1);
  lcd.print("by Your Name");
  delay(2000);
  lcd.clear();
}

void loop() {
  int threshold = map(analogRead(potPin), 0, 1023, 20, 70); // Map potentiometer value to temperature range

  float temperature = dht.readTemperature();

  delay(1000);

  if (temperature > threshold) {
    digitalWrite(fanPin, HIGH); // Turn on the fan
  } else {
    digitalWrite(fanPin, LOW); // Turn off the fan
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Threshold: ");
  lcd.print(threshold);
  lcd.print("C");

}