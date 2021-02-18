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
  ########BLOCK 1
  [./residualV_x_1]
    type = ResidualV
    component = 0
    variable = potential_E_int
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_1'
    seebeck_coefficient = 'seebeck_coefficient_1'
    block = 1
  [../]

  [./residualV_y_1]
    type = ResidualV
    component = 1
    variable = potential_E_int
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_1'
    seebeck_coefficient = 'seebeck_coefficient_1'
    block = 1
  [../]

  [./residualV_z_1]
    type = ResidualV
    component = 2
    variable = potential_E_int
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_1'
    seebeck_coefficient = 'seebeck_coefficient_1'
    block = 1
  [../]

  [./residualT_x_1]
    type = ResidualT
    component = 0
    variable = temperature
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_1'
    seebeck_coefficient = 'seebeck_coefficient_1'
    thermal_conductivity = 'thermal_conductivity_1'
    block = 1
  [../]

  [./residualT_y_1]
    type = ResidualT
    component = 1
    variable = temperature
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_1'
    seebeck_coefficient = 'seebeck_coefficient_1'
    thermal_conductivity = 'thermal_conductivity_1'
    block = 1
  [../]

  [./residualT_z_1]
    type = ResidualT
    component = 2
    variable = temperature
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_1'
    seebeck_coefficient = 'seebeck_coefficient_1'
    thermal_conductivity = 'thermal_conductivity_1'
    block = 1
  [../]


  ########BLOCK 2
  [./residualV_x_2]
    type = ResidualV
    component = 0
    variable = potential_E_int
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_2'
    seebeck_coefficient = 'seebeck_coefficient_2'
    block = 2
  [../]

  [./residualV_y_2]
    type = ResidualV
    component = 1
    variable = potential_E_int
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_2'
    seebeck_coefficient = 'seebeck_coefficient_2'
    block = 2
  [../]

  [./residualV_z_2]
    type = ResidualV
    component = 2
    variable = potential_E_int
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_2'
    seebeck_coefficient = 'seebeck_coefficient_2'
    block = 2
  [../]

  [./residualT_x_2]
    type = ResidualT
    component = 0
    variable = temperature
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_2'
    seebeck_coefficient = 'seebeck_coefficient_2'
    thermal_conductivity = 'thermal_conductivity_2'
    block = 2
  [../]

  [./residualT_y_2]
    type = ResidualT
    component = 1
    variable = temperature
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_2'
    seebeck_coefficient = 'seebeck_coefficient_2'
    thermal_conductivity = 'thermal_conductivity_2'
    block = 2
  [../]

  [./residualT_z_2]
    type = ResidualT
    component = 2
    variable = temperature
    temperature = 'temperature'
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity_2'
    seebeck_coefficient = 'seebeck_coefficient_2'
    thermal_conductivity = 'thermal_conductivity_2'
    block = 2
  [../]


  ######INTERFACE
  # [./Interface]
  #   type = TE_interfacekernel
  #   component = 2
  #   variable = temperature
  #   temperature = 'temperature'
  #   potential_E_int = 'potential_E_int'
  #   electrical_conductivity = '8.422e4'
  #   seebeck_coefficient_1 = '1.941e-4'
  #   seebeck_coefficient_2 = '2e-4'
  #   sideset = 3
  # [../]
[]

# [AuxVariables]
#   [./j_x]
#     order = CONSTANT
#     family = MONOMIAL
#   [../]
#   [./j_y]
#     order = CONSTANT
#     family = MONOMIAL
#   [../]
#   [./j_z]
#     order = CONSTANT
#     family = MONOMIAL
#   [../]
#
#   [./q_x]
#     order = CONSTANT
#     family = MONOMIAL
#   [../]
#   [./q_y]
#     order = CONSTANT
#     family = MONOMIAL
#   [../]
#   [./q_z]
#     order = CONSTANT
#     family = MONOMIAL
#   [../]
#   []

# [AuxKernels]
#   [./Electric_flux_x]
#     type = Electric_flux
#     variable = j_x
#     temperature = temperature
#     electrical_conductivity = 'electrical_conductivity'
#     seebeck_coefficient = 'seebeck_coefficient'
#     potential_E_int = 'potential_E_int'
#     component = 0
#   [../]
#   [./Electric_flux_y]
#     type = Electric_flux
#     variable = j_y
#     temperature = temperature
#     electrical_conductivity = 'electrical_conductivity'
#     seebeck_coefficient = 'seebeck_coefficient'
#     potential_E_int = 'potential_E_int'
#     component = 1
#   [../]
#   [./Electric_flux_z]
#     type = Electric_flux
#     variable = j_z
#     temperature = temperature
#     electrical_conductivity = 'electrical_conductivity'
#     seebeck_coefficient = 'seebeck_coefficient'
#     potential_E_int = 'potential_E_int'
#     component = 2
#   [../]
#
#   [./Heat_flux_x]
#     type = Heat_flux
#     variable = q_x
#     temperature = 'temperature'
#     thermal_conductivity = 'thermal_conductivity'
#     electrical_conductivity = 'electrical_conductivity'
#     seebeck_coefficient = 'seebeck_coefficient'
#     potential_E_int = 'potential_E_int'
#     component = 0
#   [../]
#   [./heat_flux_y]
#     type = Heat_flux
#     variable = q_y
#     temperature = 'temperature'
#     thermal_conductivity = 'thermal_conductivity'
#     electrical_conductivity = 'electrical_conductivity'
#     seebeck_coefficient = 'seebeck_coefficient'
#     potential_E_int = 'potential_E_int'
#     component = 1
#   [../]
#   [./Heat_flux_z]
#     type = Heat_flux
#     variable = q_z
#     temperature = 'temperature'
#     thermal_conductivity = 'thermal_conductivity'
#     electrical_conductivity = 'electrical_conductivity'
#     seebeck_coefficient = 'seebeck_coefficient'
#     potential_E_int = 'potential_E_int'
#     component = 2
#   [../]
# []

#####Temperature Dependent Input Parameters
  [Functions]
    # [./k_func]
    #   type = ParsedFunction
    #   value = '1.758 - 5.290e-3 * t + 4.134e-5 * t^2'
    # [../]
    # [./lam_func]
    #   type = ParsedFunction
    #   value = '1.028e5 - 5.369e2 * t + 1.824 * t^2'
    # [../]
    # [./eps_func]
    #   type = ParsedFunction
    #   value = '1.802e-4 + 3.861e-7 * t - 9.582e-10 * t^2'
    # [../]


    [./k_func]
      type = PiecewiseLinear
      x = '300 400 500 600 700 800'
      y = '140 100 80 60 50 40'
    [../]
    [./lam_func]
      type = PiecewiseLinear
      x = '300 400 500 600 700 800'
      y = '1000 2000 3000 4000 5000 6000'
    [../]
    [./eps_func]
      type = PiecewiseLinear
      x = '300 400 500 600 700 800'
      y = '300e-6 300e-6 300e-6 300e-6 300e-6 300e-6'
    [../]
  []


 [Materials]
   ####Static Parameters
    [./ThermoelectricProperties_1]
     type = GenericConstantMaterial
     prop_names = 'electrical_conductivity_1 thermal_conductivity_1 seebeck_coefficient_1'
     prop_values = '8.422e4 1.612 5.0e-3'
     block = 1
    [../]
    [./ThermoelectricProperties_2]
     type = GenericConstantMaterial
     prop_names = 'electrical_conductivity_2 thermal_conductivity_2 seebeck_coefficient_2'
     prop_values = '8.422e4 1.612 1.0e-4'
     block = 2
    [../]

###Temp dependent parameters
  #
    # [./ThermoelectricProperties]
    #  type = ThermoelectricMaterial
    #  temp = 'temperature'
    #  thermal_conductivity_temperature_function = k_func
    #  electrical_conductivity_temperature_function = lam_func
    #  seebeck_coefficient_temperature_function = eps_func
    # [../]
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

  # [InterfaceKernels]
  #   [./Interface]
  #     type = ConjugateHeatTransfer_lizard
  #     variable = temperature
  #     temperature = temperature
  #     potential_E_int = potential_E_int
  #     neighbor_var = 'temperature'
  #     boundary = '3'
  #     seebeck_coefficient_1 = '1.941e-4'
  #     seebeck_coefficient_2 = '2.0e-4'
  #     electrical_conductivity = 8.422e4
  #     component = 2
  #   [../]
  # []

[BCs]
  # [./interface_temperature]
  #   type = DirichletBC
  #   variable = temperature
  #   boundary = '3'
  #   value = 500
  # [../]
  # [./interface_temperature]
  #   type = Thermoelectric_InterfaceBC
  #   variable = temperature
  #   temperature = temperature
  #   potential_E_int = potential_E_int
  #   ##value = -5.0
  #   value_1 = 1.941e-4
  #   value_2 = 2e-4
  #   electrical_conductivity = 8.422e4
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
    value = 7
  [../]
  # [./top_temperature_1]
  #   type = DirichletBC
  #   variable = temperature
  #   boundary = '9'
  #   value = 7
  # [../]
  # [./bottom_temperature_1]
  #   type = DirichletBC
  #   variable = temperature
  #   boundary = '5'
  #   value = 7
  # [../]
  # [./front_temperature_1]
  #   type = NeumannBC
  #   variable = temperature
  #   boundary = '7'
  #   value = 0
  # [../]
  # [./back_temperature_1]
  #   type = NeumannBC
  #   variable = temperature
  #   boundary = '11'
  #   value = 0
  # [../]


  [./side_temperature_2]
    type = DirichletBC
    variable = temperature
    boundary = '2'
    value = 7
  [../]
  # [./top_temperature_2]
  #   type = DirichletBC
  #   variable = temperature
  #   boundary = '8'
  #   value = 7
  # [../]
  # [./bottom_temperature_2]
  #   type = DirichletBC
  #   variable = temperature
  #   boundary = '4'
  #   value = 7
  # [../]
  # [./front_temperature_2]
  #   type = NeumannBC
  #   variable = temperature
  #   boundary = '6'
  #   value = 0
  # [../]
  # [./back_temperature_2]
  #   type = NeumannBC
  #   variable = temperature
  #   boundary = '10'
  #   value = 0
  # [../]


  [./side_potential_1]
    type = DirichletBC
    variable = potential_E_int
    boundary = '1'
    value = 0.116
  [../]
  # [./top_potential_1]
  #   type = NeumannBC
  #   variable = potential_E_int
  #   boundary = '9'
  #   value = 0
  # [../]
  # [./bottom_potential_1]
  #   type = NeumannBC
  #   variable = potential_E_int
  #   boundary = '5'
  #   value = 0
  # [../]
  # [./front_potential_1]
  #   type = NeumannBC
  #   variable = potential_E_int
  #   boundary = '7'
  #   value = 0
  # [../]
  # [./back_potential_1]
  #   type = NeumannBC
  #   variable = potential_E_int
  #   boundary = '11'
  #   value = 0
  # [../]


  [./side_potential_2]
    type = DirichletBC
    variable = potential_E_int
    boundary = '2'
    value = 0
  [../]
  # [./top_potential_2]
  #   type = NeumannBC
  #   variable = potential_E_int
  #   boundary = '8'
  #   value = 0
  # [../]
  # [./bottom_potential_2]
  #   type = NeumannBC
  #   variable = potential_E_int
  #   boundary = '4'
  #   value = 0
  # [../]
  # [./front_potential_2]
  #   type = NeumannBC
  #   variable = potential_E_int
  #   boundary = '6'
  #   value = 0
  # [../]
  # [./back_potential_2]
  #   type = NeumannBC
  #   variable = potential_E_int
  #   boundary = '10'
  #   value = 0
  # [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
[]

[Debug]
  show_var_residual_norms = true
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
    petsc_options_value = ' lu       NONZERO               1e-10'
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
