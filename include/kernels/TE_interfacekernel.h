//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Kernel.h"

// Forward Declarations
class TE_interfacekernel;
class Function;

template <>
InputParameters validParams<TE_interfacekernel>();

/**
 * This kernel implements a generic functional
 * body force term:
 * $ - c \cdof f \cdot \phi_i $
 *
 * The coefficient and function both have defaults
 * equal to 1.0.
 */
class TE_interfacekernel : public Kernel
{
public:
  static InputParameters validParams();

  TE_interfacekernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

  const unsigned int _temperature_var;
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const unsigned int _potential_E_int_var;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const unsigned int _component;
  const MaterialProperty<Real> & _seebeck_coefficient_1;
  const MaterialProperty<Real> & _seebeck_coefficient_2;
  const MaterialProperty<Real> & _electrical_conductivity;
};
