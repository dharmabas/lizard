//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Thermoelectric_InterfaceBC.h"

registerMooseObject("MooseApp", Thermoelectric_InterfaceBC);

defineLegacyParams(Thermoelectric_InterfaceBC);

InputParameters
Thermoelectric_InterfaceBC::validParams()
{
  InputParameters params = DirichletBCBase::validParams();
  params.addRequiredParam<Real>("value_1", "Value 1 of the BC");
  params.declareControllable("value_1");
  params.addRequiredParam<Real>("value_2", "Value of the BC");
  params.declareControllable("value_2");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addClassDescription("Imposes the essential boundary condition $u=g$, where $g$ "
                             "is a constant, controllable value.");
  return params;
}

Thermoelectric_InterfaceBC::Thermoelectric_InterfaceBC(const InputParameters & parameters)
  : DirichletBCBase(parameters),

    _value_1(getParam<Real>("value_1")),
    _value_2(getParam<Real>("value_2")),
    _temperature_var(coupled("temperature")),
    _temperature(coupledValue("temperature"))
{
}

Real
Thermoelectric_InterfaceBC::computeQpValue()
{
  return (_value_1 - _value_2) * _temperature[_qp];
}
