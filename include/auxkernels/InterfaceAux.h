#ifndef InterfaceAux_H
#define InterfaceAux_H

#include "AuxKernel.h"

// Forward declarations
class InterfaceAux;

template <>
InputParameters validParams<InterfaceAux>();

class InterfaceAux : public AuxKernel
{
public:
  InterfaceAux(const InputParameters & parameters);

  virtual ~InterfaceAux() {}

protected:
  virtual Real computeValue();

private:
  const unsigned int _temperature_var;
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const unsigned int _potential_E_int_var;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;

  const unsigned int _component;

  const MaterialProperty<Real> & _seebeck_coefficient_1;
  const MaterialProperty<Real> & _seebeck_coefficient_2;
  const MaterialProperty<Real> & _electrical_conductivity;
  const MaterialProperty<Real> & _thermal_conductivity;
};

#endif //
