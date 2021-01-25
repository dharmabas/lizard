//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Thermoelectric_InterfaceBC.h"

registerMooseObject("lizardApp", Thermoelectric_InterfaceBC);

InputParameters
Thermoelectric_InterfaceBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addClassDescription(
      "Applies a heat source that is generated as a result of two different seebeck coefficients");
  params.addRequiredRangeCheckedParam<unsigned int>(
      "component", "component<3", "The component for the heat flux");
  params.addRequiredCoupledVar("potential_E_int", "electrical potential");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addParam<MaterialPropertyName>("seebeck_coefficient_1", "seebeck_coefficient_1");
  params.addParam<MaterialPropertyName>("seebeck_coefficient_2", "seebeck_coefficient_2");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  params.set<bool>("use_displaced_mesh") = true;
  return params;
}

Thermoelectric_InterfaceBC::Thermoelectric_InterfaceBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _component(getParam<unsigned int>("component")),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _temperature_var(coupled("temperature")),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _seebeck_coefficient_1(getMaterialProperty<Real>("seebeck_coefficient_1")),
    _seebeck_coefficient_2(getMaterialProperty<Real>("seebeck_coefficient_2")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
Thermoelectric_InterfaceBC::computeQpResidual()
{
  return _u[_qp] - 0;
  // return _u[_qp] - (_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
  // _temperature[_qp]; return (_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
  // _temperature[_qp] * _potential_E_int_grad[_qp](_component) * _normals[_qp](_component);
  // return (_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) * _temperature[_qp] *
  // _potential_E_int_grad[_qp](_component) * _normals[_qp](_component) * _test[_i][_qp] *
  // _len_scale; return (_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) *
  // _temperature[_qp] * _potential_E_int_grad[_qp](_component) * _normals[_qp](_component) *
  // _test[_i][_qp];
}
