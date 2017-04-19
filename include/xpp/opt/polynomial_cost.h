/**
 @file    polynomial_cost.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    May 30, 2016
 @brief   Declaration of ASplineCost, QuadraticSplineCost, SquaredSplineCost
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_OPT_POLYNOMIAL_COST_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_OPT_POLYNOMIAL_COST_H_

#include <Eigen/Dense>
#include <memory>
#include <string>

#include <xpp/matrix_vector.h>
#include <xpp/optimization_variables_container.h>
#include <xpp/opt/constraints/composite.h>

namespace xpp {
namespace opt {

class BaseMotion;

/** @brief Calculates the scalar cost associated to spline coefficients.
  *
  * This class is responsible for getting the current value of the optimization
  * variables from the subject and calculating the scalar cost from these.
  */
class QuadraticPolynomialCost : public Primitive {
public:
  using BaseMotionPtrS = std::shared_ptr<BaseMotion>;
  using OptVarsPtr     = std::shared_ptr<OptimizationVariablesContainer>;

  QuadraticPolynomialCost(const OptVarsPtr&, const MatVec&, double weight);
  virtual ~QuadraticPolynomialCost();

  /**  The cost is calculated as
    *  cost = x^T * M * x   +   v^T * x
    */
  VectorXd GetValues () const override;

private:
  void FillJacobianWithRespectTo(std::string var_set, Jacobian&) const;

  double weight_ = 1.0;
  BaseMotionPtrS com_motion_;
  MatVec matrix_vector_;  ///< a matrix and a vector used to calculate a scalar cost
};

//class SquaredSplineCost : public ASplineCost {
//
//  /**  The cost is calculated as:
//    *  g = M*x + v
//    *  cost = sqrt(g^T*g)
//    */
//  double EvaluateCost () const override;
//  virtual VectorXd EvaluateGradientWrt(std::string var_set) final { assert(false); };
//
//};

} /* namespace zmp */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_OPT_POLYNOMIAL_COST_H_ */