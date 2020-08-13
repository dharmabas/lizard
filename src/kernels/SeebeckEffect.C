#include "SeebeckEffect.h"

registerMooseObject("lizardApp",SeebeckEffect);

template<>
InputParameters validParams<SeebeckEffect>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a residual contribution due to nabla phi = 0");
  params.addParam<MaterialPropertyName>("electrical_conductivity", "Electrical Conductivity", "Property name of the electrical conductivity material property");
  params.addParam<MaterialPropertyName>("seebeck_coefficient", "Seebeck coefficient", "Property name of the Seebeck coefficient material property");
  params.addParam<Real>("len_scale", 1.0, "the length scale of the unit");
  return params;
}

SeebeckEffect::SeebeckEffect(const InputParameters & parameters)
  :Kernel(parameters),
    _electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity")),
    _seebeck_coefficient(getMaterialProperty<Real>("seebeck_coefficient")),
    _len_scale(getParam<Real>("len_scale"))
{
}

Real
SeebeckEffect::computeQpResidual()
{
  //for (unsigned int j =0; j<1; ++j)
  //Real Rcur = 0.0;
  return - _grad_test[_i][_qp] * _seebeck_coefficient[_qp] * _electrical_conductivity[_qp] * _grad_u[_qp] * _len_scale;
  ///  Moose::out << "\n R_cur-"; std::cout << " = " << Rcur;
  //return Rcur;
}

Real
SeebeckEffect::computeQpJacobian()
{
   return - _grad_test[_i][_qp] * _seebeck_coefficient[_qp] * _electrical_conductivity[_qp] * _grad_phi[_j][_qp] * _len_scale;

}
