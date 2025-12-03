#pragma once
#include <Arduino.h>

enum MsgType : uint8_t {
  MSG_FIRE = 1,
  MSG_STATUS = 2,
  MSG_STATUS_REQUEST = 3,
  MSG_AWK = 4
};

enum SendReqType : uint8_t {
    SEND_ACK = 1,
    SEND_STATUS = 2
};

// typedef struct __attribute__((packed))
// {
//   uint8_t id;
//   uint8_t command;
//   uint8_t port;
// } Message;

typedef struct __attribute__((packed)) {
  MsgType type;      // always MSG_FIRE
  uint8_t portId;
  uint16_t holdMs;
} FireMsg;

typedef struct __attribute__((packed)) {
  MsgType type;      // always MSG_STATUS
  uint8_t isArmed;
  uint8_t batteryPercent;
} StatusMsg;

typedef struct __attribute__((packed)) {
  MsgType type;      // always MSG_CONFIG
} StatusRequest;

typedef struct __attribute__((packed)) {
  MsgType type;      // always MSG_CONFIG
} AwkMsg;