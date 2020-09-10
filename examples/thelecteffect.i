[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 30
  ny = 30
  xmin = -0.000762
  xmax = 0.000762
  ymin = -0.0007
  ymax = 0.0007
  elem_type = QUAD4
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
  # [./potential]
  #   type = Electrostatics
  #   variable = potential_E_int
  #   electrical_conductivity = '8.422e4'
  # [../]

  # [./temperature]
  #   type = q1
  #   variable = temperature
  #   thermal_conductivity = 1.612
  # [../]

 [./residualV_x]
  type = ResidualV
  component = 0
  variable = temperature
  temperature = 'temperature'
  potential_E_int = 'potential_E_int'
  electrical_conductivity = '8.422e4'
  seebeck_coefficient = 1.941e-4
[../]

[./residualV_y]
 type = ResidualV
 component = 1
 variable = potential_E_int
 temperature = 'temperature'
 potential_E_int = 'potential_E_int'
 electrical_conductivity = '8.422e4'
 seebeck_coefficient = 1.941e-4
[../]

[./residualV_z]
 type = ResidualV
 component = 2
 variable = potential_E_int
 temperature = 'temperature'
 potential_E_int = 'potential_E_int'
 electrical_conductivity = '8.422e4'
 seebeck_coefficient = 1.941e-4
[../]

[./residualT_x]
 type = ResidualT
 component = 0
 variable = temperature
 temperature = 'temperature'
 potential_E_int = 'potential_E_int'
 electrical_conductivity = '8.422e4'
 seebeck_coefficient = 1.941e-4
 thermal_conductivity = 1.612
[../]

[./residualT_y]
 type = ResidualT
 component = 1
 variable = temperature
 temperature = 'temperature'
 potential_E_int = 'potential_E_int'
 electrical_conductivity = '8.422e4'
 seebeck_coefficient = 1.941e-4
 thermal_conductivity = 1.612
[../]

[./residualT_z]
 type = ResidualT
 component = 2
 variable = temperature
 temperature = 'temperature'
 potential_E_int = 'potential_E_int'
 electrical_conductivity = '8.422e-4'
 seebeck_coefficient = 1.941e-4
 thermal_conductivity = 1.612
[../]

[]

[BCs]
  [./left_temperature]
    type = DirichletBC
    variable = temperature
    boundary = 'left'
    value = 298
  [../]
  [./right_temperature]
    type = DirichletBC
    variable = temperature
    boundary = 'right'
    value = 298
  [../]

  [./left_potential]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'left'
    value = 0.058
  [../]
  [./right_potential]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'right'
    value = 0
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
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
