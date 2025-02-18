#include "sobec/fwd.hpp"
// keep this line on top
#include <boost/python.hpp>
#include <boost/python/enum.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <crocoddyl/core/activation-base.hpp>
#include <eigenpy/eigenpy.hpp>
#include <sobec/wbc.hpp>
namespace sobec {
namespace python {
namespace bp = boost::python;

void initialize(WBC &self, const bp::dict &settings,
                const RobotDesigner &designer, const HorizonManager &horizon,
                const Eigen::VectorXd &q0, const Eigen::VectorXd &v0,
                const std::string &actuationCostName) {
  WBCSettings conf;

  conf.horizonSteps = bp::extract<int>(settings["horizonSteps"]);
  conf.totalSteps = bp::extract<int>(settings["totalSteps"]);
  conf.T = bp::extract<int>(settings["T"]);
  conf.TdoubleSupport = bp::extract<int>(settings["TdoubleSupport"]);
  conf.TsingleSupport = bp::extract<int>(settings["TsingleSupport"]);
  conf.Tstep = bp::extract<int>(settings["Tstep"]);
  conf.ddpIteration = bp::extract<int>(settings["ddpIteration"]);
  conf.Dt = bp::extract<double>(settings["Dt"]);
  conf.simu_step = bp::extract<double>(settings["simu_step"]);
  conf.Nc = bp::extract<int>(settings["Nc"]);
  // conf.stepSize = bp::extract<double>(settings["stepSize"]);
  // conf.stepHeight = bp::extract<double>(settings["stepHeight"]);
  // conf.stepDepth = bp::extract<double>(settings["stepDepth"]);

  self.initialize(conf, designer, horizon, q0, v0, actuationCostName);
}

void exposeWBC() {
  bp::class_<WBC>("WBC", bp::init<>())
      .def("initialize", &initialize,
           bp::args("self", "settings", "design", "horizon", "q0", "v0",
                    "actuationCostName"),
           "The posture required here is the full robot posture in the order "
           "of pinicchio")
      .def("shapeState", &WBC::shapeState, bp::args("self", "q", "v"))
      .def("generateWalkigCycle", &WBC::generateWalkigCycle,
           bp::args("self", "modelMaker"))
      .def("iterate", &WBC::iterate,
           (bp::arg("self"), bp::arg("iteration"), bp::arg("q_current"),
            bp::arg("v_current"), bp::arg("is_feasible") = false))
      .def("updateStepCycleTiming", &WBC::updateStepCycleTiming,
           bp::args("self"))
      .def("timeToSolveDDP", &WBC::timeToSolveDDP,
           bp::args("self", "iteration"))
      .def<void (WBC::*)()>("recedeWithCycle", &WBC::recedeWithCycle,
                            bp::args("self"))
      .def<void (WBC::*)(HorizonManager &)>(
          "recedeWithCycle", &WBC::recedeWithCycle, bp::args("self", "cycle"))
      .add_property("x0", &WBC::get_x0, &WBC::set_x0)
      .add_property("walkingCycle", &WBC::get_walkingCycle,
                    &WBC::set_walkingCycle)
      .add_property("standingCycle", &WBC::get_standingCycle,
                    &WBC::set_standingCycle)
      .add_property("horizon", &WBC::get_horizon, &WBC::set_horizon)
      .add_property("design", &WBC::get_designer, &WBC::set_designer)
      .add_property("landing_LF", &WBC::get_LF_land, &WBC::set_LF_land)
      .add_property("landing_RF", &WBC::get_RF_land, &WBC::set_RF_land)
      .add_property("takingoff_LF", &WBC::get_LF_takeoff, &WBC::set_LF_takeoff)
      .add_property("takingoff_RF", &WBC::get_RF_takeoff, &WBC::set_RF_takeoff);
}
}  // namespace python
}  // namespace sobec
