#ifndef tensorHeat_flux_H
#define tensorHeat_flux_H

#include "AuxKernel.h"

class tensorHeat_flux;

template <>
InputParameters validParams<tensorHeat_flux>();

class tensorHeat_flux : public AuxKernel
{
public:
  tensorHeat_flux(const InputParameters & parameters);

  virtual ~tensorHeat_flux() {}

protected:
  virtual Real computeValue();

private:
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const MaterialProperty<RankTwoTensor> & _thermal_conductivity_tensor; // for tensor inclusion
  const unsigned int _component;
  const Real _len_scale;
};

#endif
