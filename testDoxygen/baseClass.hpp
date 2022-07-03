
#ifndef BASE_CLASS_HPP
#define BASE_CLASS_HPP

#include "abstractBaseClass.hpp"

// third party
#include <Eigen/Eigen>

namespace scene_graph {

class StateSolverBase : public StateSolver {
private:
  void privateMethod(unsigned int input) override;

public:
  void setState(const Eigen::Ref<const Eigen::VectorXd>& joint_values) override;

  /**
   * @brief Sets the state size
   * @param[in] size Size of state
   */
  void setStateSize(unsigned int size);
};

}  // namespace scene_graph

#endif  // BASE_CLASS_HPP