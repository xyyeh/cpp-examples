#include "Library/Library.hpp"

#include "Problem.hpp"

void Library::initialize(unsigned int nWaypoints, unsigned int nDof) {
  // assign
  m_numWayPoints = nWaypoints;
  m_numDof = nDof;

  // allocate memory
  m_pS.resize(m_numWayPoints, m_numDof);

  m_sNorm.resize(m_numWayPoints);

  m_problem = new Problem(m_numDof);
}

void Library::interpolate() {
  // compute norm of segments
  for (unsigned int i = 0; i < m_numWayPoints; i++) {
    m_sNorm(i) = m_pS.row(i).norm();
  }
}

Library::Library() { std::cout << "Construct library" << std::endl; }

Library::~Library() {
  delete m_problem;
  std::cout << "Destruct library" << std::endl;
}