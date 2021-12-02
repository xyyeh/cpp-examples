#include <iostream>

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <set>

const std::string xmlPath = "../example.xml";

namespace pt = boost::property_tree;

struct Receipient {
  std::string m_name;
  std::string m_address;
};

int main() {
  pt::ptree propertyTree;
  pt::read_xml(xmlPath, propertyTree);

  BOOST_FOREACH (boost::property_tree::ptree::value_type &v,
                 propertyTree.get_child("link")) {
    std::cout << v.first << std::endl;

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
}