#ifndef FDA7ED16_E8A3_4AD9_83BA_4AF3225B5AD8
#define FDA7ED16_E8A3_4AD9_83BA_4AF3225B5AD8

#include <Eigen/Dense>

class DifferentiablePathSegment {
private:
  /** p(s) */
  Eigen::MatrixXd m_pS;

  Eigen::VectorXd m_sNorm;

  unsigned int m_numWayPoints = 0;
  unsigned int m_numDof = 0;

public:
  DifferentiablePathSegment() = default;
  virtual ~DifferentiablePathSegment(){};

  /**
   * @brief Initialize dimensions of path vector
   *
   * @param[in] dof Number of degrees of freedom
   */
  void initialize(unsigned int nWaypoints, unsigned int nDof);

  void interpolate();

  // void insertSegmentNode(const VectorXd )

  unsigned int getSg() { return m_pS.size(); }
};
#endif /* FDA7ED16_E8A3_4AD9_83BA_4AF3225B5AD8 */
