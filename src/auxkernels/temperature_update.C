#include "temperature_update.h"

registerMooseObject("lizardApp", temperature_update);

template <>
InputParameters
validParams<temperature_update>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Electric potential generated due to heat flux");
  params.addRequiredCoupledVar("potential_E_int", "electrostatic potential");
  params.addParam<MaterialPropertyName>(
      "electrical_conductivity",
      "Electrical Conductivity",
      "Property name of the electrical conductivity material property");
  params.addParam<MaterialPropertyName>(
      "seebeck_coefficient",
      "Seebeck coefficient",
      "Property name of the Seebeck coefficient material property");
  return params;
}

temperature_update::temperature_update(const InputParameters & parameters)
  : AuxKernel(parameters),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _seebeck_coefficient(getMaterialProperty<Real>("seebeck_coefficient"))
{
}

Real
temperature_update::computeValue()
{
  return _potential_E_int[_qp] * pow(_seebeck_coefficient[_qp], -1);
}
