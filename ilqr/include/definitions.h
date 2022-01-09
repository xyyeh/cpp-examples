#ifndef A26B718B_A4D4_40EB_86EB_FFC4B7D70E66
#define A26B718B_A4D4_40EB_86EB_FFC4B7D70E66

#include <Eigen/Dense>

// matrices and vectors
typedef Eigen::Vector2d Vec2d;
typedef Eigen::Vector3d Vec3d;
typedef Eigen::Vector4d Vec4d;
typedef Eigen::Matrix<double, 6, 1> Vec6d;
typedef Eigen::Matrix<double, 7, 1> Vec7d;
typedef Eigen::VectorXd VecXd;

typedef Eigen::Matrix2d Mat2d;
typedef Eigen::Matrix3d Mat3d;
typedef Eigen::Matrix4d Mat4d;
typedef Eigen::Matrix<double, 6, 6> Mat6d;
typedef Eigen::Matrix<double, 7, 7> Mat7d;
typedef Eigen::MatrixXd MatXd;

typedef Eigen::Matrix<bool, 8, 1> Vec8b;
typedef Eigen::Matrix<bool, 16, 1> Vec16b;

typedef std::vector<VecXd, Eigen::aligned_allocator<VecXd>> VecOfVecXd;
typedef std::vector<MatXd, Eigen::aligned_allocator<MatXd>> VecOfMatXd;

// quaternions
typedef Eigen::Quaternion<double> Quat;

// angle axis
typedef Eigen::AngleAxis<double> AAxis;

// common macros
#define _degToRad(degrees) (degrees * M_PI / 180.0)
#define _radToDeg(radians) (radians * 180.0 / M_PI)

#endif /* A26B718B_A4D4_40EB_86EB_FFC4B7D70E66 */
