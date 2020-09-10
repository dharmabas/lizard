
#include "electric_flux1.h"

registerMooseObject("lizardApp", electric_flux1);

template <>
InputParameters
validParams<electric_flux1>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla squared Phi = 0");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

electric_flux1::electric_flux1(const InputParameters & parameters)
  : Kernel(parameters),
    _component(getParam<unsigned int>("component")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
electric_flux1::computeQpResidual()
{
  Real Relec = 0.0;
  Relec += _grad_test[_i][_qp](_component) * _u[_qp];
  ///  Moose::out << "\n R_elec-"; std::cout << " = " << Relec;
  return Relec;
}

Real
electric_flux1::computeQpJacobian()
{
  return _grad_test[_i][_qp](_component) * _u[_qp];
}
