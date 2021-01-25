[Mesh]
  file = thermopair.e
[]

[Variables]
  [./potential_E_int]
    order = FIRST
    family = LAGRANGE
  [../]
  [./temperature]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./residualV_x]
    type = ResidualV
    component = 0
    variable = potential_E_int
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
  [../]

  [./residualV_y]
    type = ResidualV
    component = 1
    variable = potential_E_int
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
  [../]

  [./residualV_z]
    type = ResidualV
    component = 2
    variable = potential_E_int
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
  [../]

  [./residualT_x]
    type = ResidualT
    component = 0
    variable = temperature
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    thermal_conductivity = 'thermal_conductivity'
  [../]

  [./residualT_y]
    type = ResidualT
    component = 1
    variable = temperature
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    thermal_conductivity = 'thermal_conductivity'
  [../]

  [./residualT_z]
    type = ResidualT
    component = 2
    variable = temperature
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    thermal_conductivity = 'thermal_conductivity'
  [../]
[]

[AuxVariables]
  [./j_x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./j_y]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./j_z]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./q_x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./q_y]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./q_z]
    order = CONSTANT
    family = MONOMIAL
  [../]
  []

[AuxKernels]
  [./Electric_flux_x]
    type = Electric_flux
    variable = j_x
    temperature = temperature
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 0
  [../]
  [./Electric_flux_y]
    type = Electric_flux
    variable = j_y
    temperature = temperature
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 1
  [../]
  [./Electric_flux_z]
    type = Electric_flux
    variable = j_z
    temperature = temperature
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 2
  [../]

  [./Heat_flux_x]
    type = Heat_flux
    variable = q_x
    temperature = 'temperature'
    thermal_conductivity = 'thermal_conductivity'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 0
  [../]
  [./heat_flux_y]
    type = Heat_flux
    variable = q_y
    temperature = 'temperature'
    thermal_conductivity = 'thermal_conductivity'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 1
  [../]
  [./Heat_flux_z]
    type = Heat_flux
    variable = q_z
    temperature = 'temperature'
    thermal_conductivity = 'thermal_conductivity'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 2
  [../]
[]

#####Temperature Dependent Input Parameters
  [Functions]
  #   [./k_func]
  #     type = ParsedFunction
  #     value = '1.758 - 5.290e-3 * t + 4.134e-5 * t^2'
  #   [../]
  #   [./lam_func]
  #     type = ParsedFunction
  #     value = '1.028e5 - 5.369e2 * t + 1.824 * t^2'
  #   [../]
  #   [./eps_func]
  #     type = ParsedFunction
  #     value = '1.802e-4 + 3.861e-7 * t - 9.582e-10 * t^2'
  #   [../]
  # []
  # [Functions]
  #   [./k_func]
  #     type = PiecewiseLinear
  #     x = '300 400 500 600 700 800'
  #     y = '140 100 80 60 50 40'
  #   [../]
  #   [./lam_func]
  #     type = PiecewiseLinear
  #     x = '300 400 500 600 700 800'
  #     y = '1000 2000 3000 4000 5000 6000'
  #   [../]
  #   [./eps_func]
  #     type = PiecewiseLinear
  #     x = '300 400 500 600 700 800'
  #     y = '300e-6 300e-6 300e-6 300e-6 300e-6 300e-6'
  #   [../]
  []


 [Materials]
   ####Static Parameters
    [./ThermoelectricProperties_1]
     type = GenericConstantMaterial
     prop_names = 'electrical_conductivity thermal_conductivity seebeck_coefficient'
     prop_values = '8.422e4 1.612 1.941e-4'
     block = 1
    [../]
    [./ThermoelectricProperties_2]
     type = GenericConstantMaterial
     prop_names = 'electrical_conductivity thermal_conductivity seebeck_coefficient'
     prop_values = '8.422e4 1.612 2.0e-4'
     block = 2
    [../]

###Temp dependent parameters
  #
  #   [./ThermoelectricProperties]
  #    type = ThermoelectricMaterial
  #    temp = 'temperature'
  #    thermal_conductivity_temperature_function = k_func
  #    electrical_conductivity_temperature_function = lam_func
  #    seebeck_coefficient_temperature_function = eps_func
  #   [../]
  []

  # [ICs]
  #   [./Block_1]
  #     type = ConstantIC
  #     variable = temperature
  #     block = 1
  #     value = 7
  #   [../]
  #   [./Block_2]
  #     type = ConstantIC
  #     variable = temperature
  #     block = 2
  #     value = 7
  #   [../]
  # []


[BCs]
  [./interface_temperature]
    type = NeumannBC
    variable = temperature
    boundary = '3'
    value = 1
  [../]
  # [./interface_temperature]
  #   type = Thermoelectric_InterfaceBC
  #   variable = temperature
  #   temperature = temperature
  #   potential_E_int = potential_E_int
  #   seebeck_coefficient_1 = 1.941e-4
  #   seebeck_coefficient_2 = 2e-4
  #   component = 2
  #   boundary = '3'
  # [../]
  # [./interface_temperature]
  #   type = TE_InterfaceBC
  #     variable = temperature
  #     temperature = temperature
  #     potential_E_int = potential_E_int
  #     seebeck_coefficient_1 = 1.941e-4
  #     seebeck_coefficient_2 = 2e-4
  #     component = 2
  #     value = 0
  #   boundary = '3'
  # [../]


  [./side_temperature_1]
    type = DirichletBC
    variable = temperature
    boundary = '1'
    value = 0
  [../]
  [./top_temperature_1]
    type = DirichletBC
    variable = temperature
    boundary = '9'
    value = 0
  [../]
  [./bottom_temperature_1]
    type = DirichletBC
    variable = temperature
    boundary = '5'
    value = 0
  [../]
  [./front_temperature_1]
    type = NeumannBC
    variable = temperature
    boundary = '7'
    value = 0
  [../]
  [./back_temperature_1]
    type = NeumannBC
    variable = temperature
    boundary = '11'
    value = 0
  [../]


  [./side_temperature_2]
    type = DirichletBC
    variable = temperature
    boundary = '2'
    value = 0
  [../]
  [./top_temperature_2]
    type = DirichletBC
    variable = temperature
    boundary = '8'
    value = 0
  [../]
  [./bottom_temperature_2]
    type = DirichletBC
    variable = temperature
    boundary = '4'
    value = 0
  [../]
  [./front_temperature_2]
    type = NeumannBC
    variable = temperature
    boundary = '6'
    value = 0
  [../]
  [./back_temperature_2]
    type = NeumannBC
    variable = temperature
    boundary = '10'
    value = 0
  [../]


  [./side_potential_1]
    type = DirichletBC
    variable = potential_E_int
    boundary = '1'
    value = 0.116
  [../]
  [./top_potential_1]
    type = NeumannBC
    variable = potential_E_int
    boundary = '9'
    value = 0
  [../]
  [./bottom_potential_1]
    type = NeumannBC
    variable = potential_E_int
    boundary = '5'
    value = 0
  [../]
  [./front_potential_1]
    type = NeumannBC
    variable = potential_E_int
    boundary = '7'
    value = 0
  [../]
  [./back_potential_1]
    type = NeumannBC
    variable = potential_E_int
    boundary = '11'
    value = 0
  [../]


  [./side_potential_2]
    type = DirichletBC
    variable = potential_E_int
    boundary = '2'
    value = 0
  [../]
  [./top_potential_2]
    type = NeumannBC
    variable = potential_E_int
    boundary = '8'
    value = 0
  [../]
  [./bottom_potential_2]
    type = NeumannBC
    variable = potential_E_int
    boundary = '4'
    value = 0
  [../]
  [./front_potential_2]
    type = NeumannBC
    variable = potential_E_int
    boundary = '6'
    value = 0
  [../]
  [./back_potential_2]
    type = NeumannBC
    variable = potential_E_int
    boundary = '10'
    value = 0
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  line_search = none
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]

[Postprocessors]
  [./potential_x]
    type = PointValue
    point = '0 0 0'
    variable = potential_E_int
  [../]
  [./temperature]
    type = PointValue
    point = '0 0 0'
    variable = temperature
  [../]
[]

[Outputs]
  exodus = true
  csv = true
[]

[Debug]
  show_var_residual_norms = true
[]
