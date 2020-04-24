#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#define DHTPIN 2     // Digital pin connected to the DHT sensor 

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

int sensor_pin = A0;
float output_value;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);
  dht.begin();
  lcd.print("Sumit Shrivastava");
  lcd.setCursor(0, 1);
  lcd.print("Temp & Humidity");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(3000);
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    lcd.print("ERROR:Unable to");
    lcd.setCursor(0,1);
    lcd.print("read frm Sensor!");
    return;
  }

  float hi = dht.computeHeatIndex(t - 1, h - 3, false);

  output_value = analogRead(sensor_pin);
  output_value = map(output_value, 0, 310, 0, 100);
  
  Serial.print("Temp:");
  Serial.print(t);
  Serial.print("˚C Humi:");
  Serial.print(h);
  Serial.print("% Heat Index:");
  Serial.print(hi);
  Serial.print("˚C Moisture: ");
  Serial.print(output_value);
  Serial.println("%");
  
  
  lcd.clear();
  lcd.print("Temperat:");
  lcd.print(t - 1);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.print(h - 3);
  lcd.print("%");
  lcd.setCursor(0,1);

  delay(3000);

  lcd.clear();
  lcd.print("H. Index:");
  lcd.print(hi);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Moisture:");
  lcd.print(output_value);
  lcd.print("%");
  
}
