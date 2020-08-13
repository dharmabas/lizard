#include "CurrentAux.h"

registerMooseObject("lizardApp", CurrentAux);

template<>
InputParameters validParams<CurrentAux> ()
{
InputParameters params = validParams<AuxKernel>();
params.addClassDescription("Find current component across the Mesh");
params.addRequiredCoupledVar("potential_E_int", "electrostatic potential");
params.addRequiredParam<unsigned int>("component", "an integer corresponding to direction");
params.addParam<MaterialPropertyName>("electrical_conductivity", "Electrical Conductivity", "Property name of the electrical conductivity material property");
//params.addParam<Real>("dx", "delta x");
return params;
}

CurrentAux::CurrentAux(const InputParameters & parameters):
AuxKernel(parameters),
_potential_E_int(coupledValue("potential_E_int")),
_potential_E_int_grad(coupledGradient("potential_E_int")),
_component(getParam<unsigned int>("component")),
_electrical_conductivity(getMaterialProperty<Real>("electrical_conductivity"))
//_dx(getParam<Real>("dx"))
{

}

Real
CurrentAux::computeValue()
{
return _electrical_conductivity[_qp] * _potential_E_int_grad[_qp](_component);

}
