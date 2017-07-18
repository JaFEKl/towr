/**
 @file    range_of_motion_constraint.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Jun 6, 2016
 @brief   Declares various Range of Motion Constraint classes
 */

#ifndef XPP_OPT_INCLUDE_RANGE_OF_MOTION_CONSTRAINT_H_
#define XPP_OPT_INCLUDE_RANGE_OF_MOTION_CONSTRAINT_H_

#include <memory>
#include <string>
#include <vector>

#include <xpp/endeffectors.h>
#include <xpp/opt/angular_state_converter.h>
#include <xpp/opt/bound.h>
#include <xpp/opt/motion_parameters.h>
#include <xpp/state.h>

#include "composite.h"
#include "time_discretization_constraint.h"

namespace xpp {
namespace opt {

class Spline;

/** @brief Constrains the contact to lie in a box around the nominal stance
  *
  * These constraints are necessary to avoid choosing contact locations
  * that are outside the kinematic reach of the robot. The constraint
  * is defined by Cartesian estimates of the reachability of each endeffector.
  *
  * This constraint calculates the position of of the contact expressed in the
  * current CoM frame and constrains it to lie in a box around the nominal/
  * natural contact position for that leg.
  */
class RangeOfMotionBox : public TimeDiscretizationConstraint {
public:
  using PolySplinePtr   = std::shared_ptr<Spline>;
  using VecTimes        = std::vector<double>;
  using MotionParamsPtr = std::shared_ptr<MotionParameters>;

  RangeOfMotionBox(const OptVarsPtr& opt_vars,
                   const MotionParamsPtr& params,
                   const VecTimes& ee_poly_durations,
                   const EndeffectorID& ee);
  virtual ~RangeOfMotionBox();

private:
  void UpdateConstraintAtInstance (double t, int k, VectorXd& g) const override;
  void UpdateBoundsAtInstance (double t, int k, VecBound&) const override;
  virtual void UpdateJacobianAtInstance(double t, int k, Jacobian&, std::string) const override;

  int GetRow(int node, int dimension) const;

  PolySplinePtr base_linear_;
  PolySplinePtr base_angular_;
  PolySplinePtr ee_spline_;

  Vector3d max_deviation_from_nominal_;
  Vector3d nominal_ee_pos_B;
  AngularStateConverter converter_;
};

} /* namespace opt */
} /* namespace xpp */

#endif /* XPP_OPT_INCLUDE_RANGE_OF_MOTION_CONSTRAINT_H_ */
