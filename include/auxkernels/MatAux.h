#ifndef MatAux_H
#define MatAux_H

#include "AuxKernel.h"

// Forward declarations
class MatAux;

template <>
InputParameters validParams<MatAux>();

class MatAux : public AuxKernel
{
public:
  MatAux(const InputParameters & parameters);

  virtual ~MatAux() {}

protected:
  virtual Real computeValue();

private:
  const MaterialProperty<Real> & _mat_prop;
};

#endif //
