// #include "TE_InterfaceBC.h"
//
// registerMooseObject("lizardApp", TE_InterfaceBC);
//
// template <>
// InputParameters
// validParams<TE_InterfaceBC>()
// {
//   InputParameters params = validParams<IntegratedBC>();
//   params.addRequiredParam<MaterialPropertyName>(
//       "prop_name", "the name of the material property we are going to use");
//
//   return params;
// }
//
// TE_InterfaceBC::TE_InterfaceBC(const InputParameters & parameters)
//   : IntegratedBC(parameters)
// {
//   _diff = &getMaterialProperty<Real>("prop_name");
// }
//
// Real
// TE_InterfaceBC::computeQpResidual()
// {
//   return -_test[_i][_qp] * (*_diff)[_qp] * _grad_u[_qp] * _normals[_qp];
// }
//
// Real
// TE_InterfaceBC::computeQpJacobian()
// {
//   return -_test[_i][_qp] * (*_diff)[_qp] * _grad_phi[_j][_qp] * _normals[_qp];
// }
