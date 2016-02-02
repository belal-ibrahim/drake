#include <Eigen/Core>
#include "drake/util/mexify.h"
#include "drake/util/standardMexConversions.h"
#include "drake/util/drakeGeometryUtil.h"
#include "drake/util/makeFunction.h"
#include "drake/core/Gradient.h"

using namespace std;
using namespace Eigen;
using namespace Drake;

pair<Vector3d, typename Gradient<Vector3d, 3>::type> quat2expmapWithGradient(const MatrixBase<Map<const Vector3d>> &expmap) {
  auto expmap_autodiff = initializeAutoDiff(expmap);
  auto flipped_autodiff = flipExpmap(expmap_autodiff);
  return make_pair(autoDiffToValueMatrix(flipped_autodiff), autoDiffToGradientMatrix(flipped_autodiff));
}

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
  auto func_double = make_function(&flipExpmap<Map<const Vector3d>>);
  auto func_gradient = make_function(&quat2expmapWithGradient);
  mexTryToCallFunctions(nlhs, plhs, nrhs, prhs, true, func_double, func_gradient);
}
