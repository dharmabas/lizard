#include "potential_update.h"

registerMooseObject("lizardApp", potential_update);

template <>
InputParameters
validParams<potential_update>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Electric potential generated due to heat flux");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addParam<MaterialPropertyName>(
      "seebeck_coefficient",
      "Seebeck coefficient",
      "Property name of the Seebeck coefficient material property");
  return params;
}

potential_update::potential_update(const InputParameters & parameters)
  : AuxKernel(parameters),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _seebeck_coefficient(getMaterialProperty<Real>("seebeck_coefficient"))
{
}

Real
potential_update::computeValue()
{
  return _seebeck_coefficient[_qp] * _temperature[_qp];
}
