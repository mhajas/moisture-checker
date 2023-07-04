#ifndef MICHAL_MOISTURE_CHECKER_PLANT_H_
#define MICHAL_MOISTURE_CHECKER_PLANT_H_ 1

#include <Arduino.h>

namespace michal_moisture_checker {
    class Plant {
        private:
            const int m_moisture_sensor_input;

        public:
            Plant(int moisture_sensor_input) : m_moisture_sensor_input(moisture_sensor_input) {}
            int MeasureMoistureLevel();      
    };
}

#endif