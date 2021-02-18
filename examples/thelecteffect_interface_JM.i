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
    temperature = T
    component = 1
    block = 0
    electrical_conductivity = ecC
    thermal_conductivity = thC
    seebeck_coefficient = sbC
  [../]
  [./residualT_0]
    type = ResidualT
    variable = T
    temperature = T
    component = 1
    block = 0
    electrical_conductivity = ecC
    thermal_conductivity = thC
    seebeck_coefficient = sbC
  [../]


  ########BLOCK 1
  [./residualV_1]
    type = ResidualV
    variable = potential_E_int
    component = 1
    temperature = T
    block = 1
    electrical_conductivity = ecC
    thermal_conductivity = thC
    seebeck_coefficient = sbC
  [../]
  [./residualT_1]
    type = ResidualT
    variable = T
    component = 1
    temperature = T
    electrical_conductivity = ecC
    thermal_conductivity = thC
    seebeck_coefficient = sbC
    block = 1
  [../]
[]


[Materials]
  [./ThermoelectricProperties_block1]
    type = GenericConstantMaterial
    prop_names = 'ecC thC sbC'
    prop_values = '8.422e4 1.612 1.941e-4'
    block = 0
  [../]
  [./ThermoelectricProperties_block2]
    type = GenericConstantMaterial
    prop_names = 'ecC thC sbC'
    prop_values = '8.422e4 1.612 5.0e-3'
    block = 1
  [../]
[]

[BCs]

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
    value = 7.0
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
