#ifndef FDA7ED16_E8A3_4AD9_83BA_4AF3225B5AD8
#define FDA7ED16_E8A3_4AD9_83BA_4AF3225B5AD8

#include <Eigen/Dense>
#include <iostream>

class DifferentiablePathSegment {
private:
  /** p(s) */
  Eigen::MatrixXd m_pS;

  Eigen::VectorXd m_sNorm;
  Eigen::VectorXd m_sCumulativeSum;

  Eigen::VectorXd m_qDifference;

  unsigned int m_numWayPoints = 0;
  unsigned int m_numDof = 0;

  unsigned int locateSegment(double s);

public:
  DifferentiablePathSegment() = default;
  virtual ~DifferentiablePathSegment(){};

  /**
   * @brief Initialize dimensions of path vector
   *
   * @param[in] dof Number of degrees of freedom
   */
  void initialize(unsigned int nWaypoints, unsigned int nDof);

  void insertNode(unsigned int i, const Eigen::VectorXd& q);

  void pathSetup();

  void evaluatePs(double s, Eigen::VectorXd& ps);

  void evaluateDpds(double s, Eigen::VectorXd& dpds);

  double evaluatePhis(double s);

  double evaluateDphis(double s);

  friend std::ostream& operator<<(std::ostream& os, const DifferentiablePathSegment& ds);
};
#endif /* FDA7ED16_E8A3_4AD9_83BA_4AF3225B5AD8 */
