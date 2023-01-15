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
#include "gpio.h"
#include "tim.h"

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Bool.h>

#include "Cytron_SmartDriveDuo.hpp"

#include "mainpp.h"

using namespace ros;
using geometry_msgs::Twist;
using std_msgs::Float32;
using std_msgs::Float32MultiArray;
using std_msgs::MultiArrayLayout;
using std_msgs::MultiArrayDimension;
using std_msgs::Bool;

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
Float32MultiArray dist;
Float32 time;
MultiArrayDimension dims;
Bool trig;

Publisher pub("/feedback", &msg);
Publisher pub_d("/distance", &dist);
Publisher pub_t("/time", &time);

Cytron_SmartDriveDuo csdd(CytronMode::SERIAL_SIMPLFIED, &huart1, 115200);

void cb(const Twist& data){
    float linear = data.linear.x;
    float angular = data.angular.z;

    float right_wheel = (linear - angular)*100;
    float left_wheel = (linear + angular)*100;

    csdd.control(left_wheel, right_wheel);
}

// All your callbacks, and other utility functions go below

class Ultrasonic {
private:
    uint16_t start_time;
    uint16_t end_time;
    uint8_t count;
public:
    static TIM_HandleTypeDef* TRIG_tim;
    static TIM_HandleTypeDef* ECHO_tim;
    const static uint8_t num_sensors;
    static uint8_t curr_sensor;

    GPIO_TypeDef* TRIG_Port;
    uint16_t TRIG_Pin;
    float distance;
    float pulse_width;
    bool pulse;

    Ultrasonic(GPIO_TypeDef* TRIG_Port, uint16_t TRIG_Pin) {
        this->TRIG_Port = TRIG_Port;
        this->TRIG_Pin = TRIG_Pin;
        pulse = false;
        count = 0;
    }

    static void trig_all_uss(const Bool& msg);

    void trig_start() {
        __HAL_TIM_CLEAR_FLAG(TRIG_tim, TIM_SR_UIF);
        HAL_GPIO_WritePin(TRIG_Port, TRIG_Pin, GPIO_PIN_SET);
        HAL_TIM_Base_Start_IT(TRIG_tim);
    }

    void echo_start() {
        start_time = HAL_TIM_ReadCapturedValue(ECHO_tim, TIM_CHANNEL_3);
    }

    void echo_end() {
        end_time = HAL_TIM_ReadCapturedValue(ECHO_tim, TIM_CHANNEL_3);
        pulse_width = (end_time - start_time)/4.0;
        if (pulse_width <= 0) {
            pulse_width += 65536;
        }
        distance = 340*pulse_width*0.000001/2;
        // dist.data = distance;
        time.data = pulse_width;
        // pub_d.publish(&dist);
        pub_t.publish(&time);

        curr_sensor++;
    }
};

TIM_HandleTypeDef* Ultrasonic::TRIG_tim = &htim11;
TIM_HandleTypeDef* Ultrasonic::ECHO_tim = &htim4;
const uint8_t Ultrasonic::num_sensors = 5;
uint8_t Ultrasonic::curr_sensor = 0;

Ultrasonic uss[Ultrasonic::num_sensors] = {
    Ultrasonic(TRIG0_GPIO_Port, TRIG0_Pin),
    Ultrasonic(TRIG1_GPIO_Port, TRIG1_Pin),
    Ultrasonic(TRIG2_GPIO_Port, TRIG2_Pin),
    Ultrasonic(TRIG3_GPIO_Port, TRIG3_Pin),
    Ultrasonic(TRIG4_GPIO_Port, TRIG4_Pin),
};

void Ultrasonic::trig_all_uss(const Bool& msg) {
    uint8_t sensor_trigd = -1;
    while (sensor_trigd < Ultrasonic::num_sensors) {
        if (sensor_trigd != Ultrasonic::curr_sensor) {
            sensor_trigd = Ultrasonic::curr_sensor;
            uss[sensor_trigd].trig_start();
        }
    }
    float distArray[Ultrasonic::num_sensors];
    float timeArray[Ultrasonic::num_sensors];
    Float32MultiArray distArrayMsg;
    for (uint8_t i = 0; i < Ultrasonic::num_sensors; i++) {
        distArray[i] = uss[i].distance;
        timeArray[i] = uss[i].pulse_width;
    }
    distArrayMsg.layout = MultiArrayLayout();
    distArrayMsg.layout.dim = (MultiArrayDimension *) malloc(sizeof MultiArrayDimension() * 2);

    distArrayMsg.layout.dim[0].size = Ultrasonic::num_sensors;
    distArrayMsg.layout.dim[0].stride = 1;
    distArrayMsg.layout.dim[0].label = "distances";

    distArrayMsg.layout.dim[1].size = Ultrasonic::num_sensors;
    distArrayMsg.layout.dim[1].stride = 1;
    distArrayMsg.layout.dim[1].label = "times";

    distArrayMsg.data = distArray;
    distArrayMsg.data = timeArray;

    pub_d.publish(&distArrayMsg);
}

Subscriber<Bool> sub_trig("/uss_trig", Ultrasonic::trig_all_uss);

void HAL_GPIO_EXTI_Callback(uint16_t pin) {
    if (pin == B1_Pin) {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        return;
    };
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim11) {
        HAL_GPIO_WritePin(uss[Ultrasonic::curr_sensor].TRIG_Port, uss[Ultrasonic::curr_sensor].TRIG_Pin, GPIO_PIN_RESET);
        HAL_TIM_Base_Stop_IT(&htim11);
        HAL_TIM_Base_DeInit(&htim11);
        HAL_TIM_Base_Init(&htim11);
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim4 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
        if (!uss[Ultrasonic::curr_sensor].pulse) {
            uss[Ultrasonic::curr_sensor].echo_start();
            uss[Ultrasonic::curr_sensor].pulse = true;
        } else {
            uss[Ultrasonic::curr_sensor].echo_end();
            uss[Ultrasonic::curr_sensor].pulse = false;
        }
    }
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
    nh.subscribe(sub_trig);
    nh.advertise(pub);
    nh.advertise(pub_d);
    nh.advertise(pub_t);
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);
}
