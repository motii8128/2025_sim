#ifndef DUALSENES_ROS2_NODE_HPP_
#define DUALSENES_ROS2_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <chrono>

using std::placeholders::_1;
using namespace std::chrono_literals;

namespace dualsense_ros2
{
    class DualSenseROS2 : public rclcpp::Node
    {
        public:
        DualSenseROS2(const rclcpp::NodeOptions & node_options=rclcpp::NodeOptions());
        void topic_callback(const sensor_msgs::msg::Joy::SharedPtr msg);
        
        private:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_publisher_;
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr f_publisher_1;

        rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscriber_;

        float max_pow_;
    };
}

#endif