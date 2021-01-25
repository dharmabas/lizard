#include "Q2.h"

registerMooseObject("lizardApp", Q2);

template <>
InputParameters
validParams<Q2>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla squared Phi = 0");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addParam<MaterialPropertyName>(
      "seebeck_coefficient",
      "seebeck_coefficient",
      "Property name of the Seebeck coefficient material property");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

Q2::Q2(const InputParameters & parameters)
  : Kernel(parameters),
    _component(getParam<unsigned int>("component")),
    _temperature_var(coupled("temperature")),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _seebeck_coefficient(getMaterialProperty<Real>("seebeck_coefficient")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
Q2::computeQpResidual()
{

  return _grad_test[_i][_qp](_component) *
         (_grad_u[_qp](_component) +
          (_seebeck_coefficient[_qp] * _temperature_grad[_qp](_component))) *
         _len_scale;
}

Real
Q2::computeQpJacobian()
{
  return _grad_test[_i][_qp](_component) * (_grad_phi[_j][_qp](_component)) * _len_scale;
}

Real
Q2::computeQpOffDiagJacobian()
{
  return _grad_test[_i][_qp](_component) *
         (_seebeck_coefficient[_qp] * _grad_phi[_j][_qp](_component)) * _len_scale;
}
