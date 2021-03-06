#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

const std::string configFile = "../transformation_camera_to_base.json";

int main(int argc, char* argv[]) {
  std::ifstream file;
  file.open(configFile);
  if (!file.is_open()) {
    std::cerr << "Configuration file cannot be loaded" << std::endl;
    return -1;
  }

  std::string jsonConfig((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  auto jsonTags = json::parse(jsonConfig);
  file.close();

  // clang-format off
  Eigen::Vector3d vec;
  vec << (jsonTags["bTc"]["pos"]["x"]),
         (jsonTags["bTc"]["pos"]["y"]),
         (jsonTags["bTc"]["pos"]["z"]);
  // clang-format on

  // clang-format off
  Eigen::Quaterniond q((jsonTags["bTc"]["quat"]["w"]),
                       (jsonTags["bTc"]["quat"]["x"]),
                       (jsonTags["bTc"]["quat"]["y"]),
                       (jsonTags["bTc"]["quat"]["z"]));
  // clang-format on

  std::cout << "bTc.p = \n" << vec.transpose() << std::endl;
  std::cout << "bTc.w = \n" << q.w() << std::endl;
  std::cout << "bTc.vec = \n" << q.vec().transpose() << std::endl;
}