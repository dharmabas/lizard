//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "InterfaceKernel.h"

// Forward Declarations

/**
 * DG kernel for interfacing diffusion between two variables on adjacent blocks
 */
class SideSet_TE_HeatTransferKernel : public InterfaceKernel
{
public:
  SideSet_TE_HeatTransferKernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type) override;
  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;

  /// Bulk temperature of gap
  const VariableValue * const _temperature;
  // const MaterialProperty<Real> * const _temperature_mat;

  // const unsigned int _temperature_var;
  // const VariableValue & _temperature;
  // const VariableGradient & _temperature_grad;
  // const unsigned int _potential_E_int_var;
  // const VariableValue & _potential_E_int;
  // const VariableGradient & _potential_E_int_grad;
  // const unsigned int _component;
  const MaterialProperty<Real> & _seebeck_coefficient_interface;
  // const MaterialProperty<Real> & _seebeck_coefficient_1;
  // const MaterialProperty<Real> & _seebeck_coefficient_2;
  // const MaterialProperty<Real> & _electrical_conductivity_1;
  // const MaterialProperty<Real> & _electrical_conductivity_2;
};
