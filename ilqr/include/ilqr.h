/**
 * @file ilqr.h
 * @author Xiyang Yeh
 * @brief Implementation of "Synthesis and Stabilization of Complex Behaviors
 * through Online Trajectory Optimization"
 * @version 0.1
 * @date 2021-12-12
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef CD272269_9D1B_4EB3_B5BC_BD09E456EF88
#define CD272269_9D1B_4EB3_B5BC_BD09E456EF88

#include <memory>
#include <numeric>

#include "definitions.h"

//////////////////////////// Constants ////////////////////////////

class iLQR {
private:
  /** time interval */
  double m_dt{0};

  /** initial state */
  VecXd m_x0;

  /** Q matrices */
  MatXd m_Qx;  // (5a)
  MatXd m_Qu;  // (5b)
  MatXd m_Qxx; // (5c)
  MatXd m_Quu; // (5d)
  MatXd m_Qux; // (5e)

  /** Gain vector/matrix */
  VecXd m_ki; // gain vector
  MatXd m_Ki; // gain matrix

  /** State trajectory */
  VecOfVecXd m_xs;

  /** Input trajectory */
  VecOfVecXd m_us;

  VecOfVecXd m_ls;
  VecOfMatXd m_Ls;

  /** Loss function */

  /** States at each cycle */
  MatXd m_controlLimits;
  VecXd m_xCurrent;
  VecXd m_uCurrent;
  double m_cost;

public:
  iLQR(Model *dynPtr double dt) {
    m_model.reset(dynPtr);

    m_Qx.resize(m_model->xDims);
  };
  ~iLQR();
};

iLQR::iLQR(/* args */) {}

iLQR::~iLQR() {}

#endif /* CD272269_9D1B_4EB3_B5BC_BD09E456EF88 */
