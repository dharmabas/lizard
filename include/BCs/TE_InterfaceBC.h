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
#include "IntegratedBC.h"

class TE_InterfaceBC;

template <>
InputParameters validParams<TE_InterfaceBC>();

/**
 * Boundary condition of a Dirichlet type
 *
 * Sets the value in the node
 */
class TE_InterfaceBC : public DirichletBCBase
{
public:
  static InputParameters validParams();

  TE_InterfaceBC(const InputParameters & parameters);

protected:
  virtual Real computeQpValue() override;

  /// The value for this BC
  const Real & _value;
  const unsigned int _component;
  const unsigned int _potential_E_int_var;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const unsigned int _temperature_var;
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const Real & _seebeck_coefficient_1;
  const Real & _seebeck_coefficient_2;
  const Real & _electrical_conductivity_1;
  const Real & _electrical_conductivity_2;
  const Real _len_scale;
};
