#ifndef Heat_flux_tensor_H
#define Heat_flux_tensor_H

#include "AuxKernel.h"
#include "Material.h"
#include "RankTwoTensor.h"

class Heat_flux_tensor;

template <>
InputParameters validParams<Heat_flux_tensor>();

class Heat_flux_tensor : public AuxKernel
{
public:
  Heat_flux_tensor(const InputParameters & parameters);

  virtual ~Heat_flux_tensor() {}

protected:
  virtual Real computeValue();

private:
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  // const MaterialProperty<Real> & _thermal_conductivity;
  const MaterialProperty<RankTwoTensor> & _thermal_conductivity_tensor; // for tensor inclusion
  const MaterialProperty<RankTwoTensor> & _electrical_conductivity_tensor;
  const MaterialProperty<RankTwoTensor> & _seebeck_coefficient_tensor;
  // const MaterialProperty<Real> & _electrical_conductivity;
  // const MaterialProperty<Real> & _seebeck_coefficient;
  const unsigned int _component;
  const Real _len_scale;
};

#endif
