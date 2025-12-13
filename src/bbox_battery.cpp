#include "bbox_battery.h"

void beginBattery(Battery &battery, const uint8_t ADC_PIN)
{
    battery.ADC_PIN = ADC_PIN;
    analogReadResolution(12); // 0–4095
    analogSetPinAttenuation(ADC_PIN, ADC_11db);
}
/*
Monitors battery.
Takes 16 readings each loop (1000ms intervals);
Does this for 60 seconds and averages all readings
and updates batteryPercentage 1 time per minute.

Rough attempt to get a more stable voltage reading
*/
void batteryMonitorLoop(bool immediateUpdate, Battery &battery)
{
    static unsigned long percentTotal = 0;
    static int counter = 0;
    static unsigned long lastVoltageReadTime = 0;
    unsigned long currentVoltageReadTime = millis();
    battery.doBatteryStatusUpdate = false;

    if (((currentVoltageReadTime - lastVoltageReadTime) > VOLTAGE_READ_DELAY) || immediateUpdate)
    {
        lastVoltageReadTime = currentVoltageReadTime;
        int tempPercent;

        // Sample a set number of times and get the reading
        int total = 0;
        for (uint8_t i = 0; i < PER_READING_SAMPLE_COUNT; i++)
        {
            total += analogRead(battery.ADC_PIN);
        }

        // Get max/min voltage values for the current system battery type
        float _maxVoltage = battery.voltageRange[battery.currentBatteryType].maxVoltage;
        float _minVoltage = battery.voltageRange[battery.currentBatteryType].minVoltage;

        if (battery.calibratedADCReading == 0)
        {
            battery.calibratedADCReading = 4096;
        }

        // Calculate, based off of calibartion values max possible voltage
        float maxPossibleVoltage = (battery.calibratedVoltage * ADC_STEPS) / battery.calibratedADCReading;

        // Calculate actual voltage read
        battery.systemVoltage = ((total / PER_READING_SAMPLE_COUNT) / ADC_STEPS) * maxPossibleVoltage; // Convert to voltage

        // Need to make sure we don't divide by 0
        float voltageDiff = (_maxVoltage - _minVoltage);
        if (voltageDiff == 0)
        {
            voltageDiff = 2.0;
        }

        // Calculate percent then clamp it between 0 - 100
        tempPercent = ((battery.systemVoltage - _minVoltage) / voltageDiff) * 100;

        if (tempPercent > 100)
        {
            tempPercent = 100;
        }
        else if (tempPercent < 0)
        {
            tempPercent = 0;
        }

        // We also want to get average readings over 1 minute
        percentTotal += tempPercent;
        counter += 1;
        if (counter == 60)
        {
            battery.batteryPercent = percentTotal / 60;
            counter = 0;
            percentTotal = 0;
            battery.doBatteryStatusUpdate = true;
            switch (battery.powerStatus)
            {
            case BATTERY_OK:
                if (battery.batteryPercent <= 20)
                {
                    battery.powerStatus == BATTERY_LOW;
                }
                break;

            case BATTERY_LOW:
                if (battery.batteryPercent >= 25)
                {
                    battery.powerStatus = BATTERY_OK;
                }
                break;

            default:;
            }
        }
        else if (immediateUpdate)
        {
            battery.batteryPercent = tempPercent;
            battery.doBatteryStatusUpdate = true;
        }
    }
}