///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2020-2021, LAAS-CNRS, University of Edinburgh
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#include "sobec/contact/contact1d.hpp"

#include <boost/python.hpp>
#include <boost/python/enum.hpp>
#include <eigenpy/eigenpy.hpp>

namespace sobec {
namespace python {
using namespace crocoddyl;
namespace bp = boost::python;

void exposeContact1D() {
  bp::register_ptr_to_python<boost::shared_ptr<sobec::ContactModel1D> >();

  bp::enum_<sobec::Vector3MaskType>("Vector3MaskType")
      .value("x", x)
      .value("y", y)
      .value("z", z)
      .export_values();

  bp::class_<sobec::ContactModel1D, bp::bases<crocoddyl::ContactModel1D> >(
      "ContactModel1D",
      "Rigid 1D contact model.\n\n"
      "It defines a rigid 1D contact model (point contact) based on "
      "acceleration-based holonomic constraints, in the "
      "x, y or z direction.\n"
      "The calc and calcDiff functions compute the contact Jacobian and drift "
      "(holonomic constraint) or\n"
      "the derivatives of the holonomic constraint, respectively.",
      bp::init<boost::shared_ptr<crocoddyl::StateMultibody>,
               pinocchio::FrameIndex, Eigen::Vector3d, std::size_t,
               bp::optional<Eigen::Vector2d, sobec::Vector3MaskType,
                            pinocchio::ReferenceFrame> >(
          bp::args("self", "state", "id", "xref", "nu", "gains", "mask",
                   "type"),
          "Initialize the contact model.\n\n"
          ":param state: state of the multibody system\n"
          ":param id: reference frame id of the contact\n"
          ":param xref: contact position used for the Baumgarte stabilization\n"
          ":param nu: dimension of control vector\n"
          ":param gains: gains of the contact model (default "
          "np.matrix([0.,0.]))\n"
          ":param mask: axis of the contact constraint (default z)\n"
          ":param type: reference type of contact"))
      .def(bp::init<boost::shared_ptr<crocoddyl::StateMultibody>,
                    pinocchio::FrameIndex, Eigen::Vector3d,
                    bp::optional<Eigen::Vector2d, pinocchio::ReferenceFrame> >(
          bp::args("self", "state", "id", "xref", "gains", "type"),
          "Initialize the contact model.\n\n"
          ":param state: state of the multibody system\n"
          ":param id: reference frame id of the contact\n"
          ":param xref: contact position used for the Baumgarte stabilization\n"
          ":param gains: gains of the contact model (default "
          "np.matrix([0.,0.]))\n"
          ":param type: reference type of contact\n"))
      .def("calc", &sobec::ContactModel1D::calc, bp::args("self", "data", "x"),
           "Compute the 1D contact Jacobian and drift.\n\n"
           "The rigid contact model throught acceleration-base holonomic "
           "constraint\n"
           "of the contact frame placement.\n"
           ":param data: contact data\n"
           ":param x: state point (dim. state.nx)")
      .def("calcDiff", &sobec::ContactModel1D::calcDiff,
           bp::args("self", "data", "x"),
           "Compute the derivatives of the 1D contact holonomic constraint.\n\n"
           "The rigid contact model throught acceleration-base holonomic "
           "constraint\n"
           "of the contact frame placement.\n"
           "It assumes that calc has been run first.\n"
           ":param data: cost data\n"
           ":param x: state point (dim. state.nx)")
      .def("updateForce", &sobec::ContactModel1D::updateForce,
           bp::args("self", "data", "force"),
           "Convert the force into a stack of spatial forces.\n\n"
           ":param data: cost data\n"
           ":param force: force vector (dimension 1)")
      .def("createData", &sobec::ContactModel1D::createData,
           bp::with_custodian_and_ward_postcall<0, 2>(),
           bp::args("self", "data"),
           "Create the 1D contact data.\n\n"
           "Each contact model has its own data that needs to be allocated. "
           "This function\n"
           "returns the allocated data for a predefined cost.\n"
           ":param data: Pinocchio data\n"
           ":return contact data.")
      .add_property("reference",
                    bp::make_function(&sobec::ContactModel1D::get_reference,
                                      bp::return_internal_reference<>()),
                    &sobec::ContactModel1D::set_reference,
                    "reference contact translation")
      .add_property(
          "gains",
          bp::make_function(&sobec::ContactModel1D::get_gains,
                            bp::return_value_policy<bp::return_by_value>()),
          "contact gains")
      .add_property(
          "mask",
          bp::make_function(&sobec::ContactModel1D::get_mask,
                            bp::return_value_policy<bp::return_by_value>()),
          &sobec::ContactModel1D::set_mask, "mask")
      .add_property(
          "type",
          bp::make_function(&sobec::ContactModel1D::get_type,
                            bp::return_value_policy<bp::return_by_value>()),
          &sobec::ContactModel1D::set_type, "type");

  bp::register_ptr_to_python<boost::shared_ptr<sobec::ContactData1D> >();

  bp::class_<sobec::ContactData1D, bp::bases<crocoddyl::ContactData1D> >(
      "sobec::ContactData1D", "Data for 1D contact.\n\n",
      bp::init<sobec::ContactModel1D*, pinocchio::Data*>(
          bp::args("self", "model", "data"),
          "Create 1D contact data.\n\n"
          ":param model: 1D contact model\n"
          ":param data: Pinocchio data")[bp::with_custodian_and_ward<
          1, 2, bp::with_custodian_and_ward<1, 3> >()])
      .add_property(
          "v",
          bp::make_getter(&sobec::ContactData1D::v,
                          bp::return_value_policy<bp::return_by_value>()),
          "spatial velocity of the contact body")
      .add_property(
          "a",
          bp::make_getter(&sobec::ContactData1D::a,
                          bp::return_value_policy<bp::return_by_value>()),
          "spatial acceleration of the contact body")
      .add_property("fJf",
                    bp::make_getter(&sobec::ContactData1D::fJf,
                                    bp::return_internal_reference<>()),
                    "local Jacobian of the contact frame")
      .add_property("v_partial_dq",
                    bp::make_getter(&sobec::ContactData1D::v_partial_dq,
                                    bp::return_internal_reference<>()),
                    "Jacobian of the spatial body velocity")
      .add_property("a_partial_dq",
                    bp::make_getter(&sobec::ContactData1D::a_partial_dq,
                                    bp::return_internal_reference<>()),
                    "Jacobian of the spatial body acceleration")
      .add_property("a_partial_dv",
                    bp::make_getter(&sobec::ContactData1D::a_partial_dv,
                                    bp::return_internal_reference<>()),
                    "Jacobian of the spatial body acceleration")
      .add_property("a_partial_da",
                    bp::make_getter(&sobec::ContactData1D::a_partial_da,
                                    bp::return_internal_reference<>()),
                    "Jacobian of the spatial body acceleration")
      .add_property(
          "oRf",
          bp::make_getter(&sobec::ContactData1D::oRf,
                          bp::return_internal_reference<>()),
          "Rotation matrix of the contact body expressed in the world frame");
}

}  // namespace python
}  // namespace sobec
