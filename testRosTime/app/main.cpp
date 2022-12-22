#include <ros/time.h>
#include <ros/wall_timer.h>

#include <chrono>
#include <iostream>
// #include <ros/timer_operations.hpp>
#include <thread>

int main(int argc, char *argv[]) {
  ros::Time::init();
  ros::Time a_little_after_the_beginning(0.001);
  ros::Duration five_seconds(5.0);

  using namespace std::chrono_literals;

  auto t1 = ros::Time::now().toNSec();
  ros::Duration(0.1).sleep();
  auto t2 = ros::Time::now().toNSec();
  std::cout << (t2 - t1) * 1e-9 << std::endl;

  ros::WallTime wall_time;
  std::cout << wall_time.now() << std::endl;
  ros::WallDuration(0.1).sleep();
  std::cout << wall_time.now() << std::endl;

  ros::WallDuration dt_state_update_;
  dt_state_update_.fromSec(1.0);
  ros::WallTimer state_update_timer_;
  state_update_timer_.setPeriod(dt_state_update_);
  state_update_timer_.start();
  ros::WallDuration(0.1).sleep();
  state_update_timer_.stop();

  return 0;
}
