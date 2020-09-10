#include "ModCurrentAux.h"

registerMooseObject("lizardApp", ModCurrentAux);

template <>
InputParameters
validParams<ModCurrentAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Find current component across the Mesh");
  params.addRequiredCoupledVar("potential_E_int", "electrostatic potential");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addRequiredParam<unsigned int>("component", "an integer corresponding to direction");
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

ModCurrentAux::ModCurrentAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _component(getParam<unsigned int>("component")),
    _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    _seebeck_coefficient(getMaterialProperty<Real>("seebeck_coefficient"))
{
}

Real
ModCurrentAux::computeValue()
{
  return (_electrical_conductivity[_qp] * _potential_E_int_grad[_qp](_component)) +
         (_electrical_conductivity[_qp] * _seebeck_coefficient[_qp] *
          _temperature_grad[_qp](_component));
}
