#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// Define sensor pin and type
#define DHTPIN A1           // DHT22 data pin connected to analog pin A1
#define DHTTYPE DHT22       // Sensor type: DHT22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address and size (16 columns, 2 rows)

void setup() {
  Serial.begin(9600);       // Start serial communication
  dht.begin();              // Initialize DHT sensor
  lcd.init();               // Initialize LCD
  lcd.backlight();          // Turn on LCD backlight

  // Display welcome message
  lcd.setCursor(2, 0);
  lcd.print("DHT22 Monitor");
  lcd.setCursor(1, 1);
  lcd.print("Temp & Humidity");
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(2000); // Wait 2 seconds between sensor readings

  // Read temperature (Celsius) and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // If reading fails, show error
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT22 sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    return;
  }

  // Output to Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);    // One decimal place
  lcd.print((char)223);         // Degree symbol
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity, 1);
  lcd.print(" %");
}
