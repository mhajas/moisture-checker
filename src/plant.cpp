#include "plant.h"
#include "constants.h"

using namespace michal_moisture_checker;

int Plant::MeasureMoistureLevel() {
    Serial.print("Started reading for plant ");
    Serial.print(m_moisture_sensor_input);
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

    return soilMoisturePercent;
}