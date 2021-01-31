#ifndef Q2_H
#define Q2_H

#include "Kernel.h"

class q2;

template <>
InputParameters validParams<q2>();

class q2 : public Kernel
{
public:
  q2(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian();

private:
  const unsigned int _component;
  const unsigned int _temperature_var;
  const VariableValue & _temperature;
  const VariableGradient & _temperature_grad;
  const MaterialProperty<Real> & _seebeck_coefficient;
  const Real _len_scale;
};
#endif
