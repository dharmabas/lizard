#ifndef ResidualT_tensor_H
#define ResidualT_tensor_H

#include "Kernel.h"
#include "Material.h"
#include "RankTwoTensor.h" //added for tensor calculation

class ResidualT_tensor;

template <>
InputParameters validParams<ResidualT_tensor>();

class ResidualT_tensor : public Kernel
{
public:
  ResidualT_tensor(const InputParameters & parameters);

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
  const MaterialProperty<RankTwoTensor> & _thermal_conductivity_tensor; // for tensor inclusion
  const MaterialProperty<RankTwoTensor> & _electrical_conductivity_tensor;
  const MaterialProperty<RankTwoTensor> & _seebeck_coefficient_tensor;
  // const MaterialProperty<Real> & _electrical_conductivity;
  // const MaterialProperty<Real> & _seebeck_coefficient;
  // const MaterialProperty<Real> & _thermal_conductivity;
  const Real _len_scale;
};
#endif
