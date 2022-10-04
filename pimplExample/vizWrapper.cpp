// vizWrapper.cpp
#include "vizWrapper.h"

#include <iostream>

class vizWrapper::vizImpl {
public:
  vizImpl() = default;
  virtual ~vizImpl() = default;

  void print() { std::cout << "Count = " << m_count << std::endl; }

  void updateCount() { m_count++; }

private:
  unsigned int m_count{0};
};

////////////////////////////////////////////////////////

vizWrapper::vizWrapper() { m_pimpl = std::make_unique<vizImpl>(); }
vizWrapper::~vizWrapper() = default;

void vizWrapper::print() { m_pimpl->print(); }
void vizWrapper::updateCount() { m_pimpl->updateCount(); }