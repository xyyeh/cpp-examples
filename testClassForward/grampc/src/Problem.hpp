#ifndef CC897734_A3B1_44E1_AA0E_762CB04CC288
#define CC897734_A3B1_44E1_AA0E_762CB04CC288

class Problem {
private:
  /* data */
  unsigned int m_dof{0};

public:
  Problem(unsigned int dof);
  ~Problem();

  void init();
};

Problem::Problem(unsigned int dof) { m_dof = dof; }

Problem::~Problem() {}

#endif /* CC897734_A3B1_44E1_AA0E_762CB04CC288 */
