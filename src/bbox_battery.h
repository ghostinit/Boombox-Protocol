#pragma once

#include <Arduino.h>

// Battery constants
#define VOLTAGE_READ_DELAY 1000
#define PER_READING_SAMPLE_COUNT 16

#define BATTERY_TYPE_NIMH96 0
#define BATTERY_TYPE_SLA 1

#define CONFIGURED_BATTERY_TYPES 2

#define NIMH96_MAX_VOLTAGE 11.2
#define NIHM96_MIN_VOLTAGE 8.0

#define SLA_MAX_VOLTAGE 12.6
#define SLA_MIN_VOLTAGE 11.31

#define V_REF 3.3
#define R_BITS 12 // ADC resolution

const float ADC_STEPS = (1 << R_BITS) - 1;

const String batteryTypeNames[] = {
    "9.6V NiMH",
    "Sealed Lead Acid"};

enum POWER_STATUS
{
    BATTERY_OK,
    BATTERY_LOW
};

struct VoltageRange
{
    float maxVoltage;
    float minVoltage;
};

struct Battery
{
    uint16_t currentBatteryType = BATTERY_TYPE_NIMH96;
    VoltageRange voltageRange[CONFIGURED_BATTERY_TYPES] = {
        {NIMH96_MAX_VOLTAGE, NIHM96_MIN_VOLTAGE},
        {SLA_MAX_VOLTAGE, SLA_MIN_VOLTAGE}};
    float calibratedVoltage = 13.5;
    uint16_t calibratedADCReading = 4096;
    uint8_t batteryPercent;
    float systemVoltage;
    bool doBatteryStatusUpdate;
    POWER_STATUS powerStatus = BATTERY_OK;
}

extern Battery battery;

void testFunction();