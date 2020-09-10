#ifndef CurrentAux_H
#define CurrentAux_H

#include "AuxKernel.h"

class CurrentAux;

template <>
InputParameters validParams<CurrentAux>();

class CurrentAux : public AuxKernel
{
public:
  CurrentAux(const InputParameters & parameters);

  virtual ~CurrentAux() {}

protected:
  virtual Real computeValue();

private:
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const unsigned int _component;
  const MaterialProperty<Real> & _electrical_conductivity;
};

#endif
