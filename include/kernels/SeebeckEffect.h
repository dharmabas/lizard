#ifndef SeebeckEffect_H
#define SeebeckEffect_H

#include "Kernel.h"

class SeebeckEffect; // this is the class i define by myself and not an existing moose object?//

template <>
InputParameters validParams<SeebeckEffect>();

class SeebeckEffect : public Kernel
{
public:
  SeebeckEffect(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const MaterialProperty<Real> & _electrical_conductivity;
  const MaterialProperty<Real> & _seebeck_coefficient;
  const Real _len_scale;
};
#endif
