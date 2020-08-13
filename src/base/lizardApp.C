#include "lizardApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
lizardApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  // Do not use legacy DirichletBC, that is, set DirichletBC default for preset = true
  params.set<bool>("use_legacy_dirichlet_bc") = false;

  return params;
}

lizardApp::lizardApp(InputParameters parameters) : MooseApp(parameters)
{
  lizardApp::registerAll(_factory, _action_factory, _syntax);
}

lizardApp::~lizardApp() {}

void
lizardApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"lizardApp"});
  Registry::registerActionsTo(af, {"lizardApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
lizardApp::registerApps()
{
  registerApp(lizardApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
lizardApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  lizardApp::registerAll(f, af, s);
}
extern "C" void
lizardApp__registerApps()
{
  lizardApp::registerApps();
}
