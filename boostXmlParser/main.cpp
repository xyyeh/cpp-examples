#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <set>
#include <sstream>
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

  std::string str = buffer.str();

  std::stringstream input(str);

  pt::ptree propertyTree;
  pt::read_xml(input, propertyTree, pt::xml_parser::trim_whitespace);
  int i = 0;

  if (propertyTree.get_child("robot").count("group")) {
    std::cout << "srdf file, exit!" << std::endl;
    return -1;
  }

  // edit
  std::string dirPrefix = "path";
  propertyTree.add("robot.<xmlattr>.version", "2");
  BOOST_FOREACH (pt::ptree::value_type &v, propertyTree.get_child("robot")) {
    if (v.first == "<xmlattr>") {
      std::cout << v.second.get<std::string>("name") << std::endl;
    } else {
      auto &visualMesh = v.second.get_child("visual.geometry.mesh");
      auto visualPath = visualMesh.get<std::string>("<xmlattr>.filename");
      visualPath.erase(0, strlen("package://description"));
      visualMesh.put("<xmlattr>.filename", dirPrefix + visualPath);

      auto &collision = v.second.get_child("collision.geometry");
      auto collisionPath = collision.get<std::string>("mesh.<xmlattr>.filename");
      collisionPath.erase(0, strlen("package://description"));
      collisionPath.replace(collisionPath.end() - strlen("obj"), collisionPath.end(), "stl");
      collision.erase("mesh");
      collision.add("convex_mesh.<xmlattr>.filename", dirPrefix + collisionPath);
    }
  }

  // write
  std::string xml;
  std::ostringstream oss;
  pt::write_xml(oss, propertyTree, pt::xml_writer_make_settings<std::string>(' ', 4));
  xml = oss.str();
  std::cout << "------------------------\n" << xml << std::endl;

  pt::write_xml("temp.xml", propertyTree, std::locale(), pt::xml_writer_make_settings<std::string>(' ', 4));
  // printTree(propertyTree, 3);
}