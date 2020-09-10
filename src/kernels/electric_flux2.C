#include "electric_flux2.h"

registerMooseObject("lizardApp", electric_flux2);

template <>
InputParameters
validParams<electric_flux2>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla squared Phi = 0");
  params.addRequiredCoupledVar("potential_E_int", "The potential variable");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

electric_flux2::electric_flux2(const InputParameters & parameters)
  : Kernel(parameters),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _component(getParam<unsigned int>("component")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
electric_flux2::computeQpResidual()
{
  Real Relec = 0.0;
  Relec += _test[_i][_qp] * _u[_qp] * _potential_E_int_grad[_qp](_component);
  ///  Moose::out << "\n R_elec-"; std::cout << " = " << Relec;
  return Relec;
}

Real
electric_flux2::computeQpJacobian()
{
  return _test[_i][_qp] * _u[_qp] * _potential_E_int_grad[_qp](_component);
}
