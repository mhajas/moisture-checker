#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "plant.h"

#define MOISTURE_SENSOR_PIN 8

const int AirValue = 564;   //you need to replace this value with Value_1
const int WaterValue = 300;  //you need to replace this value with Value_2
int counter = 0;

michal_moisture_checker::Plant myPlant1 = michal_moisture_checker::Plant(A0);

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
    Serial.begin(9600);
    pinMode(MOISTURE_SENSOR_PIN, OUTPUT);
    digitalWrite(MOISTURE_SENSOR_PIN, HIGH);
}

void loop() {
    Serial.println("---------------------------------------");
    Serial.print("Starting iteration ");
    Serial.println(counter);
    uint8_t soilmoisturepercent = myPlant1.MeasureMoistureLevel();

    Serial.println("Starting displaying data on LCD");
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.print("Vlhkost ");
    lcd.setCursor(0, 1);
    lcd.print("           ");
    lcd.setCursor(0, 1);
    lcd.print(soilmoisturepercent);
    lcd.print("%");
    Serial.println("Displaying finished");

    if (counter == 10 && soilmoisturepercent < 20) {
        Serial.println("Level is below 20% and we are in 10th iteration. Watering plant.");
        digitalWrite(MOISTURE_SENSOR_PIN, LOW);
        delay(2000);
        digitalWrite(MOISTURE_SENSOR_PIN, HIGH);
        Serial.println("Watering finished.");
    }

    if (counter == 10) {
        counter = 0;
    } else {
        counter++;
    }

    Serial.println("Delaying next loop iteration.");
    delay(2000);
}