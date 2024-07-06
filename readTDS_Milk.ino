#include <EEPROM.h>
#include "GravityTDS.h"

#define TdsSensorPin A1
GravityTDS gravityTds;

float temperature = 25, tdsValue = 0, fatContent = 0;

void setup()
{
    Serial.begin(115200);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  // Reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  // 1024 for 10-bit ADC; 4096 for 12-bit ADC
    gravityTds.begin();  // Initialization
}

void loop()
{
    gravityTds.setTemperature(temperature);  // Set the temperature and execute temperature compensation
    gravityTds.update();  // Sample and calculate
    tdsValue = gravityTds.getTdsValue();  // Get the TDS value in ppm

    // Convert TDS ppm to an approximate fat content estimation
    // This is a makeshift conversion and may not be accurate
    fatContent = map(tdsValue, 0, 2000, 0, 100); // Example conversion, adjust as needed

    Serial.print("TDS (ppm): ");
    Serial.print(tdsValue, 0);
    Serial.print(", Estimated Fat Content (%): ");
    Serial.println(fatContent, 2); // Print with 2 decimal places

    delay(1000);  // Delay for one second before the next reading
}
