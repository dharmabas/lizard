#ifndef RESIDUALT_H
#define RESIDUALT_H

#include "Kernel.h"

class ResidualT;

template <>
InputParameters validParams<ResidualT>();

class ResidualT : public Kernel
{
public:
  ResidualT(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  const unsigned int _component;
  const unsigned int _potential_E_int_var;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const unsigned int _temperature_var;
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  // const Real _electrical_conductivity;
  // const Real _seebeck_coefficient;
  // const Real _thermal_conductivity;
  const MaterialProperty<Real> & _electrical_conductivity;
  const MaterialProperty<Real> & _seebeck_coefficient;
  const MaterialProperty<Real> & _thermal_conductivity;
  const Real _len_scale;
};
#endif
