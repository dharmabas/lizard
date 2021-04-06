[Mesh]
 [gen]
    ############################################
    ##
    ##  Type and dimension of the mesh
    ##
    ############################################

    # type = GeneratedMeshGenerator
    # dim = 3
    #
    #
    # nx = 4
    # ny = 4
    # nz = 50
    #
    # xmin = -0.5
    # xmax = 0.5
    # ymin = -0.5
    # ymax = 0.5
    # zmin = -1.5
    # zmax = 1.5
    # elem_type = HEX8
    #############################################
    ##
    ##  FE type/order (hexahedral, tetrahedral
    ##
    #############################################

    type = GeneratedMeshGenerator
    dim = 3
    nx = 30
    ny = 30
    nz = 60
    xmin = -0.0007
    xmax = 0.0007
    ymin = -0.0007
    ymax = 0.0007
    zmin = -0.001524
    zmax = 0.001524
    elem_type = HEX8

  []

#   [subdomains]
#     type = SubdomainBoundingBoxGenerator
#     input = gen
#     bottom_left = '-0.5 -0.5 -1.5'
#     block_id = 1
#     top_right = '0.5 0.5 0.0'
#     location = INSIDE
#   []
#   [film_interface]
#     type = SideSetsBetweenSubdomainsGenerator
#     input = subdomains
#     primary_block = 0
#     paired_block = 1
#     new_boundary = 52
#   []
# []
[./subdomain1]
    input = gen
    type = SubdomainBoundingBoxGenerator
    bottom_left = '-0.0007 -0.0007 -0.001524'
    top_right = '0.0007 0.0007 0'
    block_id = 1
    location = INSIDE
  [../]
  [./interface]
    type = SideSetsBetweenSubdomainsGenerator
    input = subdomain1
    primary_block = '0'
    paired_block = '1'
    new_boundary = 'primary0_interface'
    # new_boundary = 52
  [../]
  [./break_boundary]
    input = interface
    type = BreakBoundaryOnSubdomainGenerator
  [../]
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
    T = T
    component = 1
    block = 0
    ecC = ecC
    thC = thC
    sbC = sbC
  [../]
  [./residualT_0]
    type = ResidualT
    variable = T
    T = T
    component = 1
    block = 0
    ecC = ecC
    thC = thC
    sbC = sbC
  [../]


  ########BLOCK 1
  [./residualV_1]
    type = ResidualV
    variable = potential_E_int
    component = 0
    T = T
    block = 1
    ecC = ecC
    thC = thC
    sbC = sbC
  [../]
  [./residualT_1]
    type = ResidualT
    variable = T
    component = 0
    T = T
    ecC = ecC
    thC = thC
    sbC = sbC
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
    prop_values = '8.422e4 1.612 -1.94e-4'
    block = 1
  [../]
[]

# [InterfaceKernels]
#   [./interface]
#     type = PenaltyInterfaceDiffusion
#     variable = T
#     neighbor_var = potential_E_int
#     boundary = primary0_interface
#     penalty = 1e6
#   [../]
# []

[BCs]

  [./side_potential_front]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'front'
    value = 0
  [../]
  [./side_potential_back]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'back'
    value = 0.116
  [../]
  [./side_potential_top]
    type = NeumannBC
    variable = potential_E_int
    boundary = 'top'
    value = 0
  [../]
  [./side_potential_bottom]
    type = NeumannBC
    variable = potential_E_int
    boundary = 'bottom'
    value = 0
  [../]
  [./side_potential_left]
    type = NeumannBC
    variable = potential_E_int
    boundary = 'left'
    value = 0
  [../]
  [./side_potential_right]
    type = NeumannBC
    variable = potential_E_int
    boundary = 'right'
    value = 0
  [../]

  [./side_T_front]
    type = DirichletBC
    variable = T
    boundary = 'front'
    value = 280.0
  [../]
  [./side_T_back]
    type = DirichletBC
    variable = T
    boundary = 'back'
    value = 280.0
  [../]
  [./side_T_left]
    type = DirichletBC
    variable = T
    boundary = 'left'
    value = 280.0
  [../]
  [./top_T_right]
    type = DirichletBC
    variable = T
    boundary = 'right'
    value = 280.0
  [../]
  [./side_T_top]
    type = DirichletBC
    variable = T
    boundary = 'top'
    value = 280.0
  [../]
  [./top_T_bottom]
    type = DirichletBC
    variable = T
    boundary = 'bottom'
    value = 280.0
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  end_time = 10

  [./TimeStepper]
    # type = IterationAdaptiveDT
    # optimal_iterations = 5
    # iteration_window = 2
    # dt = 0.1
    # growth_factor = 1.1
    # cutback_factor = 0.75
    type = ConstantDT
    dt = 1
  [../]
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
  file_base = out_thermoelectric_interface
  []
