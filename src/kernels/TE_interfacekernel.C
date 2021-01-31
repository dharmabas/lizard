//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TE_interfacekernel.h"

// MOOSE
#include "Function.h"

registerMooseObject("lizardApp", TE_interfacekernel);

defineLegacyParams(TE_interfacekernel);

InputParameters
TE_interfacekernel::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("Interface condition for multimaterial TE system");
  params.set<bool>("use_displaced_mesh") = true;
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addRequiredCoupledVar("potential_E_int", "electric potential");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addParam<MaterialPropertyName>(
      "seebeck_coefficient_1", "Property name of the seebeck_coefficient material property 1");
  params.addParam<MaterialPropertyName>(
      "seebeck_coefficient_2", "Property name of the seebeck_coefficient material property 2");
  params.addParam<MaterialPropertyName>(
      "electrical_conductivity",
      "Property name of the electrical_conductivity composite material property (for now)");
  return params;
}

TE_interfacekernel::TE_interfacekernel(const InputParameters & parameters)
  : Kernel(parameters),
    _temperature_var(coupled("temperature")),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _component(getParam<unsigned int>("component")),
    _seebeck_coefficient_1(getMaterialProperty<Real>("seebeck_coefficient_1")),
    _seebeck_coefficient_2(getMaterialProperty<Real>("seebeck_coefficient_2")),
    _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity"))
{
}

Real
TE_interfacekernel::computeQpResidual()
{
  return _u[_qp] - (_seebeck_coefficient_1[_qp] - _seebeck_coefficient_2[_qp]) * _temperature[_qp] *
                       _electrical_conductivity[_qp] * _potential_E_int_grad[_qp](_component) *
                       _test[_i][_qp];
}
