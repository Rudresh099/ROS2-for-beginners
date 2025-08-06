import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int32

class NumberCounterNode(Node):
    def __init__(self):
        super().__init__('number_counter')
        self.subscriber_ = self.create_subscription(
            Int32,
            'extreme',
            self.callback_counter,
            10
        )
        self.publisher_ = self.create_publisher(
            Int32,
            'number_count',
            10
        )
        self.get_logger().info("Number Counter Node has been started.")

    def callback_counter(self, msg):
        new_number = msg.data + 1
        self.get_logger().info(f"Received: {msg.data} | Publishing: {new_number}")
        
        out_msg = Int32()
        out_msg.data = new_number
        self.publisher_.publish(out_msg)

def main(args=None):
    rclpy.init(args=args)
    node = NumberCounterNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
