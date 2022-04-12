#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <boost/program_options.hpp>
#include <iostream>
#include <string>

namespace {
const size_t ERROR_IN_COMMAND_LINE = 1;
const size_t SUCCESS = 0;
const size_t ERROR_UNHANDLED_EXCEPTION = 2;
}  // namespace

int main(int argc, char** argv) {
  try {
    /** Define and parse the program options
     */
    namespace po = boost::program_options;
    po::options_description desc("Options");
    // clang-format off
    desc.add_options()
      ("help", "Print help messages")
      ("camera settings,c", po::value<std::string>()->default_value("../config/high_accuracy_d435_default.json"), "Realsense camera settings")
      ("detector settings,d", po::value<std::string>()->default_value("../config/settings.json "), "Detector settings")
      ("tag settings,t", po::value<std::string>()->default_value("../config/tags.json "), "Tag settings");
    // clang-format on

    po::variables_map vm;
    try {
      po::store(po::parse_command_line(argc, argv, desc),
                vm);  // can throw

      if (vm.count("help")) {
        spdlog::info("\n{}", desc);
        return SUCCESS;
      }

      po::notify(vm);  // throws on error, so do after help in case
                       // there are any problems
    } catch (po::error& e) {
      spdlog::error("\n{}", e.what());
      spdlog::info("\n{}", desc);
      return ERROR_IN_COMMAND_LINE;
    }

    // application code here //
    std::cout << vm["camera settings"].as<std::string>() << std::endl;
    std::cout << vm["detector settings"].as<std::string>() << std::endl;
    std::cout << vm["tag settings"].as<std::string>() << std::endl;

  } catch (std::exception& e) {
    spdlog::error("Unhandled Exception reached the top of main: {}, application will now exit", e.what());
    return ERROR_UNHANDLED_EXCEPTION;
  }

  return SUCCESS;
}