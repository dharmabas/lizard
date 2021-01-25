#include "tensorHeat_flux.h"
#include "Material.h"

registerMooseObject("lizardApp", tensorHeat_flux);

template <>
InputParameters
validParams<tensorHeat_flux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("heat generated");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

tensorHeat_flux::tensorHeat_flux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _thermal_conductivity_tensor(getMaterialProperty<RankTwoTensor>(
        "thermal_conductivity_tensor")), // added for tensor application
    _component(getParam<unsigned int>("component")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
tensorHeat_flux::computeValue()
{
  Real sum = 0.0;
  for (unsigned int j = 0; j < 3; ++j)
  {
    sum += (-_thermal_conductivity_tensor[_qp](j, 0) * _temperature_grad[_qp](0) -
            _thermal_conductivity_tensor[_qp](j, 0) * _temperature_grad[_qp](1) -
            _thermal_conductivity_tensor[_qp](j, 0) * _temperature_grad[_qp](2)) *
           _len_scale;
  }
  return sum;
}
