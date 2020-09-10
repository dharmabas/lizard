#ifndef generated_current_H
#define generated_current_H

#include "AuxKernel.h"

class generated_current;

template <>
InputParameters validParams<generated_current>();

class generated_current : public AuxKernel
{
public:
  generated_current(const InputParameters & parameters);

  virtual ~generated_current() {}

protected:
  virtual Real computeValue();

private:
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const MaterialProperty<Real> & _electrical_conductivity;
  const MaterialProperty<Real> & _seebeck_coefficient;
  const unsigned int _component;
};

#endif
