#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <set>
#include <sstream>
#include <streambuf>

// const std::string xmlPath = "../test.srdf";
const std::string xmlPath = "../test.urdf";

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

  std::cout << "Begin parsing" << std::endl;

  std::string oldPrefix = "package://description";
  std::string newPrefix = "path";

  auto updatePrefixSingle = [=](boost::optional<pt::ptree &> t, const std::string &oldPrefix,
                                const std::string &newPrefix) {
    if (t) {
      auto path = t->get<std::string>("<xmlattr>.filename");
      path.erase(0, oldPrefix.size());
      t->put("<xmlattr>.filename", newPrefix + path);
    }
  };

  boost::optional<pt::ptree &> group = propertyTree.get_child_optional("robot.group");

  if (group) {
    std::cout << "srdf" << std::endl;

    updatePrefixSingle(propertyTree.get_child_optional("robot.contact_managers_plugin_config"), oldPrefix, newPrefix);
    updatePrefixSingle(propertyTree.get_child_optional("robot.kinematics_plugin_config"), oldPrefix, newPrefix);

  } else {
    std::cout << "urdf" << std::endl;

    // edit
    propertyTree.add("robot.<xmlattr>.version", "2");
    BOOST_FOREACH (pt::ptree::value_type &v, propertyTree.get_child("robot")) {
      updatePrefixSingle(v.second.get_child_optional("visual.geometry.mesh"), oldPrefix, newPrefix);

      boost::optional<pt::ptree &> co = v.second.get_child_optional("collision.geometry");
      if (co) {
        auto path = co->get<std::string>("mesh.<xmlattr>.filename");
        path.erase(0, oldPrefix.size());

        std::string toReplace = "obj";
        size_t pos = path.find(toReplace);
        if (pos != std::string::npos) {
          path.replace(pos, toReplace.size(), "stl");
        }
        co->erase("mesh");
        co->add("convex_mesh.<xmlattr>.filename", newPrefix + path);
      }
    }
  }

  // settings
  auto settings = pt::xml_writer_make_settings<std::string>(' ', 4);

  // write
  std::string xml;
  std::ostringstream oss;
  pt::write_xml(oss, propertyTree, settings);
  xml = oss.str();
  // std::cout << "------------------------\n" << xml << std::endl;

  pt::write_xml("output.xml", propertyTree, std::locale(), settings);
  // printTree(propertyTree, 3);
}