//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Thermoelectric_InterfaceBC.h"

// MOOSE includes
#include "AddVariableAction.h"
#include "Assembly.h"
#include "MooseMesh.h"
#include "MooseVariable.h"
#include "PenetrationLocator.h"
#include "SystemBase.h"

#include "libmesh/string_to_enum.h"

registerMooseObject("lizardApp", Thermoelectric_InterfaceBC);

defineLegacyParams(Thermoelectric_InterfaceBC);

InputParameters
Thermoelectric_InterfaceBC::validParams()
{
  InputParameters params = DirichletBCBase::validParams();
  params.addRequiredParam<Real>("value_1", "Value 1 of the BC");
  params.declareControllable("value_1");
  params.addRequiredParam<Real>("value_2", "Value of the BC");
  params.declareControllable("value_2");
  params.addRequiredParam<Real>("value_3", "Value of the BC");
  params.declareControllable("value_3");
  // params.addParam<MaterialPropertyName>("seebeck_coefficient_interface","Seebeck coefficent for
  // the interface");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addClassDescription("Imposes the essential boundary condition $u=g$, where $g$ "
                             "is a constant, controllable value.");
  return params;
}

Thermoelectric_InterfaceBC::Thermoelectric_InterfaceBC(const InputParameters & parameters)
  : DirichletBCBase(parameters),

    _value_1(getParam<Real>("value_1")),
    _value_2(getParam<Real>("value_2")),
    _value_3(getParam<Real>("value_3")),
    // _seebeck_coefficient_interface(getMaterialProperty<Real>("seebeck_coefficient_interface")),
    // _seebeck_coefficient_interface(getMaterialProperty<Real>("seebeck_coefficient_interface" +
    // getParam<std::string>("appended_property_name"))),
    // _seebeck_coefficient_interface_dT(getMaterialProperty<Real>("seebeck_coefficient_interface" +
    // getParam<std::string>("appended_property_name") + "_dT")),
    _temperature_var(coupled("temperature")),
    _temperature(coupledValue("temperature"))
{
}

Real
Thermoelectric_InterfaceBC::computeQpValue()
{
  return 0;
}
