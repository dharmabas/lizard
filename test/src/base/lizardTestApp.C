//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "lizardTestApp.h"
#include "lizardApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
lizardTestApp::validParams()
{
  InputParameters params = lizardApp::validParams();
  return params;
}

lizardTestApp::lizardTestApp(InputParameters parameters) : MooseApp(parameters)
{
  lizardTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

lizardTestApp::~lizardTestApp() {}

void
lizardTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  lizardApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"lizardTestApp"});
    Registry::registerActionsTo(af, {"lizardTestApp"});
  }
}

void
lizardTestApp::registerApps()
{
  registerApp(lizardApp);
  registerApp(lizardTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
lizardTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  lizardTestApp::registerAll(f, af, s);
}
extern "C" void
lizardTestApp__registerApps()
{
  lizardTestApp::registerApps();
}
