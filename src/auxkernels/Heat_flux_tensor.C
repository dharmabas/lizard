#include "Heat_flux_tensor.h"
#include "Material.h"
#include "RankTwoTensor.h"

registerMooseObject("lizardApp", Heat_flux_tensor);

template <>
InputParameters
validParams<Heat_flux_tensor>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Electric potential generated due to heat flux");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addRequiredCoupledVar("potential_E_int", "electric potential");
  // params.addParam<MaterialPropertyName>("thermal_conductivity", "Thermal Conductivity", "Property
  // name of the thermal conductivity material property");
  // params.addParam<MaterialPropertyName>("electrical_conductivity", "Electrical Conductivity",
  // "Property name of the electrical conductivity material property");
  // params.addParam<MaterialPropertyName>("seebeck_coefficient", "Seebeck coefficient", "Property
  // name of the Seebeck coefficient material property");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

Heat_flux_tensor::Heat_flux_tensor(const InputParameters & parameters)
  : AuxKernel(parameters),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    // _thermal_conductivity(getMaterialProperty<Real>("thermal_conductivity")),
    _thermal_conductivity_tensor(getMaterialProperty<RankTwoTensor>(
        "thermal_conductivity_tensor")), // added for tensor application
    _electrical_conductivity_tensor(
        getMaterialProperty<RankTwoTensor>("electrical_conductivity_tensor")),
    _seebeck_coefficient_tensor(getMaterialProperty<RankTwoTensor>("seebeck_coefficient_tensor")),
    // _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    // _seebeck_coefficient(getMaterialProperty<Real>("seebeck_coefficient")),
    _component(getParam<unsigned int>("component")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
Heat_flux_tensor::computeValue()
// {
//   return (-_thermal_conductivity[_qp] * _temperature_grad[_qp](_component) -
//   _seebeck_coefficient[_qp] * _temperature[_qp] * _electrical_conductivity[_qp] *
//   _potential_E_int_grad[_qp](_component) - _seebeck_coefficient[_qp] * _seebeck_coefficient[_qp]
//   * _electrical_conductivity[_qp] * _temperature[_qp] * _temperature_grad[_qp](_component)) *
//   _len_scale;
//   // return (-_thermal_conductivity[_qp] * _temperature_grad[_qp](_component) + _seebeck_coefficient[_qp] * _temperature[_qp] * 3.2e6) * _len_scale;
// }

// tensor inclusion
{
  Real sum = 0.0;
  for (unsigned int i = 0, k = 0, l = 0; i < 3 && k < 3 && l < 3; ++i, ++k, ++l)
  {
    sum += (-_thermal_conductivity_tensor[_qp](i, 0) * _temperature_grad[_qp](0) -
            _seebeck_coefficient_tensor[_qp](i, k) * _electrical_conductivity_tensor[_qp](k, 0) *
                _temperature[_qp] * _potential_E_int_grad[_qp](0) -
            _seebeck_coefficient_tensor[_qp](i, k) * _seebeck_coefficient_tensor[_qp](k, l) *
                _electrical_conductivity_tensor[_qp](l, 0) * _temperature[_qp] *
                _temperature_grad[_qp](0) -
            _thermal_conductivity_tensor[_qp](i, 1) * _temperature_grad[_qp](1) -
            _seebeck_coefficient_tensor[_qp](i, k) * _electrical_conductivity_tensor[_qp](k, 1) *
                _temperature[_qp] * _potential_E_int_grad[_qp](1) -
            _seebeck_coefficient_tensor[_qp](i, k) * _seebeck_coefficient_tensor[_qp](k, l) *
                _electrical_conductivity_tensor[_qp](l, 1) * _temperature[_qp] *
                _temperature_grad[_qp](1) -
            _thermal_conductivity_tensor[_qp](i, 2) * _temperature_grad[_qp](2) -
            _seebeck_coefficient_tensor[_qp](i, k) * _electrical_conductivity_tensor[_qp](k, 2) *
                _temperature[_qp] * _potential_E_int_grad[_qp](2) -
            _seebeck_coefficient_tensor[_qp](i, k) * _seebeck_coefficient_tensor[_qp](k, l) *
                _electrical_conductivity_tensor[_qp](l, 2) * _temperature[_qp] *
                _temperature_grad[_qp](2)) *
           _len_scale;
    // return (-_thermal_conductivity[_qp] * _temperature_grad[_qp](_component) +
    // _seebeck_coefficient[_qp] * _temperature[_qp] * 3.2e6) * _len_scale;
  }
  return sum;
}
