[Mesh]
 [gen]
    ############################################
    ##
    ##  Type and dimension of the mesh
    ##
    ############################################

    type = GeneratedMeshGenerator
    dim = 3
    nx = 30
    ny = 30
    nz = 60
    xmin = -0.0007
    xmax = 0.0007
    ymin = -0.0007
    ymax = 0.0007
    zmin = -0.015
    zmax = 0.015
    elem_type = HEX8
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
      min = -0.1e-10
      max = 0.1e-10
    [../]
  [../]
  [./T]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = RandomIC
      min = 0
      max = 0.1e-10
    [../]
  [../]
[]

[Functions]
  [./sbC_function]
    type = PiecewiseLinear
    data_file = Typek_SeebeckCoefficient_input.csv
  [../]
[]

[Kernels]
  ########Time Dependence
  # [./dTdt]
  #   type = TimeDerivative
  #   variable = T
  # [../]

  ########BLOCK 1
  [./Seebeck_1_x]
    type = SeebeckEffect
    variable = potential_E_int
    potential_E_int = 'potential_E_int'
    T = 'T'
    sbC = 'seebeck_coefficient'
    component = 0
  [../]
  [./Seebeck_1_y]
    type = SeebeckEffect
    variable = potential_E_int
    potential_E_int = 'potential_E_int'
    T = 'T'
    sbC = 'seebeck_coefficient'
    component = 1
  [../]
  [./Seebeck_1_z]
    type = SeebeckEffect
    variable = potential_E_int
    potential_E_int = 'potential_E_int'
    T = 'T'
    sbC = 'seebeck_coefficient'
    component = 2
  [../]

  [./q1_1_x]
    type = q1
    variable = T
    T = 'T'
    thC = 'thermal_conductivity'
    component = 0
  [../]
  [./q1_1_y]
    type = q1
    variable = T
    T = 'T'
    thC = 'thermal_conductivity'
    component = 1
  [../]
  [./q1_1_z]
    type = q1
    variable = T
    T = 'T'
    thC = 'thermal_conductivity'
    component = 2
  [../]

[]


[Materials]

  ###Constant Seebeck
  # [./ThermoelectricProperties_block1]
  #   type = GenericConstantMaterial
  #   prop_names = 'ecC thermal_conductivity seebeck_coefficient'
  #   prop_values = '8.422e4 1.612 0.0000414'
  #   block = 0
  # [../]

  ###Temperature Dependent Seebeck
  [./ThermoelectricProperties_block1]
    type = ThermoelectricMaterial
    temp = T
    seebeck_coefficient_temperature_function = sbC_function
    thermal_conductivity = 1.612
    electrical_conductivity = 8.422e4
    block = 0
  [../]

[]

[BCs]
  [./left_temperature]
    type = DirichletBC
    variable = T
    boundary = 'front'
    value = 273
  [../]
  [./right_temperature]
    type = DirichletBC
    variable = T
    boundary = 'back'
    value = 350
  [../]


  [./right_potential]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'back'
    value = 0
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  #end_time = 10

  # [./TimeStepper]
  #   # type = IterationAdaptiveDT
  #   # optimal_iterations = 5
  #   # iteration_window = 2
  #   # dt = 0.1
  #   # growth_factor = 1.1
  #   # cutback_factor = 0.75
  #   type = ConstantDT
  #   dt = 1
  # [../]
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
    [./potential]
      type = PointValue
      point = '0 0 0.015'
      variable = potential_E_int
    [../]
    [./temperature]
      type = PointValue
      point = '0 0 -0.015'
      variable = T
    [../]
[]

[Outputs]
  exodus = true
  csv = true
  file_base = out_simpleTC_type_k
[]
