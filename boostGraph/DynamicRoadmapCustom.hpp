#ifndef DFD05AB0_63B1_4C98_8AD3_D7F98FB697E4
#define DFD05AB0_63B1_4C98_8AD3_D7F98FB697E4

#include <map>
#include <unordered_set>
#include <vector>

class DynamicRoadmapCustom {
private:
  std::pair<uint8_t, uint> getIndexFromHierarchicalConfiguration(const std::vector<uint8_t>& k);
  std::vector<uint8_t> getHierarchicalConfigurationFromIndex(uint i);
  std::vector<uint8_t> getHierarchicalConfigurationFromIndex(const std::pair<uint8_t, uint>& n_i);
  std::vector<std::pair<uint8_t, uint>> findNeighbors(const std::pair<uint8_t, uint>& node);
  bool isConfigurationValid(const std::vector<uint>& configuration);

public:
  DynamicRoadmapCustom();
};

#endif /* DFD05AB0_63B1_4C98_8AD3_D7F98FB697E4 */
