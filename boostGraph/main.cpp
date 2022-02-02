
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "DynamicRoadmap.hpp"

int main() {
  // Definition of graph
  DynamicRoadmap drm;

  // Occupied vertices
  std::unordered_set<uint> occupiedVertices{1, 2};
  std::vector<uint> path;

  // Solve astar
  drm.solve(1300, 2000000, 2, occupiedVertices, path);

  // Solution
  // for (const auto& K : path) {
  //   std::cout << K << std::endl;
  // }
  std::cout << "Path consists of " << path.size() << " nodes" << std::endl;
}