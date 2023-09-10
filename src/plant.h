#ifndef MICHAL_MOISTURE_CHECKER_PLANT_H_
#define MICHAL_MOISTURE_CHECKER_PLANT_H_ 1

#include <Arduino.h>
#include <Array.h>

namespace michal_moisture_checker {
    enum State { INIT, WATERED, DRYING, STOPPED };

    class Plant {
        private:
            const uint8_t m_moisture_sensor_input;
            const uint8_t m_watering_controler_output;
            State m_state = INIT;
            Array<int, 20> m_last_measurements;
            uint64_t* m_timestamp;
            uint64_t m_last_watering_timestamp;
            uint64_t m_watering_counter;
            bool ShouldWater();
        public:
            Plant(uint8_t moisture_sensor_input, uint8_t watering_controler_output, uint64_t* timestamp) 
                : m_moisture_sensor_input(moisture_sensor_input)
                , m_watering_controler_output(watering_controler_output)
                , m_timestamp(timestamp)
            {
                for (int i = 0; i < 20; i++) {
                    m_last_measurements.push_back(100);
                }
            }

            void MeasureMoistureLevel();      
            void WaterPlantIfNeeded(int wateringTime = 2000);
            int GetWaterLevel();
            uint64_t GetWateringCounter();
    };
}

#endif