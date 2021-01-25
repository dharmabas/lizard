#include "Electric_flux.h"

registerMooseObject("lizardApp", Electric_flux);

template <>
InputParameters
validParams<Electric_flux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Electric potential generated due to heat flux");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addRequiredCoupledVar("potential_E_int", "electric potential");
  params.addParam<MaterialPropertyName>(
      "electrical_conductivity",
      "Electrical Conductivity",
      "Property name of the electrical conductivity material property");
  params.addParam<MaterialPropertyName>(
      "seebeck_coefficient",
      "Seebeck coefficient",
      "Property name of the Seebeck coefficient material property");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  return params;
}

Electric_flux::Electric_flux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    _seebeck_coefficient(getMaterialProperty<Real>("seebeck_coefficient")),
    _component(getParam<unsigned int>("component"))
{
}

Real
Electric_flux::computeValue()
{
  return -_electrical_conductivity[_qp] * _potential_E_int_grad[_qp](_component) -
         _seebeck_coefficient[_qp] * _electrical_conductivity[_qp] *
             _temperature_grad[_qp](_component);
}
