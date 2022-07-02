#include <Eigen/Eigen>
#include <iostream>
#include <vector>

typedef Eigen::Matrix<double, 6, 1> Vec6d;
typedef Eigen::Matrix<double, 7, 1> Vec7d;
typedef Eigen::Matrix<double, 7, 7> Mat7d;

typedef Eigen::VectorXd VecXd;
typedef Eigen::MatrixXd MatXd;

int main() {
  Vec7d testVec;
  std::cout << "testVec = " << testVec.transpose() << std::endl;
  testVec.setZero();
  std::cout << "testVec after setZero = " << testVec.transpose() << std::endl;

  Mat7d testMat;
  std::cout << "testMat = \n" << testMat << std::endl;
  for (unsigned int i = 0; i < testMat.size(); i++) {
    testMat(i) = i;
  }
  std::cout << "testMat after incremental assignment = \n" << testMat << std::endl;

  VecXd vec;
  vec.resize(7);
  std::cout << "vecXd after resize = " << vec.transpose() << std::endl;

  MatXd rowVec;
  rowVec.resize(1, 7);
  rowVec.setZero();
  std::cout << "rowVec after MatXd resize = " << rowVec << std::endl;
  for (unsigned int i = 0; i < rowVec.size(); i++) {
    rowVec(i) = i;
  }
  std::cout << "rowVec after incremental assignment = " << rowVec << std::endl;

  for (int i = 0; i < 4; i++) {
    VecXd a = rowVec * testMat.col(i);
    std::cout << rowVec * testMat.col(i) << std::endl;
    std::cout << a(0) << ", " << a.size() << std::endl;
  }

  // VecXd b = rowVec * testMat;
  // for (int i = 0; i < 4; i++) {
  //   std::cout << b(i) << std::endl;
  // }

  // std::cout << rowVec * testMat.col(0) << std::endl;
  VecXd v;
  v.resize(7);
  std::cout << "v = " << v.transpose() << std::endl;

  std::vector<VecXd> vecOfPaths(2);
  vecOfPaths[0].resize(7);
  std::cout << vecOfPaths[0].size() << std::endl;

  Vec7d v1;
  v1 = v;

  std::cout << "v = " << v.transpose() << std::endl;
  std::cout << "v1 = " << v1.transpose() << std::endl;

  bool test = true;
  const char* ineqEnabledFlag = test ? "on" : "off";
  const char* temp = ineqEnabledFlag;
  std::cout << "temp = " << temp << std::endl;

  v1[2] = 10;
  std::cout << "v1 = " << v1.transpose() << std::endl;

  return 0;
}