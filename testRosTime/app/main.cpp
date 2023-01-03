#include <ros/callback_queue.h>
#include <ros/time.h>
#include <ros/timer_handle.h>
#include <ros/wall_timer.h>

#include <chrono>
#include <iostream>
#include <thread>

class TimerSystem {
private:
  /// @brief Timer system callback queue
  ros::CallbackQueuePtr queue_;

  /// @brief Callback thread handler
  std::unique_ptr<std::thread> callback_;

  /// @brief Timer handle
  std::unique_ptr<ros::TimerHandle> timer_handle_;

public:
  TimerSystem(/* args */) {
    ros::Time::init();

    if (queue_ == nullptr) {
      queue_.reset(new ros::CallbackQueue());
    }

    timer_handle_ = std::make_unique<ros::TimerHandle>();
    timer_handle_->setCallbackQueue(queue_.get());
  };
  ~TimerSystem() { stopTimerThread(); };

  void callbackThread() {
    ros::WallDuration d(0.001f);
    do {
      queue_->callAvailable();
      d.sleep();
    } while (callback_);
  }

  ros::WallTimer createWallTimer(double interval, const std::function<void(const ros::WallTimerEvent&)>& callback,
                                 bool oneshot = true, bool autostart = true) {
    return timer_handle_->createWallTimer(ros::WallDuration(interval), callback, oneshot, autostart);
  }

  void startTimerThread() {
    if (!callback_) {
      callback_ = std::make_unique<std::thread>(std::bind(&TimerSystem::callbackThread, this));
    }
  };

  void stopTimerThread() {
    if (callback_) {
      std::unique_ptr<std::thread> copy;
      copy.swap(callback_);
      copy->join();
      stopTimerThread();
    }
  };
};

class WallTimerUser {
private:
  void initialize() {
    update_timer_ =
        timer_system_->createWallTimer(1.0, std::bind(&WallTimerUser::updateCallback, this, std::placeholders::_1));
  };

  void updateCallback(const ros::WallTimerEvent& /*event*/) {
    std::cout << "WallTimerUser: " << __func__ << " callback" << std::endl;
  }

public:
  /// @brief Constructor passing in timer system as node handler
  /// @param timerSystem Timer system
  WallTimerUser(std::shared_ptr<TimerSystem> timerSystem) {
    timer_system_ = std::move(timerSystem);
    initialize();
  };
  ~WallTimerUser(){};

  /// @brief Timer callback
  ros::WallTimer update_timer_;

  /// @brief Pointer to timer system
  std::shared_ptr<TimerSystem> timer_system_;
};

int main(int argc, char* argv[]) {
  // timer system
  auto ts = std::make_shared<TimerSystem>();
  auto user = std::make_shared<WallTimerUser>(ts);

  ts->startTimerThread();
  std::cout << "start sleep" << std::endl;
  ros::Duration(2).sleep();
  std::cout << "stop sleep " << std::endl;

  ts->stopTimerThread();

  return 0;
}
