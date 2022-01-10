#include <DifferentiablePathSegment/DifferentiablePathSegment.hpp>

int main() {
  DifferentiablePathSegment ds;

  unsigned int dof = 7;
  unsigned int waypts = 3;

  Eigen::VectorXd q(dof);
  ds.initialize(waypts, dof);

  // insert nodes
  q << 1, 2, 3, 4, 5, 6, 7;
  ds.insertNode(0, q);
  q << 1, 3, 5, 7, 9, 10, 12;
  ds.insertNode(1, q);
  q << 1, 2, 3, 2, 5, 3, 7;
  ds.insertNode(2, q);

  // setup path
  ds.pathSetup();

  std::cout << ds << std::endl;

  Eigen::VectorXd psEval(dof);
  ds.evaluatePs(10, psEval);
  std::cout << psEval.transpose() << std::endl;

  Eigen::VectorXd dpdsEval(dof);
  ds.evaluateDpds(10, dpdsEval);
  std::cout << dpdsEval.transpose() << std::endl;
}