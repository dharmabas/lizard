[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 30
  ny = 30
  nz = 30
  xmin = -0.000762
  xmax = 0.000762
  ymin = -0.0007
  ymax = 0.0007
  zmin = -0.0007
  zmax = 0.0007
  elem_type = HEX8
  []

[Variables]
  [./potential_E_int]
    order = FIRST
    family = LAGRANGE
  [../]
  [./temperature]
    order = FIRST
    family = LAGRANGE
    initial_condition = 25
  [../]
  []

[Kernels]
  [./residualV_x]
  type = ResidualV
  component = 0
  variable = potential_E_int
  temperature = 'temperature'
  potential_E_int = 'potential_E_int'
[../]

[./residualV_y]
 type = ResidualV
 component = 1
 variable = potential_E_int
 temperature = 'temperature'
 potential_E_int = 'potential_E_int'
[../]

[./residualV_z]
 type = ResidualV
 component = 2
 variable = potential_E_int
 temperature = 'temperature'
 potential_E_int = 'potential_E_int'
[../]

[./residualT_x]
 type = ResidualT
 component = 0
 variable = temperature
 temperature = 'temperature'
 potential_E_int = 'potential_E_int'
[../]

[./residualT_y]
 type = ResidualT
 component = 1
 variable = temperature
 temperature = 'temperature'
 potential_E_int = 'potential_E_int'
[../]

[./residualT_z]
 type = ResidualT
 component = 2
 variable = temperature
 temperature = 'temperature'
 potential_E_int = 'potential_E_int'
[../]

[]
#
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
#
# [AuxKernels]
#   [./Electric_flux_x]
#     type = Electric_flux
#     variable = j_x
#     temperature = temperature
#     potential_E_int = 'potential_E_int'
#     component = 0
#   [../]
#   [./Electric_flux_y]
#     type = Electric_flux
#     variable = j_y
#     temperature = temperature
#     potential_E_int = 'potential_E_int'
#     component = 1
#   [../]
#   [./Electric_flux_z]
#     type = Electric_flux
#     variable = j_z
#     temperature = temperature
#     potential_E_int = 'potential_E_int'
#     component = 2
#   [../]
#
#   [./Heat_flux_x]
#     type = Heat_flux
#     variable = q_x
#     temperature = 'temperature'
#     potential_E_int = 'potential_E_int'
#     component = 0
#   [../]
#   [./heat_flux_y]
#     type = Heat_flux
#     variable = q_y
#     temperature = 'temperature'
#     potential_E_int = 'potential_E_int'
#     component = 1
#   [../]
#   [./Heat_flux_z]
#     type = Heat_flux
#     variable = q_z
#     temperature = 'temperature'
#     potential_E_int = 'potential_E_int'
#     component = 2
#   [../]
#   []

  [Materials]
     [./thermaltensor]
      type = GenericConstantRankTwoTensor
      tensor_name = 'thermal_conductivity_tensor'
      tensor_values = '1.612 1 1 0 0 0 0 0 0'
      outputs = all
     [../]
     [./electricaltensor]
      type = GenericConstantRankTwoTensor
      tensor_name = 'electrical_conductivity_tensor'
      tensor_values = '8.422e4 8e4 8e4 0 0 0 0 0 0'
      outputs = all
     [../]
     [./seebecktensor]
      type = GenericConstantRankTwoTensor
      tensor_name = 'seebeck_coefficient_tensor'
      tensor_values = '1.941e-4 1e-4 1e-4 0 0 0 0 0 0'
      outputs = all
     [../]
   []

[BCs]
  [./left_temperature]
    type = DirichletBC
    variable = temperature
    boundary = 'left'
    value = 25
  [../]
  [./right_temperature]
    type = DirichletBC
    variable = temperature
    boundary = 'right'
    value = 25
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
  [./top_bottom_temp]
    type = NeumannBC
    variable = temperature
    boundary = 'top bottom'
    value = 0
  [../]
  [./top_bottom_pot]
    type = NeumannBC
    variable = potential_E_int
    boundary = 'top bottom'
    value = 0
  [../]
  [./front_back_temp]
    type = NeumannBC
    variable = temperature
    boundary = 'front back'
    value = 0
  [../]
  [./front_back_pot]
    type = NeumannBC
    variable = potential_E_int
    boundary = 'front back'
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
