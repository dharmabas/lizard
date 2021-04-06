###Example of pulling material properties from a csv file  on a simple thermocouple block
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
      min = 0      ####Set to zero to avoid ThermoElectricMaterial warning - does not effect solution/computation. Warning discussed in materials block
      max = 0.1e-10
    [../]
  [../]
[]

[Functions]
  #####Function type used to define Seebeck coefficient as a function of temperature
  #####CSV needs to be formatted so that the first ROW is the temperature or variable dependence of interest, and second ROW is value of interest
  #####The traditional syntex for this has time as the first row. t to T conversion happens in material block
  #####The block header is what is used to call the function in the materials block
   [./sbC_function]
    type = PiecewiseLinear
    data_file = Typek_SeebeckCoefficient_input.csv
  [../]
[]

[Kernels]
  ########BLOCK 1
  [./Seebeck_1_x]
    type = SeebeckEffect
    variable = potential_E_int
    potential_E_int = 'potential_E_int'
    T = 'T'
    sbC = 'seebeck_coefficient' ###Temperature dependent input parameter
    component = 0
  [../]
  [./Seebeck_1_y]
    type = SeebeckEffect
    variable = potential_E_int
    potential_E_int = 'potential_E_int'
    T = 'T'
    sbC = 'seebeck_coefficient' ###Temperature dependent input parameter
    component = 1
  [../]
  [./Seebeck_1_z]
    type = SeebeckEffect
    variable = potential_E_int
    potential_E_int = 'potential_E_int'
    T = 'T'
    sbC = 'seebeck_coefficient' ###Temperature dependent input parameter
    component = 2
  [../]

  [./q1_1_x]
    type = q1
    variable = T
    T = 'T'
    thC = 'thermal_conductivity' ###Constant input parameter
    component = 0
  [../]
  [./q1_1_y]
    type = q1
    variable = T
    T = 'T'
    thC = 'thermal_conductivity' ###Constant input parameter
    component = 1
  [../]
  [./q1_1_z]
    type = q1
    variable = T
    T = 'T'
    thC = 'thermal_conductivity' ###Constant input parameter
    component = 2
  [../]

[]


[Materials]

  ###Temperature Dependent Seebeck
  ###This material block is a knock off of HeatConductionMaterial
  ###The block takes a function and converts the time variable into temperature (or any variable of interest for that matter)
  ###This material block is flexible and can be easily modified to account for other parameters of interest (Will need to add temp dep density and specific heat if we want time dependent heat flow analysis)

  ###If _temperature_function is specified then the block will expect a function (seebeck_coefficient_temperature_function for example).  Otherwise a constant value will need to be input (thermal_conductivity or electrical_conductivity for example).

  ###NOTE: The original HeatConductionMaterial was written for systems in terms of Kelvin, so a warning will be displayed if the temperature value goes negative.
  ######## The warning can be ignored if units are in C, or if a randomIC is used with a negative range (I changed randomIC range on T for this model to be 0 - 10e-10K to avoid the warning)

  [./ThermoelectricProperties_block1]
    type = ThermoelectricMaterial
    temp = T
    seebeck_coefficient_temperature_function = sbC_function ### Name of material property when calling in kernel: seebeck_coefficient
    thermal_conductivity = 1.612  ### Name of material property when calling in kernel: thermal_conductivity
    electrical_conductivity = 8.422e4   ### Name of material property when calling in kernel: electrical_conductivity
    block = 0
  [../]

[]

[BCs]
  [./reference_junction_temperature]
    type = DirichletBC
    variable = T
    boundary = 'front'
    value = 273
  [../]
  [./measuring_junction_temperature]
    type = DirichletBC
    variable = T
    boundary = 'back'
    value = 298
  [../]

  ###Need to ground measuring junction
  [./measuring_junction_ground]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'back'
    value = 0
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
