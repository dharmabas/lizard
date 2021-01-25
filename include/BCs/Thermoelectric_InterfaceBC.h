//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "IntegratedBC.h"

/**
 * Pressure boundary condition using coupled variable to apply pressure in a given direction
 */
class Thermoelectric_InterfaceBC : public IntegratedBC
{
public:
  static InputParameters validParams();

  Thermoelectric_InterfaceBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

  const unsigned int _component;
  const unsigned int _potential_E_int_var;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const unsigned int _temperature_var;
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const MaterialProperty<Real> & _seebeck_coefficient_1;
  const MaterialProperty<Real> & _seebeck_coefficient_2;
  const Real _len_scale;
};
