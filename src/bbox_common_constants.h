#pragma once
#include <Arduino.h>

#define MAX_SYSTEM_NAME_LEN 25
#define MAC_ADDRESS_LEN 6
#define BB_WIFI_CHANNEL 3

// Shared enums
// enums for StatusMsg, I think?
enum REMOTE_MODE
{
    REMOTE,
    LOCAL
};

enum ARM_STATUS
{
    NOT_ARMED,
    ARMED
};