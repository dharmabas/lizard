[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 25
  ny = 25
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
    # initial_condition = 0.005
  [../]
  [./T]
    order = FIRST
    family = LAGRANGE
    initial_condition = 298
  [../]
[]


[Kernels]
  [./Seebeck]
    type = SeebeckEffect
    variable = potential_E_int
    potential_E_int = 'potential_E_int'
    T = 'T'
    sbC = 'sbC'
    component = 0
  [../]

  [./q1]
    type = q1
    variable = T
    T = 'T'
    thC = 'thC'
    component = 0
  [../]
[]

[Materials]
  [./ThermoelectricProperties]
   type = GenericConstantMaterial
   prop_names = 'thC sbC'
   prop_values = '1.612 4.14e-4'
  [../]
[]

[BCs]
  [./left_temperature]
    type = DirichletBC
    variable = T
    boundary = 'left'
    value = 273
  [../]
  [./right_temperature]
    type = DirichletBC
    variable = T
    boundary = 'right'
    value = 298
  [../]

  [./top_bottom_temperature]
    type = NeumannBC
    variable = T
    boundary = 'top bottom'
    value = 0
  [../]

  [./left_right_potential]
    type = NeumannBC
    variable = potential_E_int
    boundary = 'top bottom'
    value = 0
  [../]
  [./left_potential]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'right'
    value = 0
  [../]
  [./right_potential]
    type = NeumannBC
    variable = potential_E_int
    boundary = 'left'
    value = 0
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
[]

[Postprocessors]
  [./potential]
    type = PointValue
    point = '0 0 0'
    variable = potential_E_int
  [../]
  [./temperature]
    type = PointValue
    point = '0 0 0'
    variable = T
  [../]
[]

[Outputs]
  exodus = true
[]
[Debug]
  show_var_residual_norms = true
  #show_actions = true
[]
