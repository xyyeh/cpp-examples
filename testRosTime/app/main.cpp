#include <chrono>
#include <iostream>
#include <ros/time.hpp>
#include <thread>

int main(int argc, char *argv[]) {
  ros::Time::init();
  ros::Time a_little_after_the_beginning(0.001);
  ros::Duration five_seconds(5.0);

  using namespace std::chrono_literals;

  auto t1 = ros::Time::now().toNSec();
  //   std::this_thread::sleep_for(1ms);
  ros::Duration(0.001).sleep();
  auto t2 = ros::Time::now().toNSec();

  std::cout << t2 - t1 << std::endl;

  ros::WallDuration dt_state_update_;

  /// timer for state updates.
  // Check if last_state_update_ is true and if so call updateSceneWithCurrentState()
  // Not safe to access from callback functions.
  //   ros::WallTimer state_update_timer_;

  /// Last time the state was updated from current_state_monitor_
  // Only access this from callback functions (and constructor)
  ros::WallTime last_robot_state_update_wall_time_;

  std::cout << last_robot_state_update_wall_time_.now();

  return 0;
}
