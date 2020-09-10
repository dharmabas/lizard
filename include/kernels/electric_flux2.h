#ifndef electric_flux2_H
#define electric_flux2_H

#include "Kernel.h"

class electric_flux2;

template <>
InputParameters validParams<electric_flux2>();

class electric_flux2 : public Kernel
{
public:
  electric_flux2(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const unsigned int _potential_E_int_var;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const unsigned int _component;
  const Real _len_scale;
};
#endif
