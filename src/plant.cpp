#include "plant.h"
#include "constants.h"

using namespace michal_moisture_checker;

bool michal_moisture_checker::Plant::ShouldWater()
{
    uint64_t timeSinceLastWatered = *m_timestamp - m_last_watering_timestamp;
    bool timeSinceWateredOk = timeSinceLastWatered > kPauseBetweenWatering;
    Serial.print("Time since last watered: ");
    Serial.print((unsigned int) timeSinceLastWatered);
    Serial.print(" timeSinceWateredOk: ");
    Serial.print(timeSinceWateredOk);

    int lightLevel = analogRead(A2);
    bool lightLevelOk = lightLevel < 20;
    Serial.print(" Light level: ");
    Serial.print(lightLevel);
    Serial.print(" lightLevelOk: ");
    Serial.print(lightLevelOk);
    
    int measurementsSum = 0;
    for (const int item : m_last_measurements) {
        measurementsSum += item;
    }   
    int measurementAverage = measurementsSum / m_last_measurements.size();
    bool wateringLevelOk = measurementAverage < 60;
    Serial.print(" Watering level average: ");
    Serial.print(measurementAverage);
    Serial.print(" wateringLevelOk: ");
    Serial.println(wateringLevelOk);

    return timeSinceWateredOk && lightLevelOk && wateringLevelOk;
}

void Plant::MeasureMoistureLevel()
{
    Serial.print("Started reading for plant ");
    Serial.print((unsigned int) *m_timestamp);
    Serial.print(": ");

    int soilMoistureValue = analogRead(m_moisture_sensor_input);
    Serial.println(soilMoistureValue);

    int soilMoisturePercent = map(soilMoistureValue, kSensorAirValue, KSensorWaterValue, 0, 100);

    Serial.print("Resulting percentage: ");
    if (soilMoisturePercent >= 100) {
        soilMoisturePercent = 100;
        Serial.println("100 %");
    } else if (soilMoisturePercent <= 0) {
        soilMoisturePercent = 0;
        Serial.println("0 %");
    } else if (soilMoisturePercent > 0 && soilMoisturePercent < 100) {
        Serial.print(soilMoisturePercent);
        Serial.println("%");
    }
    Serial.println("End of measurement.");

    m_last_measurements.remove(0);
    m_last_measurements.push_back(soilMoisturePercent);

    Serial.print("Last measurements: [");
    for (const int element : m_last_measurements) {
        Serial.print(element);
        Serial.print(", ");
    }
    Serial.println("]");
}

int michal_moisture_checker::Plant::GetWaterLevel() {
    int measurementsSum = 0;
    for (const int item : m_last_measurements) {
        measurementsSum += item;
    }   
    
    return measurementsSum / m_last_measurements.size();
}

uint64_t michal_moisture_checker::Plant::GetWateringCounter() {
    return m_watering_counter;
}

void Plant::WaterPlantIfNeeded(int wateringTime) {
    if (!ShouldWater()) {
        Serial.println("Watering was skipped.");
        return;
    }
    Serial.print("Watering plant for ");
    Serial.print(wateringTime);
    Serial.println(" millis");
    
    m_watering_counter++;
    digitalWrite(m_watering_controler_output, LOW);
    delay(wateringTime);
    digitalWrite(m_watering_controler_output, HIGH);
 
    m_last_watering_timestamp = *m_timestamp;
    
    Serial.println("Watering finished.");
}