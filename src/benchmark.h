#pragma once

#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int8_multi_array.hpp"

struct SerializeResult {
  const std::byte *data;
  const size_t size;
};

template <typename T> class MinimalPublisher : public rclcpp::Node {
public:
  MinimalPublisher(std::string publisher_name = "REPLACE_ME_PUBLISHER",
                   std::string topic_name = "REPLACE_ME_TOPIC")
      : Node(publisher_name),
        publisher_(this->create_publisher<T>(topic_name, 10)) {}

  void publish(const SerializeResult *result) {
    auto message = std::make_unique<T>();
    message->data.resize(result->size);
    std::memcpy(message->data.data(), result->data, result->size);
    publisher_->publish(std::move(message));
  }

  typename rclcpp::Publisher<T>::SharedPtr publisher_;
};

template <typename T, typename Y> class Benchmarkable {
public:
  Benchmarkable(MinimalPublisher<Y> *publisher) : publisher_(publisher) {}
  virtual ~Benchmarkable() {}
  virtual const SerializeResult serialize(T message) = 0;
  virtual T makeMessage(const size_t num_cycles) = 0;

  void setSerializedResult(SerializeResult *result) { result_ = result; }

  void publish() { publisher_->publish(result_); }

protected:
  MinimalPublisher<Y> *publisher_;
  SerializeResult *result_;
};
