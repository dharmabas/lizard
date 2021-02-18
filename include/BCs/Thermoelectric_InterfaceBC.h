//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "DirichletBCBase.h"

class Thermoelectric_InterfaceBC;

template <>
InputParameters validParams<Thermoelectric_InterfaceBC>();

/**
 * Boundary condition of a Dirichlet type
 *
 * Sets the value in the node
 */
class Thermoelectric_InterfaceBC : public DirichletBCBase
{
public:
  static InputParameters validParams();

  Thermoelectric_InterfaceBC(const InputParameters & parameters);

protected:
  virtual Real computeQpValue() override;

  /// The value for this BC

  const Real & _value_1;
  const Real & _value_2;
  const Real & _value_3;
  // const MaterialProperty<Real> & _seebeck_coefficient_interface;
  // const MaterialProperty<Real> & _seebeck_coefficient_interface_dT;
  // const MaterialProperty<Real> & _seebeck_coefficient_interface;
  const unsigned int _temperature_var;
  const VariableValue & _temperature;
};
