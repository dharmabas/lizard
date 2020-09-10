#include "q3.h"

registerMooseObject("lizardApp", q3);

template <>
InputParameters
validParams<q3>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla squared Phi = 0");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addParam<MaterialPropertyName>(
      "electrical_conductivity",
      "Electrical Conductivity",
      "Property name of the electrical conductivity material property");
  params.addParam<MaterialPropertyName>(
      "seebeck_coefficient",
      "Seebeck coefficient",
      "Property name of the Seebeck coefficient material property");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

q3::q3(const InputParameters & parameters)
  : Kernel(parameters),
    _temperature_var(coupled("temperature")),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    _seebeck_coefficient(getMaterialProperty<Real>("seebeck_coefficient")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
q3::computeQpResidual()
{
  Real Relec = 0.0;
  Relec += -_grad_test[_i][_qp] * _seebeck_coefficient[_qp] * _seebeck_coefficient[_qp] *
           _electrical_conductivity[_qp] * _temperature[_qp] * _grad_u[_qp] * _len_scale;
  ///  Moose::out << "\n R_elec-"; std::cout << " = " << Relec;
  return Relec;
}

Real
q3::computeQpJacobian()
{
  return -_grad_test[_i][_qp] * _seebeck_coefficient[_qp] * _seebeck_coefficient[_qp] *
         _electrical_conductivity[_qp] * _temperature[_qp] * _grad_phi[_j][_qp] * _len_scale;
}
