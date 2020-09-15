#include "ResidualV.h"
// #include "HeatConduction.h"
#include "Material.h"

registerMooseObject("lizardApp", ResidualV);

template <>
InputParameters
validParams<ResidualV>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to modified ohm's law");
  params.addParam<MaterialPropertyName>("electrical_conductivity", "electrical_conductivity");
  params.addParam<MaterialPropertyName>("seebeck_coefficient", "seebeck_coefficient");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction the variable "
                                        "this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addRequiredCoupledVar("potential_E_int", "electrical potential");
  params.addRequiredCoupledVar("temperature", "temperature");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

ResidualV::ResidualV(const InputParameters & parameters)
  : Kernel(parameters),
    _component(getParam<unsigned int>("component")),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _temperature_var(coupled("temperature")),
    _temperature(coupledValue("temperature")),
    _temperature_grad(coupledGradient("temperature")),
    _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    _seebeck_coefficient(getMaterialProperty<Real>("seebeck_coefficient")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
ResidualV::computeQpResidual()

{
  return (((-_grad_test[_i][_qp](0)) * (-_electrical_conductivity[_qp] * _seebeck_coefficient[_qp] *
                                        _temperature_grad[_qp](0)) +
           (-_grad_test[_i][_qp](0)) *
               (-_electrical_conductivity[_qp] * _potential_E_int_grad[_qp](0))) +
          (-_grad_test[_i][_qp](1) * (-_electrical_conductivity[_qp] * _seebeck_coefficient[_qp] *
                                      _temperature_grad[_qp](1)) +
           (-_grad_test[_i][_qp](1)) *
               (-_electrical_conductivity[_qp] * _potential_E_int_grad[_qp](1))) +
          (-_grad_test[_i][_qp](2) * (-_electrical_conductivity[_qp] * _seebeck_coefficient[_qp] *
                                      _temperature_grad[_qp](2)) +
           (-_grad_test[_i][_qp](2)) *
               (-_electrical_conductivity[_qp] * _potential_E_int_grad[_qp](2)))) *
         _len_scale;
}

Real
ResidualV::computeQpJacobian()

{
  return ((-_grad_test[_i][_qp](0)) * (-_electrical_conductivity[_qp] * _grad_phi[_j][_qp](0)) +
          (-_grad_test[_i][_qp](1)) * (-_electrical_conductivity[_qp] * _grad_phi[_j][_qp](1)) +
          (-_grad_test[_i][_qp](2)) * (-_electrical_conductivity[_qp] * _grad_phi[_j][_qp](2))) *
         _len_scale;
}

Real
ResidualV::computeQpOffDiagJacobian()
{
  return ((-_grad_test[_i][_qp](0)) *
              (-_electrical_conductivity[_qp] * _seebeck_coefficient[_qp] * _grad_phi[_j][_qp](0)) +
          (-_grad_test[_i][_qp](1)) *
              (-_electrical_conductivity[_qp] * _seebeck_coefficient[_qp] * _grad_phi[_j][_qp](1)) +
          (-_grad_test[_i][_qp](2)) * (-_electrical_conductivity[_qp] * _seebeck_coefficient[_qp] *
                                       _grad_phi[_j][_qp](2))) *
         _len_scale;
}
