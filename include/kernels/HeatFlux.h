#ifndef HeatFlux_H
#define HeatFlux_H

#include "Kernel.h"

class HeatFlux; // this is the class i define by myself and not an existing moose object?//

template <>
InputParameters validParams<HeatFlux>();

class HeatFlux : public Kernel
{
public:
  HeatFlux(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const unsigned int _T_var;
  const VariableValue & _T;
  const VariableGradient & _T_grad;
  const unsigned int _component;
  const MaterialProperty<Real> & _thermal_conductivity;
  // const Real _len_scale;
};
#endif
