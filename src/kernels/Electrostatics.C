#include "Electrostatics.h"

registerMooseObject("lizardApp", Electrostatics);

template<>
InputParameters validParams<Electrostatics>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla squared Phi = 0");
  params.addParam<MaterialPropertyName>("electrical_conductivity", "Electrical Conductivity", "Property name of the electrical conductivity material property");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

Electrostatics::Electrostatics(const InputParameters & parameters)
  :Kernel(parameters),
   _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
   _len_scale(getParam<Real>("len_scale"))
{
}

Real
Electrostatics::computeQpResidual()
{
  Real Relec = 0.0;
  Relec += _grad_test[_i][_qp] * _electrical_conductivity[_qp] * _grad_u[_qp] * _len_scale;
  ///  Moose::out << "\n R_elec-"; std::cout << " = " << Relec;
  return Relec;
}

Real
Electrostatics::computeQpJacobian()
{
   return _grad_test[_i][_qp] * _electrical_conductivity[_qp] * _grad_phi[_j][_qp] * _len_scale;
}
