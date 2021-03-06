#include "ResidualV_tensor.h"
// #include "HeatConduction.h"
#include "Material.h"

registerMooseObject("lizardApp", ResidualV_tensor);

template <>
InputParameters
validParams<ResidualV_tensor>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to modified ohm's law");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addRequiredCoupledVar("potential_E_int", "electrical potential");
  params.addRequiredCoupledVar("T", "temperature");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

ResidualV_tensor::ResidualV_tensor(const InputParameters & parameters)
  : Kernel(parameters),
    _component(getParam<unsigned int>("component")),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _T_var(coupled("T")),
    _T(coupledValue("T")),
    _T_grad(coupledGradient("T")),
    _ecC_tensor(getMaterialProperty<RankTwoTensor>("ecC_tensor")), // added for tensor application
    _sbC_tensor(getMaterialProperty<RankTwoTensor>("sbC_tensor")), // added for tensor application
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
ResidualV_tensor::computeQpResidual()
// include tensor//

{
  Real sum = 0.0;
  for (unsigned int j = 0, k = 0; j < 3 && k < 3; ++j, ++k)
  {
    sum +=
        (((-_grad_test[_i][_qp](0)) *
              (-_ecC_tensor[_qp](j, 0) * _sbC_tensor[_qp](0, k) * _T_grad[_qp](0)) +
          (-_grad_test[_i][_qp](0)) * (-_ecC_tensor[_qp](j, 0) * _potential_E_int_grad[_qp](0))) +
         (-_grad_test[_i][_qp](1) *
              (-_ecC_tensor[_qp](j, 1) * _sbC_tensor[_qp](1, k) * _T_grad[_qp](1)) +
          (-_grad_test[_i][_qp](1)) * (-_ecC_tensor[_qp](j, 1) * _potential_E_int_grad[_qp](1))) +
         (-_grad_test[_i][_qp](2) *
              (-_ecC_tensor[_qp](j, 2) * _sbC_tensor[_qp](2, k) * _T_grad[_qp](2)) +
          (-_grad_test[_i][_qp](2)) * (-_ecC_tensor[_qp](j, 2) * _potential_E_int_grad[_qp](2)))) *
        _len_scale;
  }
  return sum;
}

Real
ResidualV_tensor::computeQpJacobian()

// include tensor//
{
  Real sum = 0.0;
  for (unsigned int j = 0; j < 3; ++j)
  {
    sum += ((-_grad_test[_i][_qp](0)) * (-_ecC_tensor[_qp](j, 0) * _grad_phi[_j][_qp](0)) +
            (-_grad_test[_i][_qp](1)) * (-_ecC_tensor[_qp](j, 1) * _grad_phi[_j][_qp](1)) +
            (-_grad_test[_i][_qp](2)) * (-_ecC_tensor[_qp](j, 2) * _grad_phi[_j][_qp](2))) *
           _len_scale;
  }
  return sum;
}

Real
ResidualV_tensor::computeQpOffDiagJacobian(unsigned int jvar)
// include tensor//

{
  if (jvar == _T_var)
  {
    Real sum = 0.0;
    for (unsigned int j = 0, k = 0; j < 3 && k < 3; ++j, ++k)
    {
      sum += ((-_grad_test[_i][_qp](0)) *
                  (-_ecC_tensor[_qp](j, 0) * _sbC_tensor[_qp](0, k) * _grad_phi[_j][_qp](0)) +
              (-_grad_test[_i][_qp](1)) *
                  (-_ecC_tensor[_qp](j, 1) * _sbC_tensor[_qp](1, k) * _grad_phi[_j][_qp](1)) +
              (-_grad_test[_i][_qp](2)) *
                  (-_ecC_tensor[_qp](j, 2) * _sbC_tensor[_qp](2, k) * _grad_phi[_j][_qp](2))) *
             _len_scale;
    }
    return sum;
  }
  else
  {
    return 0.0;
  }
}
