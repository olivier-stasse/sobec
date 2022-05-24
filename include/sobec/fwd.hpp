///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2019-2021, LAAS-CNRS, University of Edinburgh, INRIA
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#ifndef SOBEC_FWD_HPP_
#define SOBEC_FWD_HPP_

namespace sobec {

// Cost COM-vel
template <typename Scalar>
class ResidualModelCoMVelocityTpl;
template <typename Scalar>
struct ResidualDataCoMVelocityTpl;
typedef ResidualModelCoMVelocityTpl<double> ResidualModelCoMVelocity;
typedef ResidualDataCoMVelocityTpl<double> ResidualDataCoMVelocity;

// Activation quad-ref
template <typename Scalar>
class ActivationModelQuadRefTpl;
typedef ActivationModelQuadRefTpl<double> ActivationModelQuadRef;

// State LPF
template <typename Scalar>
class StateLPFTpl;
typedef StateLPFTpl<double> StateLPF;

// IAM LPF
template <typename Scalar>
class IntegratedActionModelLPFTpl;
typedef IntegratedActionModelLPFTpl<double> IntegratedActionModelLPF;
template <typename Scalar>
class IntegratedActionDataLPFTpl;
typedef IntegratedActionDataLPFTpl<double> IntegratedActionDataLPF;


// contact 3D
template <typename Scalar>
class ContactModel3DTpl;
typedef ContactModel3DTpl<double> ContactModel3D;
template <typename Scalar>
class ContactData3DTpl;
typedef ContactData3DTpl<double> ContactData3D;

// contact 1D
template <typename Scalar>
class ContactModel1DTpl;
typedef ContactModel1DTpl<double> ContactModel1D;
template <typename Scalar>
class ContactData1DTpl;
typedef ContactData1DTpl<double> ContactData1D;

// multiple contacts
template <typename Scalar>
class ContactModelMultipleTpl;
typedef ContactModelMultipleTpl<double> ContactModelMultiple;


// DAM contact fwd dynamics
template <typename Scalar>
class DifferentialActionModelContactFwdDynamicsTpl;
typedef DifferentialActionModelContactFwdDynamicsTpl<double> DifferentialActionModelContactFwdDynamics;

}  // namespace sobec

#endif  // SOBEC_FWD_HPP_
