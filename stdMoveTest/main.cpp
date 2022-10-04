// test
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class environment {
public:
  environment() = default;
  virtual ~environment() = default;

  void print() { std::cout << "inside environment, env_value_'s value " << env_value_ << std::endl; }

private:
  unsigned int env_value_{0};
};

class test {
public:
  test() = default;
  virtual ~test() = default;

  void print() { std::cout << "test a = " << value_ << std::endl; }
  void update() { value_++; }
  int getValue() { return value_; }
  void init(std::shared_ptr<environment> e) {
    // std::cout << env_.use_count() << std::endl;
    env_ = std::move(e);
    // env_ = env;

    std::cout << "shared ptr count env_ = " << env_.use_count() << ", " << e.use_count() << std::endl;
  }

private:
  unsigned int value_{0};
  std::shared_ptr<environment> env_;
};

int main() {
  auto env = std::make_shared<environment>();

  std::cout << env.use_count() << std::endl;

  test temp;
  temp.init(env);
}