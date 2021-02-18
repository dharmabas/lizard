#include "Electric_flux_tensor.h"
#include "Material.h"
#include "RankTwoTensor.h"

registerMooseObject("lizardApp", Electric_flux_tensor);

template <>
InputParameters
validParams<Electric_flux_tensor>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Electric potential generated due to heat flux");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addRequiredCoupledVar("potential_E_int", "electric potential");
  // params.addParam<MaterialPropertyName>("electrical_conductivity", "Electrical Conductivity",
  // "Property name of the electrical conductivity material property");
  // params.addParam<MaterialPropertyName>("seebeck_coefficient", "Seebeck coefficient", "Property
  // name of the Seebeck coefficient material property");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  return params;
}

Electric_flux_tensor::Electric_flux_tensor(const InputParameters & parameters)
  : AuxKernel(parameters),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _electrical_conductivity_tensor(
        getMaterialProperty<RankTwoTensor>("electrical_conductivity_tensor")),
    _seebeck_coefficient_tensor(getMaterialProperty<RankTwoTensor>("seebeck_coefficient_tensor")),
    // _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    // _seebeck_coefficient(getMaterialProperty<Real>("seebeck_coefficient")),
    _component(getParam<unsigned int>("component"))
{
}

Real
Electric_flux_tensor::computeValue()
// {
//   return -_electrical_conductivity[_qp] * _potential_E_int_grad[_qp](_component) -
//   _seebeck_coefficient[_qp] * _electrical_conductivity[_qp] * _temperature_grad[_qp](_component);
// }
// tensor inclusion
{
  Real sum = 0.0;
  for (unsigned int i = 0, k = 0; i < 3 && k < 3; ++i, ++k)
  {
    sum += -_electrical_conductivity_tensor[_qp](i, 0) * _potential_E_int_grad[_qp](0) -
           _seebeck_coefficient_tensor[_qp](i, k) * _electrical_conductivity_tensor[_qp](k, 0) *
               _temperature_grad[_qp](0) -
           _electrical_conductivity_tensor[_qp](i, 1) * _potential_E_int_grad[_qp](1) -
           _seebeck_coefficient_tensor[_qp](i, k) * _electrical_conductivity_tensor[_qp](k, 1) *
               _temperature_grad[_qp](1) -
           _electrical_conductivity_tensor[_qp](i, 2) * _potential_E_int_grad[_qp](2) -
           _seebeck_coefficient_tensor[_qp](i, k) * _electrical_conductivity_tensor[_qp](k, 2) *
               _temperature_grad[_qp](2);
  }
  return sum;
}
