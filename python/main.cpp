#include <eigenpy/eigenpy.hpp>

#include "sobec/python.hpp"

BOOST_PYTHON_MODULE(sobec_pywrap) {
  sobec::python::exposeResidualVelCollision();
  sobec::python::exposeResidualCoMVelocity();
  sobec::python::exposeResidualCenterOfPressure();
  sobec::python::exposeResidualFlyHigh();
  sobec::python::exposeActivationQuadRef();
}
