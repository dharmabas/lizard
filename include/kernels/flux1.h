/*
   This file is part of HORNET, an add-on module for MOOSE

   HORNET is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

**/

#ifndef flux1_H
#define flux1_H

#include "Kernel.h"

class flux1;

template <>
InputParameters validParams<flux1>();

class flux1 : public Kernel
{
public:
  flux1(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const unsigned int _component;
  const Real _len_scale;
};
#endif
