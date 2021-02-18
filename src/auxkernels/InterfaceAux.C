// Takes density parameter from materials block
#include "InterfaceAux.h"

registerMooseObject("lizardApp", InterfaceAux);

template <>
InputParameters
validParams<InterfaceAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Sanity check for interface parameter value");
  params.addCoupledVar("temperature", "Coupled Temperature");
  params.addCoupledVar("potential_E_int", "Coupled Potential");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addRequiredParam<MaterialPropertyName>("seebeck_coefficient_1",
                                                "The seebeck coefficient value for material 1");
  params.addRequiredParam<MaterialPropertyName>("seebeck_coefficient_2",
                                                "The seebeck coefficient value for material 2");
  params.addRequiredParam<MaterialPropertyName>("electrical_conductivity",
                                                "The electrical conductivity value");
  params.addRequiredParam<MaterialPropertyName>("thermal_conductivity",
                                                "The thermal_conductivity conductivity value");

  return params;
}

InterfaceAux::InterfaceAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _temperature_var(coupled("temperature")),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),

    _component(getParam<unsigned int>("component")),

    _seebeck_coefficient_1(getMaterialProperty<Real>("seebeck_coefficient_1")),
    _seebeck_coefficient_2(getMaterialProperty<Real>("seebeck_coefficient_2")),
    _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    _thermal_conductivity(getMaterialProperty<Real>("thermal_conductivity"))
{
}

Real
InterfaceAux::computeValue()

{
  // return (-_thermal_conductivity[_qp] * _temperature_grad[_qp](_component)
  // -_seebeck_coefficient_1[_qp] * _temperature[_qp] * _electrical_conductivity[_qp]
  // *_potential_E_int_grad[_qp](_component) -_seebeck_coefficient_1[_qp] *
  // _seebeck_coefficient_1[_qp] * _electrical_conductivity[_qp] *_temperature[_qp] *
  // _temperature_grad[_qp](_component))
  // - (-_thermal_conductivity[_qp] * _temperature_grad[_qp](_component)
  // -_seebeck_coefficient_2[_qp] * _temperature[_qp] * _electrical_conductivity[_qp]
  // *_potential_E_int_grad[_qp](_component) -_seebeck_coefficient_2[_qp] *
  // _seebeck_coefficient_2[_qp] * _electrical_conductivity[_qp] *_temperature[_qp] *
  // _temperature_grad[_qp](_component));
  return (-(_seebeck_coefficient_1[_qp] * _temperature[_qp] * _electrical_conductivity[_qp] *
            _potential_E_int_grad[_qp](_component)) -
          (_seebeck_coefficient_2[_qp] * _temperature[_qp] * _electrical_conductivity[_qp] *
           _potential_E_int_grad[_qp](_component)));
}
