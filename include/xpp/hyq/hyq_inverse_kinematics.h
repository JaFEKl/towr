#ifndef INVERSEKINEMATICS_H_
#define INVERSEKINEMATICS_H_

#include <cmath>
#include <string>
#include <xpp/opt/a_inverse_kinematics.h>

namespace xpp {
namespace hyq {

/** @brief The SL implementation of the inverse kinematics */
class HyqInverseKinematics : public xpp::opt::AInverseKinematics {
public:
	HyqInverseKinematics();
	virtual ~HyqInverseKinematics();

	/** @brief Returns the joint angles to reach for a specific endeffector position
	  *
	  * @param pos_b the 3d position of the endeffector expressed in the base frame
	  * @param ee the number of endeffector that the above position is referring to.
	  * @return the joints angles of the robot
	  */
	JointAngles GetJointAngles(const EEPosition& pos_b, size_t ee) const override;

  JointAngles GetUpperJointLimits(size_t ee) const override;
  JointAngles GetLowerJointLimits(size_t ee) const override;

private:
	bool compute(size_t leg, const EEPosition& x, Eigen::Vector3d& q_bf, int &rc) const;
};

} /* namespace xpp */
} /* namespace hyq */

#endif /* INVERSEKINEMATICS_H_ */