// #include "TE_fluxBC.h"
//
// registerMooseObject("lizardApp", TE_fluxBC);
//
// template <>
// InputParameters
// validParams<TE_fluxBC>()
// {
//   InputParameters params = validParams<IntegratedBC>();
//   params.addRequiredParam<MaterialPropertyName>("prop_name_1", "the name of the material property
//   1 we are going to use"); params.addRequiredParam<MaterialPropertyName>("prop_name_2", "the name
//   of the material property 2 we are going to use");
//
//   return params;
// }
//
// TE_fluxBC::TE_fluxBC(const InputParameters & parameters)
//   : IntegratedBC(parameters)
// {
//   _diff_1 = &getMaterialProperty<Real>("prop_name_1");
//   _diff_2 = &getMaterialProperty<Real>("prop_name_2");
// }
//
// Real
// TE_fluxBC::computeQpResidual()
// {
//   // return -_test[_i][_qp] * ((*_diff_1)[_qp]-(*_diff_2)[_qp]) * _grad_u[_qp] * _normals[_qp];
//   return -_test[_i][_qp] * ((*_diff_1)[_qp]-(*_diff_2)[_qp]) * _u[_qp];
// }
//
// Real
// TE_fluxBC::computeQpJacobian()
// {
//   //return -_test[_i][_qp] * ((*_diff_1)[_qp]-(*_diff_2)[_qp]) * _grad_phi[_j][_qp] * _normals[_qp];
//   return -_test[_i][_qp] * ((*_diff_1)[_qp]-(*_diff_2)[_qp]) * _phi[_j][_qp];
// }
#include "TE_fluxBC.h"

registerMooseObject("lizardApp", TE_fluxBC);

template <>
InputParameters
validParams<TE_fluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<MaterialPropertyName>("seebeck_coefficient_interface",
                                                "Seebeck coefficent for the interface");

  return params;
}

TE_fluxBC::TE_fluxBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _seebeck_coefficient_interface(getMaterialProperty<Real>("seebeck_coefficient_interface"))

{
}

Real
TE_fluxBC::computeQpResidual()
{
  return -_test[_i][_qp] * _seebeck_coefficient_interface[_qp] * _grad_u[_qp] * _normals[_qp];
}

Real
TE_fluxBC::computeQpJacobian()
{
  return -_test[_i][_qp] * _seebeck_coefficient_interface[_qp] * _grad_phi[_j][_qp] * _normals[_qp];
}
