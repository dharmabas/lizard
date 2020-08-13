#ifndef OHMSLAW_H
#define OHMSLAW_H

#include "Kernel.h"

class OhmsLaw;//this is the class i define by myself and not an existing moose object?//

template<>
InputParameters validParams<OhmsLaw>();

class OhmsLaw: public Kernel
{
public:

  OhmsLaw(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const unsigned int _potential_E_int_var;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const unsigned int _component;
  const MaterialProperty<Real> & _electrical_conductivity;
  const Real _len_scale;
};
#endif
