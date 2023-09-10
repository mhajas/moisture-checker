#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "plant.h"

const int AirValue = 564;   //you need to replace this value with Value_1
const int WaterValue = 300;  //you need to replace this value with Value_2
uint64_t timestamp = 0;
bool backlight = false;

michal_moisture_checker::Plant myPlant1 = michal_moisture_checker::Plant(A1, PIN6, &timestamp);
michal_moisture_checker::Plant myPlant2 = michal_moisture_checker::Plant(A0, PIN7, &timestamp);

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
    Serial.begin(9600);
    Serial.println("Starting setup");

    Serial.println("Setting up PINS - started");
    pinMode(PIN7, OUTPUT);
    pinMode(PIN6, OUTPUT);
    digitalWrite(PIN7, HIGH);    
    digitalWrite(PIN6, HIGH);    
    Serial.println("Setting up PINS - finished");
    

    // Init LED
    Serial.println("Setting up LED - started");
    lcd.init();
    Serial.println("Setting up LED - finished");


    // Serial.println("Setting up LED interrupt - started");

    // pinMode(PIN2, INPUT);
    // attachInterrupt(digitalPinToInterrupt(PIN2), enableBacklight, RISING);
    // Serial.println("Setting up LED interrupt - finished");


}

void loop() {
    Serial.println("---------------------------------------");
    Serial.print("Starting iteration at ");
    Serial.println((unsigned int) timestamp);
    myPlant1.MeasureMoistureLevel();
    myPlant2.MeasureMoistureLevel();

    int lightLevel = analogRead(A2);
    Serial.print("Light level: ");
    Serial.println(lightLevel);

    lcd.setBacklight(backlight);
    lcd.clear();

    // Plant 1
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(myPlant1.GetWaterLevel());
    lcd.print("% ");
    lcd.print((long) myPlant1.GetWateringCounter());
    lcd.print("x ");
    lcd.print(lightLevel);
    lcd.print("l");
    

    // Plant 2
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(myPlant2.GetWaterLevel());
    lcd.print("% ");
    lcd.print((long) myPlant2.GetWateringCounter());
    lcd.print("x");

    Serial.println("Displaying finished");

    myPlant1.WaterPlantIfNeeded();
    myPlant2.WaterPlantIfNeeded();

    Serial.println("Delaying next loop iteration.");
    delay(1000);
    timestamp++;
}