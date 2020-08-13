#include "OhmsLaw.h"

registerMooseObject("lizardApp", OhmsLaw);

template<>
InputParameters validParams<OhmsLaw>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla phi = 0");
  params.addRequiredCoupledVar("potential_E_int", "electric potential");
  params.addRequiredParam<unsigned int>("component", "An integer corresponding to the direction the variable this kernel acts in. (0 for x, 1 for y, 2 for z)");
  params.addParam<MaterialPropertyName>("electrical_conductivity", "Electrical Conductivity", "Property name of the electrical conductivity material property");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

OhmsLaw::OhmsLaw(const InputParameters & parameters)
  :Kernel(parameters),
    _potential_E_int_var(coupled("potential_E_int")),
    _potential_E_int(coupledValue("potential_E_int")),
    _potential_E_int_grad(coupledGradient("potential_E_int")),
    _component(getParam<unsigned int>("component")),
    _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
OhmsLaw::computeQpResidual()
{
  //for (unsigned int j =0; j<1; ++j)
  //Real Rcur = 0.0;
  return _test[_i][_qp] * _electrical_conductivity[_qp] * _potential_E_int_grad[_qp](_component) * _len_scale;
  ///  Moose::out << "\n R_cur-"; std::cout << " = " << Rcur;
  //return Rcur;
}

Real
OhmsLaw::computeQpJacobian()
{
   return _test[_i][_qp] * _electrical_conductivity[_qp] * _grad_phi[_j][_qp](_component) * _len_scale;

}
