[Mesh]
 [gen]
    ############################################
    ##
    ##  Type and dimension of the mesh 
    ##
    ############################################

    type = GeneratedMeshGenerator
    dim = 3


    nx = 4
    ny = 4
    nz = 50  

    xmin = -0.5
    xmax = 0.5
    ymin = -0.5
    ymax = 0.5
    zmin = -1.5
    zmax = 1.5

    #############################################
    ##
    ##  FE type/order (hexahedral, tetrahedral
    ##
    #############################################

    elem_type = HEX8
  []

  [subdomains]
    type = SubdomainBoundingBoxGenerator
    input = gen
    bottom_left = '-0.5 -0.5 -1.5'
    block_id = 1
    top_right = '0.5 0.5 0.0'
    location = INSIDE
  []
  [film_interface]
    type = SideSetsBetweenSubdomainsGenerator
    input = subdomains
    primary_block = 0
    paired_block = 1
    new_boundary = 52
  []
[]

[GlobalParams]
  T = T
  potential_E_int = potential_E_int
[]

[Variables]
  [./potential_E_int]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = RandomIC
      min = -0.1e-5
      max = 0.1e-5
    [../]
  [../]
  [./T]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = RandomIC
      min = -0.1e-5
      max = 0.1e-5
    [../]
  [../]
[]

[Kernels]
  ########BLOCK 1
  [./residualV_0]
    type = ResidualV
    variable = potential_E_int
    block = 0
  [../]
  [./residualT_0]
    type = ResidualT
    variable = T
    block = 0
  [../]


  ########BLOCK 1
  [./residualV_1]
    type = ResidualV
    variable = potential_E_int
    block = 1
  [../]
  [./residualT_1]
    type = ResidualT
    variable = T
    block = 1
  [../]
[]


[Materials]
  [./ThermoelectricProperties_block1]
    type = GenericConstantMaterial
    prop_names = 'ecC thC sbC'
    prop_values = '8.422e4 1.612 1.0e-4'
    block = 0
  [../]
  [./ThermoelectricProperties_block2]
    type = GenericConstantMaterial
    prop_names = 'ecC thC sbC'
    prop_values = '8.422e4 1.612 5.0e-3'
    block = 1
  [../]
[]

<<<<<<< HEAD
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

=======
[BCs]
>>>>>>> 6d6d7f608ea121693d8b139204cb9ef158c97c38

  [./side_potential_1]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'front'
    value = 0.116
  [../]
  [./side_potential_2]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'back'
    value = 0.0
  [../]

  [./side_temperature_1]
    type = DirichletBC
    variable = T
    boundary = 'front'
    value = 7.0
  [../]
  [./top_temperature_1]
    type = DirichletBC
    variable = T
    boundary = 'back'
    value = 7.1
  [../]
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

[]

[Outputs]
  exodus = true
  csv = true
  file_base = out_thermo4
[]
<<<<<<< HEAD
=======


>>>>>>> 6d6d7f608ea121693d8b139204cb9ef158c97c38
