#pragma once
#include <Arduino.h>

#define MAX_SYSTEM_NAME_LEN 25

enum REMOTE_MODE {
  REMOTE,
  LOCAL
};

enum ARM_STATUS
{
    NOT_ARMED,
    ARMED
};

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

enum MasterSendReqType : uint8_t {
  SEND_FIRE_CMD = 1,
  SEND_STATUS_REQ = 2
};

typedef struct {
  MasterSendReqType type;
  uint8_t mac[6];
  uint8_t port;
  uint16_t holdDuration;
} MasterSendRequest;

typedef struct {
  SendReqType type;
} SendRequest;

// Generic incoming message struct
typedef struct {
  uint8_t data[32];
  uint8_t mac[6];
  int len;
} IncomingMsg;

// From master to remote
typedef struct __attribute__((packed)) {
  MsgType type;      // always MSG_FIRE
  uint8_t portId;
  uint16_t holdMs;
} FireMsg;

// from remote to master
typedef struct __attribute__((packed)) {
  MsgType type;      // always MSG_STATUS
  uint8_t mode;
  char systemName[MAX_SYSTEM_NAME_LEN];
  uint8_t isArmed;
  uint8_t activeBankCount;
  uint8_t batteryPercent;
} StatusMsg;

// from master to remote
typedef struct __attribute__((packed)) {
  MsgType type;      // always MSG_CONFIG
} StatusRequest;


// from remote to master
typedef struct __attribute__((packed)) {
  MsgType type;      // always MSG_CONFIG
} AwkMsg;