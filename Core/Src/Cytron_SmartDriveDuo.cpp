#include "Cytron_SmartDriveDuo.hpp"
#include "main.h"

#define UART_TIMEOUT 50

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

Cytron_SmartDriveDuo::Cytron_SmartDriveDuo(CytronMode mode, uint16_t in1Pin, uint16_t in2Pin, uint16_t an1Pin, uint16_t an2Pin) {
    _mode = mode;
    _an1Pin = an1Pin;
    _an2Pin = an2Pin;
    _in1Pin = in1Pin;
    _in2Pin = in2Pin;
}

Cytron_SmartDriveDuo::Cytron_SmartDriveDuo(CytronMode mode, UART_HandleTypeDef* uart_handle, uint32_t baudrate) {
    _mode = mode;
    _uart_handle = uart_handle;
}

Cytron_SmartDriveDuo::Cytron_SmartDriveDuo(CytronMode mode, UART_HandleTypeDef* uart_handle, int boardId, uint32_t baudrate) {
    _mode = mode;
    _uart_handle = uart_handle;
    _boardId = boardId;
}

void Cytron_SmartDriveDuo::initialByte(uint8_t dummyByte) {
    HAL_UART_Transmit(_uart_handle, &dummyByte, 1, UART_TIMEOUT);
}

void Cytron_SmartDriveDuo::control(signed int motorLSpeed, signed int motorRSpeed) {
    switch (_mode) {
        case CytronMode::SERIAL_SIMPLFIED:
            if (motorLSpeed >= 0) {
                commandByte = 0x0;
                _motorLSpeed = map(motorLSpeed, 0, 100, 0, 63);
            } else {
                commandByte = 0x40;
                _motorLSpeed = map(motorLSpeed, 0, -100, 0, 63);
            }
            commandByte = commandByte | _motorLSpeed;
            HAL_UART_Transmit(_uart_handle, &commandByte, 1, UART_TIMEOUT);

            if (motorRSpeed >= 0) {
                commandByte = 0xC0;
                _motorRSpeed = map(motorRSpeed, 0, 100, 0, 63);
            } else {
                commandByte = 0x80;
                _motorRSpeed = map(motorRSpeed, 0, -100, 0, 63);
            }
            commandByte = commandByte | _motorRSpeed;
            HAL_UART_Transmit(_uart_handle, &commandByte, 1, UART_TIMEOUT);
            break;

        case CytronMode::SERIAL_PACKETIZED:
            addressByte = _boardId;
            commandByte = map(motorLSpeed, -100, 100, 0, 255);
            checksum = headerByte + addressByte + commandByte;
            HAL_UART_Transmit(_uart_handle, &headerByte, 1, UART_TIMEOUT);
            HAL_UART_Transmit(_uart_handle, &addressByte, 1, UART_TIMEOUT);
            HAL_UART_Transmit(_uart_handle, &commandByte, 1, UART_TIMEOUT);
            HAL_UART_Transmit(_uart_handle, &checksum, 1, UART_TIMEOUT);
            break;

        default:
            break;
    }
}
