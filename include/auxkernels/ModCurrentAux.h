#ifndef ModCurrentAux_H
#define ModCurrentAux_H

#include "AuxKernel.h"

class ModCurrentAux;

template<>
InputParameters validParams<ModCurrentAux>();

class ModCurrentAux : public AuxKernel
{
public:
ModCurrentAux(const InputParameters & parameters);

virtual ~ModCurrentAux() {}

protected:
virtual Real computeValue();

private:
const VariableValue & _potential_E_int;
const VariableGradient & _potential_E_int_grad;
const VariableValue & _temperature;
const VariableGradient & _temperature_grad;
const unsigned int _component;
const MaterialProperty<Real> & _electrical_conductivity;
const MaterialProperty<Real> & _seebeck_coefficient;
//const Real _dx;

};

#endif
