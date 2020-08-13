#ifndef potential_update_H
#define potential_update_H

#include "AuxKernel.h"

class potential_update;

template<>
InputParameters validParams<potential_update>();

class potential_update : public AuxKernel
{
public:
potential_update(const InputParameters & parameters);

virtual ~potential_update() {}

protected:
virtual Real computeValue();

private:

const VariableValue & _temperature;
const VariableGradient & _temperature_grad;
const MaterialProperty<Real> & _seebeck_coefficient;
//const Real _dx;

};

#endif
