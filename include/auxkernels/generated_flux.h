#ifndef generated_flux_H
#define generated_flux_H

#include "AuxKernel.h"

class generated_flux;

template <>
InputParameters validParams<generated_flux>();

class generated_flux : public AuxKernel
{
public:
  generated_flux(const InputParameters & parameters);

  virtual ~generated_flux() {}

protected:
  virtual Real computeValue();

private:
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;
  const MaterialProperty<Real> & _thermal_conductivity;
  const MaterialProperty<Real> & _electrical_conductivity;
  const MaterialProperty<Real> & _seebeck_coefficient;
  const unsigned int _component;
};

#endif
