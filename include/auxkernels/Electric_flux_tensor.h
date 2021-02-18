#ifndef Electric_flux_tensor_H
#define Electric_flux_tensor_H

#include "AuxKernel.h"
#include "Material.h"
#include "RankTwoTensor.h"

class Electric_flux_tensor;

template <>
InputParameters validParams<Electric_flux_tensor>();

class Electric_flux_tensor : public AuxKernel
{
public:
  Electric_flux_tensor(const InputParameters & parameters);

  virtual ~Electric_flux_tensor() {}

protected:
  virtual Real computeValue();

private:
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const MaterialProperty<RankTwoTensor> & _electrical_conductivity_tensor; // tensor inclusion
  const MaterialProperty<RankTwoTensor> & _seebeck_coefficient_tensor;
  // const MaterialProperty<Real> & _electrical_conductivity;
  // const MaterialProperty<Real> & _seebeck_coefficient;
  const unsigned int _component;
};

#endif
