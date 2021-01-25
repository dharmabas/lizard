//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TE_InterfaceBC.h"

registerMooseObject("MooseApp", TE_InterfaceBC);

defineLegacyParams(TE_InterfaceBC);

InputParameters
TE_InterfaceBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  // InputParameters params = DirichletBCBase::validParams();
  params.addRequiredParam<Real>("value", "Value of the BC");
  params.declareControllable("value");
  params.addRequiredRangeCheckedParam<unsigned int>(
      "component", "component<3", "The component for the heat flux");
  params.addRequiredCoupledVar("potential_E_int", "electrical potential");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addParam<MaterialPropertyName>("seebeck_coefficient_1", "seebeck_coefficient_1");
  params.addParam<MaterialPropertyName>("seebeck_coefficient_2", "seebeck_coefficient_2");
  params.addParam<MaterialPropertyName>("electrical_conductivity_1", "electrical_conductivity_1");
  params.addParam<MaterialPropertyName>("electrical_conductivity_2", "electrical_conductivity_2");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  params.set<bool>("use_displaced_mesh") = true;
  return params;
}

TE_InterfaceBC::TE_InterfaceBC(const InputParameters & parameters)
  : DirichletBCBase(parameters),
    _value(getParam<Real>("value")),
    _component(getParam<unsigned int>("component")),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _temperature_var(coupled("temperature")),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _seebeck_coefficient_1(getParam<Real>("seebeck_coefficient_1")),
    _seebeck_coefficient_2(getParam<Real>("seebeck_coefficient_2")),
    _electrical_conductivity_1(getParam<Real>("electrical_conductivity_1")),
    _electrical_conductivity_2(getParam<Real>("electrical_conductivity_2")),
    // _seebeck_coefficient_1(getMaterialProperty<Real>("seebeck_coefficient_1")),
    // _seebeck_coefficient_2(getMaterialProperty<Real>("seebeck_coefficient_2")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
TE_InterfaceBC::computeQpValue()
{
  return (_seebeck_coefficient_1 - _seebeck_coefficient_2) * _temperature[_qp] *
         _potential_E_int_grad[_qp](_component) * 0.5 *
         (_electrical_conductivity_1 + _electrical_conductivity_2);
}
