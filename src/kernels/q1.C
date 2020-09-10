#include "q1.h"

registerMooseObject("lizardApp", q1);

template <>
InputParameters
validParams<q1>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla squared Phi = 0");
  params.addParam<MaterialPropertyName>(
      "thermal_conductivity",
      "Thermal Conductivity",
      "Property name of the thermal conductivity material property");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

q1::q1(const InputParameters & parameters)
  : Kernel(parameters),
    _thermal_conductivity(getMaterialProperty<Real>("thermal_conductivity")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
q1::computeQpResidual()
{
  Real Relec = 0.0;
  Relec += -_grad_test[_i][_qp] * _thermal_conductivity[_qp] * _grad_u[_qp] * _len_scale;
  ///  Moose::out << "\n R_elec-"; std::cout << " = " << Relec;
  return Relec;
}

Real
q1::computeQpJacobian()
{
  return -_grad_test[_i][_qp] * _thermal_conductivity[_qp] * _grad_phi[_j][_qp] * _len_scale;
}
