#include "current1.h"

registerMooseObject("lizardApp", current1);

template <>
InputParameters
validParams<current1>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla squared Phi = 0");
  params.addRequiredCoupledVar("potential_E_int", "electric potential");
  params.addParam<MaterialPropertyName>(
      "electrical_conductivity",
      "Electrical Conductivity",
      "Property name of the electrical conductivity material property");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

current1::current1(const InputParameters & parameters)
  : Kernel(parameters),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
current1::computeQpResidual()
{
  Real Relec = 0.0;
  Relec += -_test[_i][_qp] * _electrical_conductivity[_qp] * _potential_E_int_grad[_qp] *
           _grad_u[_qp] * _len_scale;
  ///  Moose::out << "\n R_elec-"; std::cout << " = " << Relec;
  return Relec;
}

Real
current1::computeQpJacobian()
{
  return -_test[_i][_qp] * _electrical_conductivity[_qp] * _potential_E_int_grad[_qp] *
         _grad_phi[_j][_qp] * _len_scale;
}
