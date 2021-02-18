#include "SideSet_TE_HeatTransferKernel.h"

registerMooseObject("HeatConductionApp", SideSet_TE_HeatTransferKernel);

template <>
InputParameters
validParams<SideSet_TE_HeatTransferKernel>()
{
  InputParameters params = validParams<InterfaceKernel>();
  params.addClassDescription("Modeling Peltier Effect across internal side set.");
  params.addCoupledVar("temperature", "Bulk temperature as variable");
  // params.addCoupledVar("potential", "Bulk potential as variable");

  // params.addParam<MaterialPropertyName>("temperature_mat","Bulk temperature of gap as material");

  params.addParam<MaterialPropertyName>("seebeck_coefficient_interface",
                                        "Seebeck coefficent for the interface");

  // params.addParam<MaterialPropertyName>("seebeck_coefficient_1","Seebeck coefficent for material
  // 1"); params.addParam<MaterialPropertyName>("seebeck_coefficient_2","Seebeck coefficent for
  // material 2"); params.addParam<MaterialPropertyName>("electrical_conductivity_1", "electrical
  // conductivity for material 1");
  // params.addParam<MaterialPropertyName>("electrical_conductivity_2", "electrical conductivity for
  // material 2");
  return params;
}

SideSet_TE_HeatTransferKernel::SideSet_TE_HeatTransferKernel(const InputParameters & parameters)
  : InterfaceKernel(parameters),
    _temperature(isParamValid("temperature") ? &coupledValue("temperature") : nullptr),
    // _Tbulk_mat(_Tbulk_var ? nullptr : &getMaterialProperty<Real>("Tbulk_mat")),

    //_potential(isParamValid("potential") ? &coupledValue("potential") : nullptr),

    // _temperature_var(coupled("temperature")),
    // _temperature(coupledValue("temperature")),
    // _temperature_grad(coupledGradient("temperature")),
    // _potential_E_int_var(coupled("potential_E_int")),
    // _potential_E_int(coupledValue("potential_E_int")),
    // _potential_E_int_grad(coupledGradient("potential_E_int")),

    //_component(getParam<unsigned int>("component")),
    _seebeck_coefficient_interface(getMaterialProperty<Real>("seebeck_coefficient_interface"))
// _seebeck_coefficient_1(getMaterialProperty<Real>("seebeck_coefficient_1")),
// _seebeck_coefficient_2(getMaterialProperty<Real>("seebeck_coefficient_2")),
// _electrical_conductivity_1(getMaterialProperty<Real>("electrical_conductivity_1")),
// _electrical_conductivity_2(getMaterialProperty<Real>("electrical_conductivity_2"))

{
  // if (parameters.isParamSetByUser("Tbulk_mat") && _Tbulk_var)
  //   paramError("Tbulk_var", "Both Tbulk_mat and Tbulk_var set by user, cannot use both.");
  //
  // if (_var.number() == _neighbor_var.number() && _var.isNodal())
  //   mooseError(
  //       "Variable and neighbor variable are the same, but they are not elemental variables.");
}

Real
SideSet_TE_HeatTransferKernel::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;
  // Real electrical_conductivity_interface = (electrical_conductivity_1[_qp] -
  // electrical_conductivity_2[_qp]);

  if (_seebeck_coefficient_interface[_qp] != 0.0) // Conduction
  {
    Real jump = _u[_qp] - _neighbor_value[_qp];
    switch (type)
    {
      case Moose::Element:
        r += _seebeck_coefficient_interface[_qp] * jump * _test[_i][_qp];
        break;

      case Moose::Neighbor:
        r -= _seebeck_coefficient_interface[_qp] * jump * _test_neighbor[_i][_qp];
        break;
    }
  }
  // if (seebeck_interface != 0.0)
  // {
  //   Real jump = _u[_qp] - _neighbor_value[_qp];
  //   switch (type)
  //   {
  //     case Moose::Element:
  //       r += seebeck_interface * jump * _test[_i][_qp];
  //       break;
  //
  //     case Moose::Neighbor:
  //       r -= seebeck_interface * jump * _test_neighbor[_i][_qp];
  //       break;
  //   }
  // }

  return r;
}

Real
SideSet_TE_HeatTransferKernel::computeQpJacobian(Moose::DGJacobianType type)
{
  Real jac = 0;

  if (_seebeck_coefficient_interface[_qp] != 0.0) // Conduction
  {
    switch (type)
    {
      case Moose::ElementElement:
        jac += _seebeck_coefficient_interface[_qp] * _phi[_j][_qp] * _test[_i][_qp];
        break;

      case Moose::NeighborNeighbor:
        jac +=
            _seebeck_coefficient_interface[_qp] * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
        break;

      case Moose::ElementNeighbor:
        jac -= _seebeck_coefficient_interface[_qp] * _phi_neighbor[_j][_qp] * _test[_i][_qp];
        break;

      case Moose::NeighborElement:
        jac -= _seebeck_coefficient_interface[_qp] * _phi[_j][_qp] * _test_neighbor[_i][_qp];
        break;
    }
  }
  // if (seebeck_interface != 0.0) // Conduction
  // {
  //   switch (type)
  //   {
  //     case Moose::ElementElement:
  //       jac += seebeck_interface * _phi[_j][_qp] * _test[_i][_qp];
  //       break;
  //
  //     case Moose::NeighborNeighbor:
  //       jac += seebeck_interface * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
  //       break;
  //
  //     case Moose::ElementNeighbor:
  //       jac -= seebeck_interface * _phi_neighbor[_j][_qp] * _test[_i][_qp];
  //       break;
  //
  //     case Moose::NeighborElement:
  //       jac -= seebeck_interface * _phi[_j][_qp] * _test_neighbor[_i][_qp];
  //       break;
  //   }
  // }

  return jac;
}
