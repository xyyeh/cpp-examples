#include "DynamicRoadmapBoost.hpp"

#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

DynamicRoadmapBoost::DynamicRoadmapBoost() {
  // calculate the deltas and the K
  for (uint i = 0; i < k_dof; i++) {
    // double deltaN = (1 + (sqrt(2) * k_linkWidth)) / ((k_dof - i) * k_linkLength);
    // uint8_t temp_K = std::ceil((2 * M_PI) / deltaN + 1);
    // uint8_t temp_K = 3;
    // m_K.push_back(temp_K);
    // m_deltaN.push_back(2 * M_PI / temp_K);

    std::vector<uint8_t> numDiscStates{16, 15, 15, 15, 12, 5};
    m_K = numDiscStates;
  }
  std::cout << "For dof = " << (int)k_dof << ", K = [";
  for (const auto& K : m_K) {
    std::cout << (int)K << ", ";
  }
  std::cout << '\b' << '\b' << "]" << std::endl;

  // number of indices
  uint numIndices = 1;
  for (uint i = 0; i < k_dof; i++) {
    numIndices *= m_K[i];
  }

  // lambda expression to create vertices
  const auto& getOrCreateVertex = [&](uint index) {
    if (!m_vertices.count(index)) {
      Vertex newVertex = boost::add_vertex(vertex_info{index}, m_graph);
      m_vertices[index] = newVertex;
    }
    return m_vertices.at(index);
  };

  // for all the vertices at the leaf nodes
  for (unsigned int i = 1; i < numIndices + 1; i++) {
    // create vertex
    auto curVertex = getOrCreateVertex(i);
    // hierarchical configuration
    auto k = getHierarchicalConfigurationFromIndex(i);
    // find neighbors
    auto neighbors = findNeighbors(std::make_pair(k_dof, i));
    // add edge to neighbors
    for (const auto& neighbor : neighbors) {
      uint neighborIndex = neighbor.second;
      auto neighborVertex = getOrCreateVertex(neighborIndex);
      boost::add_edge(neighborVertex, curVertex, 1.0, m_graph);
    }
  }

  std::cout << "Num vertices = " << boost::num_vertices(m_graph) << std::endl;
  std::cout << "Num edges = " << boost::num_edges(m_graph) << std::endl;
  std::cout << "Graph created" << std::endl;

  ///////////////////////////////////// print graph /////////////////////////////////////
  // print_graph(m_graph);

  auto PrintVector = [=](std::vector<uint> vec) {
    std::stringstream ss;
    ss << "[";
    for (const auto& v : vec) {
      ss << v << ", ";
    }
    ss << '\b' << '\b' << "]";
    return ss.str();
  };

  for (uint i = 0; i < boost::num_vertices(m_graph); i++) {
    auto index = m_graph[i].index;
    auto k = getHierarchicalConfigurationFromIndex(std::make_pair(k_dof, index));
    // std::cout << "Index = " << i << ", Leaf index = " << m_graph[i].index << ", " << PrintVector(k) << std::endl;
    // std::cout << "Leaf index = " << m_graph[i].index << ", " << PrintVector(k) << std::endl;
  }

  ///////////////////////////////////// print edge weights /////////////////////////////////////
  // using EdgeIter = boost::graph_traits<Graph>::edge_iterator;

  // auto edgeWeightMap = get(boost::edge_weight_t(), m_graph);
  // std::pair<EdgeIter, EdgeIter> edgePair;
  // for (edgePair = boost::edges(m_graph); edgePair.first != edgePair.second; ++edgePair.first) {
  //   std::cout << *edgePair.first << " " << edgeWeightMap[*edgePair.first] << std::endl;
  // }
}

std::pair<uint8_t, uint> DynamicRoadmapBoost::getIndexFromHierarchicalConfiguration(const std::vector<uint8_t>& k) {
  uint i = k[0];
  uint8_t n = k.size();

  for (int j = 1; j < n; j++) {
    i = (i - 1) * m_K[j] + k[j];
  }

  return std::make_pair(n, i);
}

std::vector<uint8_t> DynamicRoadmapBoost::getHierarchicalConfigurationFromIndex(uint i) {
  std::vector<uint8_t> k(k_dof, 0);
  for (int j = k_dof - 1; j > -1; j--) {
    auto div_res = std::div((int)i, (int)m_K[j]);
    i = div_res.quot;
    k[j] = div_res.rem;

    if (i != 0 && k[j] == 0) {
      k[j] = m_K[j];
    } else {
      i = i + 1;
    }
  }

  return k;
}

std::vector<uint8_t> DynamicRoadmapBoost::getHierarchicalConfigurationFromIndex(const std::pair<uint8_t, uint>& n_i) {
  uint8_t n = n_i.first;
  uint i = n_i.second;

  std::vector<uint8_t> k(n, 0);
  for (int j = n - 1; j > -1; j--) {
    auto div_res = std::div((int)i, (int)m_K[j]);
    i = div_res.quot;
    k[j] = div_res.rem;

    if (i != 0 && k[j] == 0) {
      k[j] = m_K[j];
    } else {
      i = i + 1;
    }
  }

  return k;
}

std::vector<std::pair<uint8_t, uint>> DynamicRoadmapBoost::findNeighbors(const std::pair<uint8_t, uint>& node) {
  // storage for neighbors
  std::vector<std::pair<uint8_t, uint>> neighbors;

  // hierarchical configuration of the node
  auto k = getHierarchicalConfigurationFromIndex(node);

  // add neighbors by checking for adjacent indices at ever level
  for (uint i = 0; i < k.size(); i++) {
    // any index other than the greatest
    std::vector<uint8_t> new_k = k;
    if (k[i] % m_K[i] != 0) {
      new_k[i] = k[i] + 1;
      neighbors.push_back(getIndexFromHierarchicalConfiguration(new_k));
    }
    // any index other than the smallest
    if (k[i] % m_K[i] != 1) {
      new_k[i] = k[i] - 1;
      neighbors.push_back(getIndexFromHierarchicalConfiguration(new_k));
    }
  }

  return neighbors;
}

int DynamicRoadmapBoost::solve(uint start, uint goal, double subOptimalGain,
                               const std::unordered_set<uint>& occupiedVertices, std::vector<uint>& path) {
  path.clear();

  auto start_remove_vertices = std::chrono::high_resolution_clock::now();

  UnoccupiedFilter filter{.g = &m_graph, .collidingVertices = &occupiedVertices};
  FilteredGraph filteredGraph(m_graph, filter, filter);

  std::cout << "Filtering the graph took: "
            << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() -
                                                                     start_remove_vertices)
                   .count()
            << " us" << std::endl;

  // print_graph(filteredGraph);

  boost::vector_property_map<Vertex> prev(boost::num_vertices(filteredGraph));

  Vertex vertexStart;
  Vertex vertexGoal;

  auto start_it = m_vertices.find(start);
  auto goal_it = m_vertices.find(goal);

  if ((start_it != m_vertices.end()) && (goal_it != m_vertices.end())) {
    vertexStart = start_it->second;
    vertexGoal = goal_it->second;
  } else {
    std::cout << "Start/end vertex not found!" << std::endl;
    return -1;
  }

  int num = 0;
  double time = 0;
  auto startConfiguration = getHierarchicalConfigurationFromIndex(m_graph[vertexStart].index);
  auto goalConfiguration = getHierarchicalConfigurationFromIndex(m_graph[vertexGoal].index);

  std::cout << "Start = [";
  for (const auto& K : startConfiguration) {
    std::cout << (int)K << ", ";
  }
  std::cout << '\b' << '\b' << "]" << std::endl;
  std::cout << "End = [";
  for (const auto& K : goalConfiguration) {
    std::cout << (int)K << ", ";
  }
  std::cout << '\b' << '\b' << "]" << std::endl;

  auto heuristicCostToGo = [this, goalConfiguration, &subOptimalGain, &num, &time](Vertex v) {
    auto now = std::chrono::high_resolution_clock::now();
    auto currConfiguration = getHierarchicalConfigurationFromIndex(m_graph[v].index);

    float sumSqrCost = 0;
    for (unsigned int i = 0; i < goalConfiguration.size(); i++) {
      if (currConfiguration[i] != goalConfiguration[i]) {
        sumSqrCost += std::pow(goalConfiguration[i] - currConfiguration[i], 2);
      }
    }
    num += 1;

    time +=
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - now).count() *
        0.001;
    return subOptimalGain * sqrt(sumSqrCost);
  };

  auto start_a_star = std::chrono::high_resolution_clock::now();
  try {
    boost::astar_search(filteredGraph, vertexStart, heuristicCostToGo,
                        boost::predecessor_map(prev).visitor(AStarGoalVisitor<Vertex>(vertexGoal)));
  } catch (AStarFoundGoal&) {
  }

  if (prev[vertexGoal] == vertexGoal) {
    std::cout << "Could not find solution path" << std::endl;
    return -1;
  }
  std::cout << "Solving A* took: "
            << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() -
                                                                     start_a_star)
                   .count()
            << " us" << std::endl;
  std::cout << "Visited " << num << " vertices" << std::endl;
  std::cout << "Spent a cumulated " << time << " us in the heuristic cost estimation" << std::endl;
  for (Vertex pos = vertexGoal; prev[pos] != pos; pos = prev[pos]) path.push_back(filteredGraph[pos].index);
  path.push_back(filteredGraph[vertexStart].index);

  return path.size();
}

bool DynamicRoadmapBoost::isConfigurationValid(const std::vector<uint>& configuration) {
  // Check if the configuration is in self-collision, or is in collision with
  // a static obstacle
  // TODO
  return true;
}