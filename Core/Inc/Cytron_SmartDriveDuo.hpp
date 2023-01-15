#ifndef CYTRON_SMARDRIVEDUO_h
#define CYTRON_SMARDRIVEDUO_h

#include "main.h"

enum class CytronMode {
    RC_MCU,
    PWM_INDEPENDENT,
    PWM_MIXED,
    SERIAL_SIMPLFIED,
    SERIAL_PACKETIZED
};

class Cytron_SmartDriveDuo {
public:
    Cytron_SmartDriveDuo(CytronMode mode, uint16_t in1Pin, uint16_t in2Pin, uint16_t an1Pin, uint16_t an2Pin);
    Cytron_SmartDriveDuo(CytronMode mode, UART_HandleTypeDef* uart_handle, uint32_t baudrate);
    Cytron_SmartDriveDuo(CytronMode mode, UART_HandleTypeDef* uart_handle, int boardId, uint32_t baudrate);
    void initialByte(uint8_t dummybyte);
    void control(signed int motorLeftSpeed, signed int motorRightSpeed);

private:
    CytronMode _mode;
    uint16_t _rc1Pin, _rc2Pin;
    uint16_t _an1Pin, _an2Pin, _in1Pin, _in2Pin;
    uint16_t _boardId;
    UART_HandleTypeDef* _uart_handle;
    uint8_t headerByte = 0x85, addressByte, commandByte, checksum;
    int _motorLSpeed, _motorRSpeed;
    int rc1Delay, rc2Delay;
};

#endif
