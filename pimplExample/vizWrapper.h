// vizWrapper.h

#include <memory>

class vizWrapper {
public:
  vizWrapper();
  virtual ~vizWrapper();

  void print();
  void updateCount();

private:
  class vizImpl;
  std::unique_ptr<vizImpl> m_pimpl;
};
