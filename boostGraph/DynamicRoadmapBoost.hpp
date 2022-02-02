#ifndef DYNAMIC_ROADMAP_
#define DYNAMIC_ROADMAP_

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/astar_search.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

constexpr uint8_t k_dof = 6;

struct AStarFoundGoal {};  // exception for termination

// visitor that terminates when we find the goal
// V is the vertex type
template <typename V>
class AStarGoalVisitor : public boost::default_astar_visitor {
public:
  AStarGoalVisitor(const V& goal) : goal_(goal) {}

  // G is the graph type
  template <typename G>
  void examine_vertex(const V& u, const G& /*unused*/) {
    if (u == goal_) throw AStarFoundGoal();
  }

private:
  V goal_;
};

class DynamicRoadmap {
  /** @brief Property definition for the vertex. */
  struct vertex_info {
    uint index;
  };

  /**
   * @brief The type for a graph.
   * @note http://www.richelbilderbeek.nl/CppBoostAdjacency_list.htm
   */
  using Graph = boost::adjacency_list<boost::hash_setS, boost::vecS, boost::undirectedS, vertex_info,
                                      boost::property<boost::edge_weight_t, float>>;

  /** @brief The type for a vertex in the roadmap. */
  using Vertex = boost::graph_traits<Graph>::vertex_descriptor;

  /** @brief The type for an edge in the roadmap. */
  using Edge = boost::graph_traits<Graph>::edge_descriptor;

  /**
   * @brief Predicate used to filter graph
   */
  struct UnoccupiedFilter {
    bool operator()(const Edge& edge) const { return true; }  // true to keep
    bool operator()(const Vertex& vertex) const {
      bool isVertexColliding = collidingVertices->count((*g)[vertex].index);
      return !isVertexColliding;  // keep all non-colliding vertices
    }

    const Graph* g;
    const std::unordered_set<uint>* collidingVertices;
  };

  /** @brief The type for a filtered graph. */
  using FilteredGraph = boost::filtered_graph<Graph, UnoccupiedFilter, UnoccupiedFilter>;

private:
  std::pair<uint8_t, uint> getIndexFromHierarchicalConfiguration(const std::vector<uint8_t>& k);
  std::vector<uint8_t> getHierarchicalConfigurationFromIndex(uint i);
  std::vector<uint8_t> getHierarchicalConfigurationFromIndex(const std::pair<uint8_t, uint>& n_i);
  std::vector<std::pair<uint8_t, uint>> findNeighbors(const std::pair<uint8_t, uint>& node);
  bool isConfigurationValid(const std::vector<uint>& configuration);

public:
  DynamicRoadmap();

  /** Max indices at every level of hierarchical indices */
  std::vector<uint8_t> m_K;

  /** Map from hierarchical indicies key to vertex */
  std::unordered_map<uint, Vertex> m_vertices;

  /** Graph */
  Graph m_graph;

  /**
   * @brief Solve the path planning problem using AStar search
   *
   * @param[in] start Starting vertex index
   * @param[in] goal Goal vertex index
   * @param[in] subOptimalConstant Scale to over-estimate the cost, resulting in faster search but more sub-optimal
   * solutions
   * @param[in] occupiedVertices Vertices that are occupied by obstacles
   * @param[out] path Vector of path nodes
   * @return -1 if fail, otherwise, return the number of path nodes
   */
  int solve(uint start, uint goal, double subOptimalConstant, const std::unordered_set<uint>& occupiedVertices,
            std::vector<uint>& path);
};

#endif