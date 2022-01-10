#include "DifferentiablePathSegment/DifferentiablePathSegment.hpp"

#include <cmath>

#include "Utils.hpp"

constexpr double kFiniteDiffEps = 1e-4;
constexpr double kTerminalEps = 1e-4;

unsigned int DifferentiablePathSegment::locateSegment(double s) {
  ASSERT(((s >= 0) && (s <= m_sCumulativeSum(m_numWayPoints - 1))), "s is not within bounds");

  // find the lower index of the segment we are in
  unsigned int k = 0;
  for (unsigned int i = 1; i < m_numWayPoints; i++) {
    if ((s > m_sCumulativeSum(i - 1)) && (s < m_sCumulativeSum(i))) {
      k = i - 1;
      break;
    }
  }

  return k;
}

void DifferentiablePathSegment::initialize(unsigned int nWaypoints, unsigned int nDof) {
  // assign
  m_numWayPoints = nWaypoints;
  m_numDof = nDof;

  // allocate memory
  m_pS.resize(m_numWayPoints, m_numDof);
  m_sNorm.resize(m_numWayPoints);
  m_sCumulativeSum.resize(m_numWayPoints);
  m_qDifference.resize(m_numDof);

  // zero
  m_sNorm.setZero();
  m_sCumulativeSum.setZero();
}

void DifferentiablePathSegment::pathSetup() {
  // compute norm and cumsum of segments
  for (unsigned int i = 1; i < m_numWayPoints; i++) {
    m_sNorm(i) = (m_pS.row(i) - m_pS.row(i - 1)).norm();
    m_sCumulativeSum(i) = m_sNorm(i) + m_sCumulativeSum(i - 1);
  }
}

void DifferentiablePathSegment::insertNode(unsigned int i, const Eigen::VectorXd& q) { m_pS.row(i) = q; }

void DifferentiablePathSegment::evaluatePs(double s, Eigen::VectorXd& ps) {
  ASSERT(ps.size() == m_numDof, "size of argument ps is not correct");

  unsigned int k = locateSegment(s);

  m_qDifference.noalias() = m_pS.row(k + 1) - m_pS.row(k);
  ps.noalias() = m_pS.row(k).transpose() + ((s - m_sCumulativeSum(k)) / m_sNorm(k + 1)) * m_qDifference;
}

void DifferentiablePathSegment::evaluateDpds(double s, Eigen::VectorXd& dpds) {
  ASSERT(dpds.size() == m_numDof, "size of argument dpds is not correct");

  Eigen::VectorXd pMinusEps(m_numDof);
  Eigen::VectorXd pPlusEps(m_numDof);

  double sMinusEps = std::min(0.0, s - kFiniteDiffEps);
  double sPlusEps = std::max(s + kFiniteDiffEps, m_sCumulativeSum(m_numWayPoints - 1));

  evaluatePs(sMinusEps, pMinusEps);
  evaluatePs(sPlusEps, pPlusEps);

  dpds.noalias() = (1.0 / (sPlusEps - sMinusEps)) * (pPlusEps - pMinusEps);
}

double DifferentiablePathSegment::evaluatePhis(double s) {
  auto end = s - m_sCumulativeSum(m_numDof - 1);
  auto absEnd = std::abs(end);

  if (absEnd > kTerminalEps) {
    return absEnd;
  } else {
    return absEnd * absEnd / kTerminalEps;
  }
}

double DifferentiablePathSegment::evaluateDphis(double s) {
  auto end = s - m_sCumulativeSum(m_numDof - 1);
  auto absEnd = std::abs(end);

  if (absEnd > kTerminalEps) {
    return end > 0 ? 1.0 : -1.0;
  } else {
    return 2 * end / kTerminalEps;
  }
}

std::ostream& operator<<(std::ostream& os, const DifferentiablePathSegment& ds) {
  // clang-format off
  os << "Nodes: \n" << ds.m_pS 
     << "\nNorm: \n" << ds.m_sNorm
     << "\nCumSum: \n" << ds.m_sCumulativeSum;

  // clang-format on

  return os;
}