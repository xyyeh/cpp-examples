#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <iostream>
#include <string>

namespace bp = boost::process;
namespace bf = boost::filesystem;

std::string getBoostXmlParserPath() {
  auto p = boost::filesystem::current_path();
  p = p.parent_path().parent_path() / "boostXmlParser" / "build" / "boost_xml_parser";

  return p.string();
}

int main() {
  // Create a child process with its output piped
  bp::ipstream output;
  bp::child c(getBoostXmlParserPath(), bp::std_out > output);

  // Read the output of the child process
  std::string line;
  while (std::getline(output, line)) {
    std::cout << line << std::endl;
  }

  // Wait for the child process to finish
  c.wait();

  return 0;
}