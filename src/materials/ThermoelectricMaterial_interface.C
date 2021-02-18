//*Moe made material block that sets fraction solid and material properties to temperature
#include "ThermoelectricMaterial_interface.h"
#include "Function.h"
#include "libmesh/quadrature.h"

registerMooseObject("lizardApp", ThermoelectricMaterial_interface);

template <>
InputParameters
validParams<ThermoelectricMaterial_interface>()
{
  InputParameters params = Material::validParams();

  params.addCoupledVar("temperature", "Coupled Temperature");
  params.addCoupledVar("potential_E_int", "Coupled Potential");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addParam<Real>("seebeck_coefficient_1", "The seebeck coefficient value for material 1");
  params.addParam<Real>("seebeck_coefficient_2", "The seebeck coefficient value for material 2");
  params.addParam<Real>("electrical_conductivity", "The electrical conductivity value");

  params.addClassDescription("General-purpose material model for thermoelectrics");

  return params;
}

ThermoelectricMaterial_interface::ThermoelectricMaterial_interface(
    const InputParameters & parameters)
  : Material(parameters),

    _temperature_var(coupled("temperature")),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),

    _component(getParam<unsigned int>("component")),

    _seebeck_coefficient_1(getParam<Real>("seebeck_coefficient_1")),
    _seebeck_coefficient_2(getParam<Real>("seebeck_coefficient_2")),
    _electrical_conductivity(getParam<Real>("electrical_conductivity")),

    _interface_val(declareProperty<Real>("interface_value"))
{
}

void
ThermoelectricMaterial_interface::computeQpProperties()
{
  // InterfaceValue
  _interface_val[_qp] = (_seebeck_coefficient_1 - _seebeck_coefficient_2) * _temperature[_qp] *
                        _electrical_conductivity * _potential_E_int_grad[_qp](_component);
}
