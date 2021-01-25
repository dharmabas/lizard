#ifndef Electric_flux_H
#define Electric_flux_H

#include "AuxKernel.h"

class Electric_flux;

template <>
InputParameters validParams<Electric_flux>();

class Electric_flux : public AuxKernel
{
public:
  Electric_flux(const InputParameters & parameters);

  virtual ~Electric_flux() {}

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
