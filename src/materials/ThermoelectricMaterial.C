#include "ThermoelectricMaterial.h"
#include "Function.h"

#include "libmesh/quadrature.h"

registerMooseObject("lizardApp", ThermoelectricMaterial);
registerMooseObject("lizardApp", ADThermoelectricMaterial);

template <bool is_ad>
InputParameters
ThermoelectricMaterialTempl<is_ad>::validParams()
{
  InputParameters params = Material::validParams();

  params.addCoupledVar("temp", "Coupled Temperature");

  params.addParam<Real>("thermal_conductivity", "The thermal conductivity value");
  params.addParam<FunctionName>("thermal_conductivity_temperature_function","","Thermal conductivity as a function of temperature.");
  params.addParam<Real>("electrical_conductivity", "The electrical conductivity value");
  params.addParam<FunctionName>("electrical_conductivity_temperature_function", "", "electrical conductivity as a function of temperature.");
  params.addParam<Real>("seebeck_coefficient", "The seebeck coefficient value");
  params.addParam<FunctionName>("seebeck_coefficient_temperature_function", "", "seebeck coefficient as a function of temperature.");
  params.addClassDescription("General-purpose material model for thermoelectrics");

  return params;
}

template <bool is_ad>
ThermoelectricMaterialTempl<is_ad>::ThermoelectricMaterialTempl(const InputParameters & parameters)
  : Material(parameters),

    _has_temp(isCoupled("temp")),
    _temperature((_has_temp && !is_ad) ? coupledValue("temp") : _zero),
    _ad_temperature((_has_temp && is_ad) ? adCoupledValue("temp") : _ad_zero),
    _my_thermal_conductivity(isParamValid("thermal_conductivity") ? getParam<Real>("thermal_conductivity") : 0),
    _my_electrical_conductivity(isParamValid("electrical_conductivity") ? getParam<Real>("electrical_conductivity") : 0),
    _my_seebeck_coefficient(isParamValid("seebeck_coefficient") ? getParam<Real>("seebeck_coefficient") : 0),

    _thermal_conductivity(declareGenericProperty<Real, is_ad>("thermal_conductivity")),
    _thermal_conductivity_dT(declareProperty<Real>("thermal_conductivity_dT")),
    _thermal_conductivity_temperature_function(
        getParam<FunctionName>("thermal_conductivity_temperature_function") != ""
            ? &getFunction("thermal_conductivity_temperature_function")
            : NULL),

    _electrical_conductivity(declareGenericProperty<Real, is_ad>("electrical_conductivity")),
    _electrical_conductivity_dT(declareProperty<Real>("electrical_conductivity_dT")),
    _electrical_conductivity_temperature_function(
        getParam<FunctionName>("electrical_conductivity_temperature_function") != ""
            ? &getFunction("electrical_conductivity_temperature_function")
            : NULL),

    _seebeck_coefficient(declareGenericProperty<Real, is_ad>("seebeck_coefficient")),
    _seebeck_coefficient_dT(declareProperty<Real>("seebeck_coefficient_dT")),
    _seebeck_coefficient_temperature_function(
        getParam<FunctionName>("seebeck_coefficient_temperature_function") != ""
            ? &getFunction("seebeck_coefficient_temperature_function")
            : NULL)
{
  if (_thermal_conductivity_temperature_function && !_has_temp)
  {
    mooseError("Must couple with temperature if using thermal conductivity function");
  }
  if (isParamValid("thermal_conductivity") && _thermal_conductivity_temperature_function)
  {
    mooseError(
        "Cannot define both thermal conductivity and thermal conductivity temperature function");
  }
  if (_electrical_conductivity_temperature_function && !_has_temp)
  {
    mooseError("Must couple with temperature if using electrical conductivity function");
  }
  if (isParamValid("electrical_conductivity") && _electrical_conductivity_temperature_function)
  {
    mooseError(
        "Cannot define both electrical conductivity and electrical conductivity temperature function");
  }
  if (_seebeck_coefficient_temperature_function && !_has_temp)
  {
    mooseError("Must couple with temperature if using seebeck coefficient function");
  }
  if (isParamValid("seebeck_coefficient") && _seebeck_coefficient_temperature_function)
  {
    mooseError("Cannot define both seebeck coefficient and seebeck coefficient temperature function");
  }
}

template <bool is_ad>
void
ThermoelectricMaterialTempl<is_ad>::setDerivatives(GenericReal<is_ad> & prop,
                                                   Real dprop_dT,
                                                   const ADReal & ad_T)
{
  if (ad_T < 0)
    prop.derivatives() = 0;
  else
    prop.derivatives() = dprop_dT * ad_T.derivatives();
}

template <>
void
ThermoelectricMaterialTempl<false>::setDerivatives(Real &, Real, const ADReal &)
{
  mooseError("Mistaken call of setDerivatives in a non-AD ThermoelectricMaterial version");
}

template <bool is_ad>
void
ThermoelectricMaterialTempl<is_ad>::computeProperties()
{
  for (unsigned int qp(0); qp < _qrule->n_points(); ++qp)
  {
    Real qp_temperature = 0;
    if (_has_temp)
    {
      if (is_ad)
        qp_temperature = MetaPhysicL::raw_value(_ad_temperature[qp]);
      else
        qp_temperature = _temperature[qp];
      if (qp_temperature < 0)
      {
        std::stringstream msg;
        msg << "WARNING:  In ThermoelectricMaterial:  negative temperature!\n"
            << "\tResetting to zero.\n"
            << "\t_qp: " << qp << "\n"
            << "\ttemp: " << qp_temperature << "\n"
            << "\telem: " << _current_elem->id() << "\n"
            << "\tproc: " << processor_id() << "\n";
        mooseWarning(msg.str());
        qp_temperature = 0;
      }
    }
    if (_thermal_conductivity_temperature_function)
    {
      Point p;
      _thermal_conductivity[qp] =
          _thermal_conductivity_temperature_function->value(qp_temperature, p);
      // A terrible exploitation of the Function API to get a derivative with respect to a
      // non-linear variable
      _thermal_conductivity_dT[qp] =
          _thermal_conductivity_temperature_function->timeDerivative(qp_temperature, p);
      if (is_ad)
        setDerivatives(
            _thermal_conductivity[qp], _thermal_conductivity_dT[qp], _ad_temperature[qp]);
    }
    else
    {
      _thermal_conductivity[qp] = _my_thermal_conductivity;
      _thermal_conductivity_dT[qp] = 0;
    }

    if (_electrical_conductivity_temperature_function)
    {
      Point p;
      _electrical_conductivity[qp] =
          _electrical_conductivity_temperature_function->value(qp_temperature, p);
      // A terrible exploitation of the Function API to get a derivative with respect to a
      // non-linear variable
      _electrical_conductivity_dT[qp] =
          _electrical_conductivity_temperature_function->timeDerivative(qp_temperature, p);
      if (is_ad)
        setDerivatives(
            _electrical_conductivity[qp], _electrical_conductivity_dT[qp], _ad_temperature[qp]);
    }
    else
    {
      _electrical_conductivity[qp] = _my_electrical_conductivity;
      _electrical_conductivity_dT[qp] = 0;
    }

    if (_seebeck_coefficient_temperature_function)
    {
      Point p;
      _seebeck_coefficient[qp] =
          _seebeck_coefficient_temperature_function->value(qp_temperature, p);
      // A terrible exploitation of the Function API to get a derivative with respect to a
      // non-linear variable
      _seebeck_coefficient_dT[qp] =
          _seebeck_coefficient_temperature_function->timeDerivative(qp_temperature, p);
      if (is_ad)
        setDerivatives(
            _seebeck_coefficient[qp], _seebeck_coefficient_dT[qp], _ad_temperature[qp]);
    }
    else
    {
      _seebeck_coefficient[qp] = _my_seebeck_coefficient;
      _seebeck_coefficient_dT[qp] = 0;
    }
  }
}

template class ThermoelectricMaterialTempl<false>;
template class ThermoelectricMaterialTempl<true>;
