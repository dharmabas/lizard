#include "HeatFlux.h"

registerMooseObject("lizardApp", HeatFlux);

template<>
InputParameters validParams<HeatFlux>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla V = 0");
  params.addRequiredCoupledVar("Temperature", "Temperature");
  params.addRequiredParam<unsigned int>("component", "An integer corresponding to the direction the variable this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addParam<MaterialPropertyName>("thermal_conductivity","thermal_conductivity");
  //params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

HeatFlux::HeatFlux(const InputParameters & parameters)
  :Kernel(parameters),
   _T_var(coupled("Temperature")),
   _T(coupledValue("Temperature")),
   _T_grad(coupledGradient("Temperature")),
   _component(getParam<unsigned int>("component")),
   _thermal_conductivity(getMaterialProperty<Real>("thermal_conductivity"))
   //_len_scale(getParam<Real>("len_scale"))
{
}

Real
HeatFlux::computeQpResidual()
{
  Real Relec = 0.0;
  Relec += _test[_i][_qp] * _thermal_conductivity[_qp]  * _T_grad[_qp](_component);
  ///  Moose::out << "\n R_elec-"; std::cout << " = " << Relec;
  return Relec;
}

Real
HeatFlux::computeQpJacobian()
{
  return _test[_i][_qp] * _thermal_conductivity[_qp]  * _grad_phi[_j][_qp](_component);
}
