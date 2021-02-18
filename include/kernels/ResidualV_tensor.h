#ifndef ResidualV_tensor_H
#define ResidualV_tensor_H

#include "Kernel.h"
#include "Material.h"
#include "RankTwoTensor.h" //added for tensor calculation

class ResidualV_tensor;

template <>
InputParameters validParams<ResidualV_tensor>();

class ResidualV_tensor : public Kernel
{
public:
  ResidualV_tensor(const InputParameters & parameters);

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
  // const MaterialProperty<Real> & _electrical_conductivity;
  // const MaterialProperty<Real> & _seebeck_coefficient;
  const MaterialProperty<RankTwoTensor> & _electrical_conductivity_tensor; // for tensor inclusion
  const MaterialProperty<RankTwoTensor> & _seebeck_coefficient_tensor;
  const Real _len_scale;
};
#endif
