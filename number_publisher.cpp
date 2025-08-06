#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int32.hpp"

using namespace std::chrono_literals;

class NumberPublisherNode : public rclcpp::Node // Node class definition
{
public:
    NumberPublisherNode() : Node("number_publisher") // Node name
    {
        publisher_ = this->create_publisher<example_interfaces::msg::Int32>("extreme", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&NumberPublisherNode::publishNumber, this));
        RCLCPP_INFO(this->get_logger(), "Number Publisher Node has been started.");
    }

private:
    void publishNumber()
    {
        auto msg = example_interfaces::msg::Int32();
        msg.data = 9;
        publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "Publishing: %d", msg.data);
    }

    rclcpp::Publisher<example_interfaces::msg::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}   
