#include "Electric_flux_tensor.h"
#include "Material.h"
#include "RankTwoTensor.h"

registerMooseObject("lizardApp", Electric_flux_tensor);

template <>
InputParameters
validParams<Electric_flux_tensor>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Electric flux generated");
  params.addRequiredCoupledVar("T", "temperature");
  params.addRequiredCoupledVar("potential_E_int", "electric potential");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  return params;
}

Electric_flux_tensor::Electric_flux_tensor(const InputParameters & parameters)
  : AuxKernel(parameters),
    _T(coupledValue("T")),
    _T_grad(coupledGradient("T")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _ecC_tensor(getMaterialProperty<RankTwoTensor>("ecC_tensor")),
    _sbC_tensor(getMaterialProperty<RankTwoTensor>("sbC_tensor")),
    _component(getParam<unsigned int>("component"))
{
}

Real
Electric_flux_tensor::computeValue()
// tensor inclusion
{
  Real sum = 0.0;
  for (unsigned int i = 0, k = 0; i < 3 && k < 3; ++i, ++k)
  {
    sum += -_ecC_tensor[_qp](i, 0) * _potential_E_int_grad[_qp](0) -
           _sbC_tensor[_qp](i, k) * _ecC_tensor[_qp](k, 0) * _T_grad[_qp](0) -
           _ecC_tensor[_qp](i, 1) * _potential_E_int_grad[_qp](1) -
           _sbC_tensor[_qp](i, k) * _ecC_tensor[_qp](k, 1) * _T_grad[_qp](1) -
           _ecC_tensor[_qp](i, 2) * _potential_E_int_grad[_qp](2) -
           _sbC_tensor[_qp](i, k) * _ecC_tensor[_qp](k, 2) * _T_grad[_qp](2);
  }
  return sum;
}
