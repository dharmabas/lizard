#include "q1.h"
#include "Material.h"

registerMooseObject("lizardApp", q1);

template <>
InputParameters
validParams<q1>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla squared Phi = 0");
  // params.addParam<MaterialPropertyName>("thermal_conductivity", "Thermal Conductivity", "Property
  // name of the thermal conductivity material property");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

q1::q1(const InputParameters & parameters)
  : Kernel(parameters),
    // _thermal_conductivity(getMaterialProperty<Real>("thermal_conductivity")),
    _thermal_conductivity_tensor(getMaterialProperty<RankTwoTensor>(
        "thermal_conductivity_tensor")), // added for tensor application
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
q1::computeQpResidual()
{
  Real sum = 0.0;
  for (unsigned int j = 0; j < 3; ++j)
  {
    sum += -_grad_test[_i][_qp](j) *
           (_thermal_conductivity_tensor[_qp](j, 0) * _grad_u[_qp](0) +
            _thermal_conductivity_tensor[_qp](j, 1) * _grad_u[_qp](1) +
            _thermal_conductivity_tensor[_qp](j, 2) * _grad_u[_qp](2)) *
           _len_scale;
  }
  return sum;
}

Real
q1::computeQpJacobian()
{
  Real sum = 0.0;
  for (unsigned int j = 0; j < 3; ++j)
  {
    sum += -_grad_test[_i][_qp](j) *
           (_thermal_conductivity_tensor[_qp](j, 0) * _grad_phi[_j][_qp](0) +
            _thermal_conductivity_tensor[_qp](j, 1) * _grad_phi[_j][_qp](1) +
            _thermal_conductivity_tensor[_qp](j, 2) * _grad_phi[_j][_qp](2)) *
           _len_scale;
  }
  return sum;
}
