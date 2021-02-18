// Takes density parameter from materials block
#include "MatAux.h"

registerMooseObject("lizardApp", MatAux);

template <>
InputParameters
validParams<MatAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Sanity Check for Material property");
  params.addRequiredParam<MaterialPropertyName>("mat_prop", "material property");
  return params;
}

MatAux::MatAux(const InputParameters & parameters)
  : AuxKernel(parameters), _mat_prop(getMaterialProperty<Real>("mat_prop"))
{
}

Real
MatAux::computeValue()

{
  return _mat_prop[_qp];
}
