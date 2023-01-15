#ifndef _ROS_electronics_custom_h
#define _ROS_electronics_custom_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Pose.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Time.h"

namespace electronics
{

  class custom : public ros::Msg
  {
    public:
      typedef geometry_msgs::Twist _velocity_type;
      _velocity_type velocity;
      typedef std_msgs::Float64 _distance_type;
      _distance_type distance;
      typedef geometry_msgs::Pose _coords_type;
      _coords_type coords;
      typedef std_msgs::Int32 _battery_type;
      _battery_type battery;
      typedef std_msgs::Time _time_type;
      _time_type time;

    custom():
      velocity(),
      distance(),
      coords(),
      battery(),
      time()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->velocity.serialize(outbuffer + offset);
      offset += this->distance.serialize(outbuffer + offset);
      offset += this->coords.serialize(outbuffer + offset);
      offset += this->battery.serialize(outbuffer + offset);
      offset += this->time.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->velocity.deserialize(inbuffer + offset);
      offset += this->distance.deserialize(inbuffer + offset);
      offset += this->coords.deserialize(inbuffer + offset);
      offset += this->battery.deserialize(inbuffer + offset);
      offset += this->time.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "electronics/custom"; };
    virtual const char * getMD5() override { return "19ccb3abd73a43b8aced5d44f561a836"; };

  };

}
#endif
