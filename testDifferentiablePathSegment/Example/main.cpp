#include <DifferentiablePathSegment/DifferentiablePathSegment.hpp>

int main() {
    DifferentiablePathSegment ds;

    unsigned int dof = 7;

    Eigen::VectorXd vec(dof);

    ds.initialize(10, dof);
    ds.insertNode(0, vec);
}