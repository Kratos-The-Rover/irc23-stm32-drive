/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : mainpp.cpp
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ros/subscriber.h"
#include "usart.h"

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Bool.h>

#include "Cytron_SmartDriveDuo.hpp"

#include "mainpp.h"

using namespace ros;
using geometry_msgs::Twist;

NodeHandle nh;

void HAL_UART_TxCpItCallback(UART_HandleTypeDef *huart){
    if(huart->Instance == USART2)
        nh.getHardware()->flush();
}

void HAL_UART_RxCpItCallback(UART_HandleTypeDef *huart){
    if(huart->Instance == USART2)
        nh.getHardware()->reset_rbuf();
}

Twist msg;

Publisher pub("/feedback", &msg);

Cytron_SmartDriveDuo csdd(CytronMode::SERIAL_SIMPLFIED, &huart1, 115200);

void cb(const Twist& data){
    float linear = data.linear.x;
    float angular = data.angular.z;

    msg = data;
    pub.publish(&msg);

    float right_wheel = (linear + angular)*100;
    float left_wheel = (linear - angular)*100;

    csdd.control(left_wheel, right_wheel);
}

// All your callbacks, and other utility functions go below

void HAL_GPIO_EXTI_Callback(uint16_t pin) {
    if (pin == B1_Pin) {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        return;
    };
}

void loop() {
    // All this code gets looped forever
    nh.spinOnce();
}

Subscriber<Twist> sub("/rover", &cb);

void init() {
    // This code runs before any init happens
}

void init_after_peripherals() {
    // This code runs after different peripheral inits happen
    nh.initNode();
    nh.subscribe(sub);
    nh.advertise(pub);
}
