//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ConjugateHeatTransfer_lizard.h"

#include "metaphysicl/raw_type.h"

using MetaPhysicL::raw_value;

registerMooseObject("HeatConductionApp", ConjugateHeatTransfer_lizard);

InputParameters
ConjugateHeatTransfer_lizard::validParams()
{
  InputParameters params = InterfaceKernel::validParams();
  params.addRequiredCoupledVar("temperature",
                               "The temperature. It is not always identical to neighbor_var, "
                               "e.g. when the heat equation is solved for internal energy");
  params.addParam<MaterialPropertyName>(
      "seebeck_coefficient_1",
      "Seebeck coefficient 1",
      "Property name of the Seebeck coefficient 1 material property");
  params.addParam<MaterialPropertyName>(
      "seebeck_coefficient_2",
      "Seebeck coefficient 2",
      "Property name of the Seebeck coefficient 2 material property");
  params.addRequiredCoupledVar("potential_E_int", "electric potential");
  params.addParam<MaterialPropertyName>(
      "electrical_conductivity",
      "Electrical Conductivity",
      "Property name of the electrical conductivity material property");
  params.addClassDescription(
      "This InterfaceKernel models conjugate heat transfer. Fluid side must "
      "be primary side and solid side must be secondary side. T_fluid is provided in case that "
      "variable "
      "(== fluid energy variable) is not temperature but e.g. internal energy.");
  return params;
}

ConjugateHeatTransfer_lizard::ConjugateHeatTransfer_lizard(const InputParameters & parameters)
  : InterfaceKernel(parameters),
    _temperature(coupledValue("temperature")),
    _seebeck_coefficient_1(getMaterialProperty<Real>("seebeck_coefficient_1")),
    _seebeck_coefficient_2(getMaterialProperty<Real>("seebeck_coefficient_2")),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    _apply_element_jacobian(_var.name() == getParam<std::vector<VariableName>>("temperature")[0])
{
}

Real
ConjugateHeatTransfer_lizard::computeQpResidual(Moose::DGResidualType type)
{
  switch (type)
  {
    case Moose::Element:
      return raw_value(_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
             (_temperature[_qp] - _neighbor_value[_qp]) * _test[_i][_qp] *
             _electrical_conductivity[_qp] * _potential_E_int_grad[_qp] * _normals[_qp];

    case Moose::Neighbor:
      return -raw_value(_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
             (_neighbor_value[_qp] - _temperature[_qp]) * _test_neighbor[_i][_qp] *
             _electrical_conductivity[_qp] * _potential_E_int_grad[_qp] * _normals[_qp];

    default:
      return 0.0;
  }
}

Real
ConjugateHeatTransfer_lizard::computeQpJacobian(Moose::DGJacobianType type)
{
  switch (type)
  {
    case Moose::ElementElement:
      return _apply_element_jacobian
                 ? raw_value(_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
                       _phi[_j][_qp] * _test[_i][_qp] * _electrical_conductivity[_qp] *
                       _potential_E_int_grad[_qp] * _normals[_qp]
                 : 0;

    case Moose::NeighborNeighbor:
      return -raw_value(_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
             _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp] * _electrical_conductivity[_qp] *
             _potential_E_int_grad[_qp] * _normals[_qp];

    case Moose::NeighborElement:
      return _apply_element_jacobian
                 ? -raw_value(_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
                       -_phi[_j][_qp] * _test_neighbor[_i][_qp] * _electrical_conductivity[_qp] *
                       _potential_E_int_grad[_qp] * _normals[_qp]
                 : 0;

    case Moose::ElementNeighbor:
      return raw_value(_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
             -_phi_neighbor[_j][_qp] * _test[_i][_qp] * _electrical_conductivity[_qp] *
             _potential_E_int_grad[_qp] * _normals[_qp];

    default:
      return 0.0;
  }
}
