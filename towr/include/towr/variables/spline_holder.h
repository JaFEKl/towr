/******************************************************************************
Copyright (c) 2018, Alexander W. Winkler. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#ifndef TOWR_TOWR_INCLUDE_TOWR_VARIABLES_SPLINE_HOLDER_H_
#define TOWR_TOWR_INCLUDE_TOWR_VARIABLES_SPLINE_HOLDER_H_

#include "phase_nodes.h"
#include "phase_durations.h"
#include "node_spline.h"
#include "nodes.h"

namespace towr {

/**
 * @brief Holds pointers to fully constructed splines, that are linked to the
 *        optimization variables.
 *
 * This is independent from whether they are added as optimization variables.
 *
 * @ingroup Variables
 */
struct SplineHolder {
  /**
   * @brief Fully initializes this object.
   * @param base_lin  The nodes describing the base linear motion.
   * @param base_ang  The nodes describing the base angular motion.
   * @param base_poly_durations The durations of each base polynomial.
   * @param ee_motion The nodes describing the endeffector motions.
   * @param ee_force  The nodes describing the endeffector forces.
   * @param phase_durations  The phase durations of each endeffector.
   * @param ee_durations_change  True if the ee durations are optimized over.
   */
  SplineHolder (Nodes::Ptr base_lin,
                Nodes::Ptr base_ang,
                const std::vector<double>& base_poly_durations,
                std::vector<PhaseNodes::Ptr> ee_motion,
                std::vector<PhaseNodes::Ptr> ee_force,
                std::vector<PhaseDurations::Ptr> phase_durations,
                bool ee_durations_change);

  SplineHolder () = default;

  NodeSpline::Ptr base_linear_;
  NodeSpline::Ptr base_angular_;

  std::vector<NodeSpline::Ptr> ee_motion_;
  std::vector<NodeSpline::Ptr> ee_force_;
  std::vector<PhaseDurations::Ptr> phase_durations_;
};

} /* namespace towr */

#endif /* TOWR_TOWR_INCLUDE_TOWR_VARIABLES_SPLINE_HOLDER_H_ */
