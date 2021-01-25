#ifndef q1_H
#define q1_H

#include "Kernel.h"
#include "Material.h"

class q1;

template <>
InputParameters validParams<q1>();

class q1 : public Kernel
{
public:
  q1(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  // const MaterialProperty<Real> & _thermal_conductivity;
  const MaterialProperty<RankTwoTensor> & _thermal_conductivity_tensor; // for tensor inclusion
  const Real _len_scale;
};
#endif
