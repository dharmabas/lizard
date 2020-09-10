#ifndef temperature_update_H
#define temperature_update_H

#include "AuxKernel.h"

class temperature_update;

template <>
InputParameters validParams<temperature_update>();

class temperature_update : public AuxKernel
{
public:
  temperature_update(const InputParameters & parameters);

  virtual ~temperature_update() {}

protected:
  virtual Real computeValue();

private:
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const MaterialProperty<Real> & _seebeck_coefficient;
  // const Real _dx;
};

#endif
