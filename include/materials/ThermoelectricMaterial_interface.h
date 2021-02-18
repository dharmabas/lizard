
#ifndef ThermoelectricMaterial_interface_H
#define ThermoelectricMaterial_interface_H

#include "Material.h"
// Forward Declarations
class ThermoelectricMaterial_interface;

template <>
InputParameters validParams<ThermoelectricMaterial_interface>();

class ThermoelectricMaterial_interface : public Material
{
public:
  ThermoelectricMaterial_interface(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  const unsigned int _temperature_var;
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const unsigned int _potential_E_int_var;
  const VariableValue & _potential_E_int;
  const VariableGradient & _potential_E_int_grad;

  const unsigned int _component;

  Real _seebeck_coefficient_1;
  Real _seebeck_coefficient_2;
  Real _electrical_conductivity;

  ///Mateiral property declarations
  MaterialProperty<Real> & _interface_val;
};

#endif // ThermoelectricMaterial_interface_H
