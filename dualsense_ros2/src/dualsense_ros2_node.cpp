#include "dualsense_ros2/dualsense_ros2_node.hpp"

namespace dualsense_ros2
{
    DualSenseROS2::DualSenseROS2(const rclcpp::NodeOptions & node_options) : rclcpp::Node("DualSenseROS2", node_options)
    {
        twist_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/dualsense/twist", rclcpp::SystemDefaultsQoS());

        f_publisher_1 = this->create_publisher<std_msgs::msg::Float32>("/dualsense/f", rclcpp::SystemDefaultsQoS());

        joy_subscriber_ = this->create_subscription<sensor_msgs::msg::Joy>("/joy", rclcpp::SystemDefaultsQoS(), std::bind(&DualSenseROS2::topic_callback, this, _1));

        this->declare_parameter("max_pow", 1.0);
        this->get_parameter("max_pow", max_pow_);

        RCLCPP_INFO(this->get_logger(), "DualSenseROS2 intialize OK!!");
    }

    void DualSenseROS2::topic_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        auto x_msg = std_msgs::msg::Float32();
        auto y_msg = std_msgs::msg::Float32();
        auto rotation_msg = std_msgs::msg::Float32();
        auto cmd = geometry_msgs::msg::Twist();
        cmd.linear.y = -max_pow_* msg->axes[0];
        cmd.linear.x = max_pow_ * msg->axes[1];
        cmd.angular.z = max_pow_* msg->axes[3];

        auto f1_msg = std_msgs::msg::Float32();

        // left right
        f1_msg.data = -1.0 * msg->axes[7];

        twist_publisher_->publish(cmd);
        f_publisher_1->publish(f1_msg);
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(dualsense_ros2::DualSenseROS2)