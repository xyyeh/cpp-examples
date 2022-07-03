
#ifndef ABSTRACT_BASE_CLASS_HPP
#define ABSTRACT_BASE_CLASS_HPP
#include <memory>

// third party
#include <Eigen/Eigen>

namespace scene_graph {

class StateSolver {
protected:
  /// State
  Eigen::VectorXd m_state;

  /**
   * @brief Private method
   * @param[in] input Input
   */
  virtual void privateMethod(unsigned int input) = 0;

public:
  using Ptr = std::shared_ptr<StateSolver>;
  using ConstPtr = std::shared_ptr<const StateSolver>;
  using UPtr = std::unique_ptr<StateSolver>;
  using ConstUPtr = std::unique_ptr<const StateSolver>;

  StateSolver() = default;
  virtual ~StateSolver() = default;
  StateSolver(const StateSolver&) = default;
  StateSolver& operator=(const StateSolver&) = default;
  StateSolver(StateSolver&&) = default;
  StateSolver& operator=(StateSolver&&) = default;

  /**
   * @brief Set the current state of the solver
   * @details This must be the same size and order as what is returned by getJointNames
   * @param joint_values The joint values
   */
  virtual void setState(const Eigen::Ref<const Eigen::VectorXd>& joint_values) = 0;

  /**
   * @brief Get the state of the solver given the joint values
   * @details This must be the same size and order as what is returned by getJointNames
   * @param joint_values The joint values
   */
  virtual Eigen::VectorXd getState(const Eigen::Ref<const Eigen::VectorXd>& joint_values) const = 0;
};

}  // namespace scene_graph

#endif  // ABSTRACT_BASE_CLASS_HPP