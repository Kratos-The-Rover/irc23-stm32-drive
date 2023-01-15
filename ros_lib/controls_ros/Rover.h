#ifndef _ROS_controls_ros_Rover_h
#define _ROS_controls_ros_Rover_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace controls_ros
{

  class Rover : public ros::Msg
  {
    public:
      typedef bool _left_bev_dir_type;
      _left_bev_dir_type left_bev_dir;
      typedef bool _left_bev_pwm_type;
      _left_bev_pwm_type left_bev_pwm;
      typedef bool _right_bev_dir_type;
      _right_bev_dir_type right_bev_dir;
      typedef bool _right_bev_pwm_type;
      _right_bev_pwm_type right_bev_pwm;
      typedef bool _l1_dir_type;
      _l1_dir_type l1_dir;
      typedef bool _l1_pwm_type;
      _l1_pwm_type l1_pwm;
      typedef bool _l2_dir_type;
      _l2_dir_type l2_dir;
      typedef bool _l2_pwm_type;
      _l2_pwm_type l2_pwm;
      typedef bool _base_dir_type;
      _base_dir_type base_dir;
      typedef bool _base_pwm_type;
      _base_pwm_type base_pwm;
      typedef bool _stepper_dir_type;
      _stepper_dir_type stepper_dir;
      typedef bool _stepper_step_type;
      _stepper_step_type stepper_step;
      typedef int8_t _right_wheel_vel_type;
      _right_wheel_vel_type right_wheel_vel;
      typedef int8_t _left_wheel_vel_type;
      _left_wheel_vel_type left_wheel_vel;

    Rover():
      left_bev_dir(0),
      left_bev_pwm(0),
      right_bev_dir(0),
      right_bev_pwm(0),
      l1_dir(0),
      l1_pwm(0),
      l2_dir(0),
      l2_pwm(0),
      base_dir(0),
      base_pwm(0),
      stepper_dir(0),
      stepper_step(0),
      right_wheel_vel(0),
      left_wheel_vel(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_left_bev_dir;
      u_left_bev_dir.real = this->left_bev_dir;
      *(outbuffer + offset + 0) = (u_left_bev_dir.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->left_bev_dir);
      union {
        bool real;
        uint8_t base;
      } u_left_bev_pwm;
      u_left_bev_pwm.real = this->left_bev_pwm;
      *(outbuffer + offset + 0) = (u_left_bev_pwm.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->left_bev_pwm);
      union {
        bool real;
        uint8_t base;
      } u_right_bev_dir;
      u_right_bev_dir.real = this->right_bev_dir;
      *(outbuffer + offset + 0) = (u_right_bev_dir.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->right_bev_dir);
      union {
        bool real;
        uint8_t base;
      } u_right_bev_pwm;
      u_right_bev_pwm.real = this->right_bev_pwm;
      *(outbuffer + offset + 0) = (u_right_bev_pwm.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->right_bev_pwm);
      union {
        bool real;
        uint8_t base;
      } u_l1_dir;
      u_l1_dir.real = this->l1_dir;
      *(outbuffer + offset + 0) = (u_l1_dir.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->l1_dir);
      union {
        bool real;
        uint8_t base;
      } u_l1_pwm;
      u_l1_pwm.real = this->l1_pwm;
      *(outbuffer + offset + 0) = (u_l1_pwm.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->l1_pwm);
      union {
        bool real;
        uint8_t base;
      } u_l2_dir;
      u_l2_dir.real = this->l2_dir;
      *(outbuffer + offset + 0) = (u_l2_dir.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->l2_dir);
      union {
        bool real;
        uint8_t base;
      } u_l2_pwm;
      u_l2_pwm.real = this->l2_pwm;
      *(outbuffer + offset + 0) = (u_l2_pwm.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->l2_pwm);
      union {
        bool real;
        uint8_t base;
      } u_base_dir;
      u_base_dir.real = this->base_dir;
      *(outbuffer + offset + 0) = (u_base_dir.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->base_dir);
      union {
        bool real;
        uint8_t base;
      } u_base_pwm;
      u_base_pwm.real = this->base_pwm;
      *(outbuffer + offset + 0) = (u_base_pwm.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->base_pwm);
      union {
        bool real;
        uint8_t base;
      } u_stepper_dir;
      u_stepper_dir.real = this->stepper_dir;
      *(outbuffer + offset + 0) = (u_stepper_dir.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->stepper_dir);
      union {
        bool real;
        uint8_t base;
      } u_stepper_step;
      u_stepper_step.real = this->stepper_step;
      *(outbuffer + offset + 0) = (u_stepper_step.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->stepper_step);
      union {
        int8_t real;
        uint8_t base;
      } u_right_wheel_vel;
      u_right_wheel_vel.real = this->right_wheel_vel;
      *(outbuffer + offset + 0) = (u_right_wheel_vel.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->right_wheel_vel);
      union {
        int8_t real;
        uint8_t base;
      } u_left_wheel_vel;
      u_left_wheel_vel.real = this->left_wheel_vel;
      *(outbuffer + offset + 0) = (u_left_wheel_vel.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->left_wheel_vel);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_left_bev_dir;
      u_left_bev_dir.base = 0;
      u_left_bev_dir.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->left_bev_dir = u_left_bev_dir.real;
      offset += sizeof(this->left_bev_dir);
      union {
        bool real;
        uint8_t base;
      } u_left_bev_pwm;
      u_left_bev_pwm.base = 0;
      u_left_bev_pwm.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->left_bev_pwm = u_left_bev_pwm.real;
      offset += sizeof(this->left_bev_pwm);
      union {
        bool real;
        uint8_t base;
      } u_right_bev_dir;
      u_right_bev_dir.base = 0;
      u_right_bev_dir.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->right_bev_dir = u_right_bev_dir.real;
      offset += sizeof(this->right_bev_dir);
      union {
        bool real;
        uint8_t base;
      } u_right_bev_pwm;
      u_right_bev_pwm.base = 0;
      u_right_bev_pwm.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->right_bev_pwm = u_right_bev_pwm.real;
      offset += sizeof(this->right_bev_pwm);
      union {
        bool real;
        uint8_t base;
      } u_l1_dir;
      u_l1_dir.base = 0;
      u_l1_dir.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->l1_dir = u_l1_dir.real;
      offset += sizeof(this->l1_dir);
      union {
        bool real;
        uint8_t base;
      } u_l1_pwm;
      u_l1_pwm.base = 0;
      u_l1_pwm.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->l1_pwm = u_l1_pwm.real;
      offset += sizeof(this->l1_pwm);
      union {
        bool real;
        uint8_t base;
      } u_l2_dir;
      u_l2_dir.base = 0;
      u_l2_dir.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->l2_dir = u_l2_dir.real;
      offset += sizeof(this->l2_dir);
      union {
        bool real;
        uint8_t base;
      } u_l2_pwm;
      u_l2_pwm.base = 0;
      u_l2_pwm.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->l2_pwm = u_l2_pwm.real;
      offset += sizeof(this->l2_pwm);
      union {
        bool real;
        uint8_t base;
      } u_base_dir;
      u_base_dir.base = 0;
      u_base_dir.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->base_dir = u_base_dir.real;
      offset += sizeof(this->base_dir);
      union {
        bool real;
        uint8_t base;
      } u_base_pwm;
      u_base_pwm.base = 0;
      u_base_pwm.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->base_pwm = u_base_pwm.real;
      offset += sizeof(this->base_pwm);
      union {
        bool real;
        uint8_t base;
      } u_stepper_dir;
      u_stepper_dir.base = 0;
      u_stepper_dir.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->stepper_dir = u_stepper_dir.real;
      offset += sizeof(this->stepper_dir);
      union {
        bool real;
        uint8_t base;
      } u_stepper_step;
      u_stepper_step.base = 0;
      u_stepper_step.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->stepper_step = u_stepper_step.real;
      offset += sizeof(this->stepper_step);
      union {
        int8_t real;
        uint8_t base;
      } u_right_wheel_vel;
      u_right_wheel_vel.base = 0;
      u_right_wheel_vel.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->right_wheel_vel = u_right_wheel_vel.real;
      offset += sizeof(this->right_wheel_vel);
      union {
        int8_t real;
        uint8_t base;
      } u_left_wheel_vel;
      u_left_wheel_vel.base = 0;
      u_left_wheel_vel.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->left_wheel_vel = u_left_wheel_vel.real;
      offset += sizeof(this->left_wheel_vel);
     return offset;
    }

    virtual const char * getType() override { return "controls_ros/Rover"; };
    virtual const char * getMD5() override { return "cc0e5bc6bd16236af4ed661f54f0e1fb"; };

  };

}
#endif
