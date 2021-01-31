// //* This file is part of the MOOSE framework
// //* https://www.mooseframework.org
// //*
// //* All rights reserved, see COPYRIGHT for full restrictions
// //* https://github.com/idaholab/moose/blob/master/COPYRIGHT
// //*
// //* Licensed under LGPL 2.1, please see LICENSE for details
// //* https://www.gnu.org/licenses/lgpl-2.1.html
//
// #include "InterfaceKernel.h"
//
// /**
//  * InterfaceKernel for modeling conjugate heat transfer.
//  * The fluid block must be the primary block that owns
//  * the sidset; therefore, "element" is the element that
//  * the fluid temperature is defined. The solid block is the
//  * neighbor side and the solid element is the "neighbor_elem"
//  * The fluid energy equation may not be solved for temperature.
//  * To handle that case, T_fluid must be provided separately.
//  * If T_fluid is the primary variable of the fluid energy equation
//  * then variable and T_fluid are the same.
//  */
// class TE_Interface_HeatTransfer : public InterfaceKernel
// {
// public:
//   static InputParameters validParams();
//
//   TE_Interface_HeatTransfer(const InputParameters & parameters);
//
// protected:
//   virtual Real computeQpResidual(Moose::DGResidualType type) override;
//   virtual Real computeQpJacobian(Moose::DGJacobianType type) override;
//
//   /// Convective heat transfer coefficient
//   const ADMaterialProperty<Real> & _h;
//
//   /// Fluid temperature
//
//   const unsigned int _temperature_var;
//   const VariableValue & _temperature;
//   const VariableGradient & _temperature_grad;
//   const unsigned int _potential_E_int_var;
//   const VariableValue & _potential_E_int;
//   const VariableGradient & _potential_E_int_grad;
//   const unsigned int _component;
//   const MaterialProperty<Real> & _electrical_conductivity;
//   const MaterialProperty<Real> & _seebeck_coefficient_1;
//   const MaterialProperty<Real> & _seebeck_coefficient_2;
//
//   /// Element Jacobian is only applied if variable = T_fluid
//   const bool _apply_element_jacobian;
// };
