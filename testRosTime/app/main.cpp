#include <ros/callback_queue.h>
#include <ros/time.h>
#include <ros/timer_handle.h>
#include <ros/wall_timer.h>

#include <chrono>
#include <iostream>
#include <thread>

class WallTimerUser {
private:
  void initialize() {
    update_timer_ = nh_->createWallTimer(ros::WallDuration(1.0), &WallTimerUser::updateCallback, this, true);
  };

  void updateCallback(const ros::WallTimerEvent& /*event*/) { std::cout << __func__ << " callback" << std::endl; }

public:
  WallTimerUser(std::shared_ptr<ros::TimerHandle> nh) {
    nh_ = std::move(nh);
    initialize();
  };
  ~WallTimerUser(){};

  ros::WallTimer update_timer_;

  std::shared_ptr<ros::TimerHandle> nh_;
};

int main(int argc, char* argv[]) {
  // create callback queue;
  ros::CallbackQueue callback_queue;

  // create global timer handler
  auto nh = std::make_shared<ros::TimerHandle>();
  nh->setCallbackQueue(&callback_queue);
  WallTimerUser wt(nh);

  // use another thread to process callbacks
  std::thread t([&callback_queue]() {
    if (!callback_queue.isEnabled()) {
      std::cout << "not enabled" << std::endl;
    } else {
      ros::WallDuration d(0.001f);
      for (int32_t i = 0; i < 2000; ++i) {
        callback_queue.callAvailable(ros::WallDuration());
        d.sleep();
      }
    }
  });
  t.join();

  return 0;
}
