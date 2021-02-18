//
// #ifndef TE_fluxBC_H
// #define TE_fluxBC_H
//
// #include "IntegratedBC.h"
//
// class TE_fluxBC;
//
// template <>
// InputParameters validParams<TE_fluxBC>();
//
// class TE_fluxBC : public IntegratedBC
// {
// public:
//   TE_fluxBC(const InputParameters & parameters);
//
// protected:
//   virtual Real computeQpResidual() override;
//   virtual Real computeQpJacobian() override;
//   const MaterialProperty<Real> * _diff;
// };
//
// #endif /* TE_fluxBC_H */

#ifndef TE_fluxBC_H
#define TE_fluxBC_H

#include "IntegratedBC.h"

class TE_fluxBC;

template <>
InputParameters validParams<TE_fluxBC>();

class TE_fluxBC : public IntegratedBC
{
public:
  TE_fluxBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  const MaterialProperty<Real> & _seebeck_coefficient_interface;
};

#endif /* TE_fluxBC_H */
