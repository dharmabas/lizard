// //* This file is part of the MOOSE framework
// //* https://www.mooseframework.org
// //*
// //* All rights reserved, see COPYRIGHT for full restrictions
// //* https://github.com/idaholab/moose/blob/master/COPYRIGHT
// //*
// //* Licensed under LGPL 2.1, please see LICENSE for details
// //* https://www.gnu.org/licenses/lgpl-2.1.html
//
// #include "TE_Interface_HeatTransfer.h"
//
// #include "metaphysicl/raw_type.h"
//
// using MetaPhysicL::raw_value;
//
// registerMooseObject("HeatConductionApp", TE_Interface_HeatTransfer);
//
// InputParameters
// TE_Interface_HeatTransfer::validParams()
// {
//   params.addClassDescription("Calculates a residual contribution due to nabla squared Phi = 0");
//   params.addRequiredCoupledVar("temperature", "temperature");
//   params.addRequiredCoupledVar("potential_E_int", "electric potential");
//   params.addRequiredParam<unsigned int>("component",
//                                         "An integer corresponding to the direction the variable "
//                                         "this kernel acts in. (0 for x, 1 for y, 2 for z)");
//   params.addRequiredParam<MaterialPropertyName>(
//       "electrical_conductivity",
//       "Electrical Conductivity",
//       "Property name of the electrical conductivity material property");
//   params.addRequiredParam<MaterialPropertyName>("electrical_conductivity","Electrical
//   Conductivity","Property name of the electrical conductivity material property");
//   params.addRequiredParam<MaterialPropertyName>("seebeck_coefficient_1","Seebeck coefficient
//   1","Property name of the Seebeck coefficient 1 material property");
//   params.addRequiredParam<MaterialPropertyName>("seebeck_coefficient_2","Seebeck coefficient
//   2","Property name of the Seebeck coefficient 2 material property");
//   // params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
// }
//
// TE_Interface_HeatTransfer::TE_Interface_HeatTransfer(const InputParameters & parameters)
//   : InterfaceKernel(parameters),
//   _temperature_var(coupled("temperature")),
//   _temperature(coupledValue("temperature")),
//   _temperature_grad(coupledGradient("temperature")),
//   _potential_E_int_var(coupled("potential_E_int")),
//   _potential_E_int(coupledValue("potential_E_int")),
//   _potential_E_int_grad(coupledGradient("potential_E_int")),
//   _component(getParam<unsigned int>("component")),
//   _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
//   _seebeck_coefficient_1(getMaterialProperty<Real>("seebeck_coefficient_1")),
//   _seebeck_coefficient_2(getMaterialProperty<Real>("seebeck_coefficient_2")),
//   // _len_scale(getParam<Real>("len_scale"))
// {
// }
//
// Real
// TE_Interface_HeatTransfer::computeQpResidual(Moose::DGResidualType type)
// {
//   switch (type)
//   {
//     case Moose::Element:
//       return raw_value(_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
//       (_temperature[_qp] - _neighbor_value[_qp]) * _test[_i][_qp] * _electrical_conductivity[_qp]
//       * _potential_E_int_grad[_qp](_component);
//
//     case Moose::Neighbor:
//       return raw_value(_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
//       (_neighbor_value[_qp] - _temperature[_qp]) * _test_neighbor[_i][_qp] *
//       _electrical_conductivity[_qp] * _potential_E_int_grad[_qp](_component);
//
//     default:
//       return 0.0;
//   }
// }
//
// Real
// TE_Interface_HeatTransfer::computeQpJacobian(Moose::DGJacobianType type)
// {
//   switch (type)
//   {
//     case Moose::ElementElement:
//       return _apply_element_jacobian ? raw_value(_seebeck_coefficient_1[_qp] -
//       _seebeck_coefficient_2[_qp]) * _phi[_j][_qp] * _test[_i][_qp] *
//       _electrical_conductivity[_qp] * _potential_E_int_grad[_qp](_component) : 0;
//
//     case Moose::NeighborNeighbor:
//       return raw_value(_h[_qp]) * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
//
//     case Moose::NeighborElement:
//       return _apply_element_jacobian ? raw_value(_seebeck_coefficient_1[_qp] -
//       _seebeck_coefficient_2[_qp]) * -_phi[_j][_qp] * _test_neighbor[_i][_qp] *
//       _electrical_conductivity[_qp] * _potential_E_int_grad[_qp](_component)
//                                      : 0;
//
//     case Moose::ElementNeighbor:
//       return raw_value(_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
//       -_phi_neighbor[_j][_qp] * _test[_i][_qp] * _electrical_conductivity[_qp] *
//       _potential_E_int_grad[_qp](_component);
//
//     default:
//       return 0.0;
//   }
// }
