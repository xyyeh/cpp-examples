#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <set>
#include <streambuf>

const std::string xmlPath = "../example.xml";

namespace pt = boost::property_tree;

std::string indent(int level) {
  std::string s;
  for (int i = 0; i < level; i++) s += "  ";
  return s;
}

void printTree(boost::property_tree::ptree &pt, int level) {
  if (pt.empty()) {
    std::cout << "\"" << pt.data() << "\"";
  }

  else {
    if (level) std::cout << std::endl;

    std::cout << indent(level) << "{" << std::endl;

    for (boost::property_tree::ptree::iterator pos = pt.begin(); pos != pt.end();) {
      std::cout << indent(level + 1) << "\"" << pos->first << "\": ";

      printTree(pos->second, level + 1);
      ++pos;
      if (pos != pt.end()) {
        std::cout << ",";
      }
      std::cout << std::endl;
    }

    std::cout << indent(level) << " }";
  }
  std::cout << std::endl;
  return;
}

int main() {
  std::ifstream fs(xmlPath);
  std::stringstream buffer;
  buffer << fs.rdbuf();

  pt::ptree propertyTree;
  pt::read_xml(buffer, propertyTree, pt::xml_parser::trim_whitespace);
  int i = 0;

  // read
  std::cout << propertyTree.get<std::string>("robot.<xmlattr>.name") << std::endl;
  BOOST_FOREACH (pt::ptree::value_type &v, propertyTree.get_child("robot.link")) {
    std::cout << "----------------- [i = " << i++ << "]-----------------" << std::endl;

    std::cout << "v.first = " << v.first << std::endl;
    if (v.first == "<xmlattr>") {
      std::cout << v.second.get<std::string>("name") << std::endl;
    } else {
      auto origin = v.second.get_child("origin");
      std::cout << origin.get<std::string>("<xmlattr>.xyz") << std::endl;
      std::cout << origin.get<std::string>("<xmlattr>.rpy") << std::endl;

      auto geom = v.second.get_child("geometry.mesh");
      std::cout << geom.get<std::string>("<xmlattr>.filename") << std::endl;
    }
  }

  // write
  propertyTree.add("robot.<xmlattr>.version", "2");

  pt::write_xml("temp.xml", propertyTree, std::locale(), pt::xml_writer_make_settings<std::string>(' ', 4));

  printTree(propertyTree, 3);
}