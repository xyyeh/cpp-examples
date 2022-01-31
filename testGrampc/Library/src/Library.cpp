#include "Library/Library.hpp"

void Library::initialize(unsigned int nWaypoints, unsigned int nDof) {
  // assign
  m_numWayPoints = nWaypoints;
  m_numDof = nDof;

  // allocate memory
  m_pS.resize(m_numWayPoints, m_numDof);

  m_sNorm.resize(m_numWayPoints);
}

void Library::interpolate() {
  // compute norm of segments
  for (unsigned int i = 0; i < m_numWayPoints; i++) {
    m_sNorm(i) = m_pS.row(i).norm();
  }
}