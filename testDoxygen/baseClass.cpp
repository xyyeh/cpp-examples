#include "baseClass.hpp"

#include <iostream>

namespace scene_graph {

void StateSolverBase::privateMethod(unsigned int input) {
  std::cout << "In " << __FUNCTION__ << ", value passed in " << input << std::endl;
}

void StateSolverBase::setState(const Eigen::Ref<const Eigen::VectorXd>& joint_values) {
  std::cout << "In " << __FUNCTION__ << std::endl;
  std::cout << joint_values.transpose() << std::endl;
}

void StateSolverBase::setStateSize(unsigned int size) { m_state.resize(size); }

}  // namespace scene_graph
