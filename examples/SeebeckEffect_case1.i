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
  [../]
  [./temperature]
    order = FIRST
    family = LAGRANGE
  [../]
[]


[Kernels]
  [./Electrostatics]
    type = Electrostatics
    variable = potential_E_int
    electrical_conductivity = electrical_conductivity
  [../]
  [./Seebeck]
    type = SeebeckEffect
    variable = temperature
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
  [../]

  [./q1]
    type = q1
    variable = temperature
    thermal_conductivity = 'thermal_conductivity'
  [../]
  [./q2]
    type = q2
    variable = potential_E_int
    temperature = 'temperature'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
  [../]
  [./q3]
    type = q3
    variable = temperature
    temperature = 'temperature'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
  [../]

  [./current1]
    type = current1
    variable = potential_E_int
    potential_E_int = potential_E_int
    electrical_conductivity = 'electrical_conductivity'
  [../]
  [./current2]
    type = current2
    variable = potential_E_int
    temperature = 'temperature'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
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

  [./E_new]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./T_new]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./generated_current_x]
    type = generated_current
    variable = j_x
    temperature = temperature
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 0
  [../]
  [./generated_current_y]
    type = generated_current
    variable = j_y
    temperature = temperature
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 1
  [../]
  [./generated_current_z]
    type = generated_current
    variable = j_z
    temperature = temperature
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 2
  [../]

  [./generated_flux_x]
    type = generated_flux
    variable = q_x
    temperature = 'temperature'
    thermal_conductivity = 'thermal_conductivity'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 0
  [../]
  [./generated_flux_y]
    type = generated_flux
    variable = q_y
    temperature = 'temperature'
    thermal_conductivity = 'thermal_conductivity'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 1
  [../]
  [./generated_flux_z]
    type = generated_flux
    variable = q_z
    temperature = 'temperature'
    thermal_conductivity = 'thermal_conductivity'
    electrical_conductivity = 'electrical_conductivity'
    seebeck_coefficient = 'seebeck_coefficient'
    potential_E_int = 'potential_E_int'
    component = 2
  [../]

  [./new_potential]
    type = potential_update
    variable = E_new
    temperature = temperature
    seebeck_coefficient = 'seebeck_coefficient'
  [../]

  [./new_temperature]
    type = temperature_update
    variable = T_new
    potential_E_int = 'potential_E_int'
    seebeck_coefficient = 'seebeck_coefficient'
  [../]
[]


[Materials]
  [./ThermoelectricProperties]
   type = GenericConstantMaterial
   prop_names = 'electrical_conductivity thermal_conductivity seebeck_coefficient'
   prop_values = '9.5e4 1.75 1.87e-4'
  [../]
[]

[BCs]
  [./left_temperature]
    type = DirichletBC
    variable = temperature
    boundary = 'left'
    value = 0
  [../]
  [./right_temperature]
    type = DirichletBC
    variable = temperature
    boundary = 'right'
    value = 25
  [../]

  [./top_bottom_temperature]
    type = NeumannBC
    variable = temperature
    boundary = 'top bottom'
    value = 0
  [../]
  [./left_right_potential]
    type = NeumannBC
    variable = potential_E_int
    boundary = 'left right top bottom'
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
    variable = temperature
  [../]

  [./new_potential]
    type = PointValue
    point = '0 0 0'
    variable = E_new
  [../]
  [./new_temperature]
    type = PointValue
    point = '0 0 0'
    variable = T_new
  [../]

  [./flux_x]
    type = PointValue
    point = '0 0 0'
    variable = q_x
  [../]
  [./flux_y]
    type = PointValue
    point = '0 0 0'
    variable = q_y
  [../]
  [./flux_z]
    type = PointValue
    point = '0 0 0'
    variable = q_z
  [../]

  [./current_x]
    type = PointValue
    point = '0 0 0'
    variable = j_x
  [../]
  [./current_y]
    type = PointValue
    point = '0 0 0'
    variable = j_y
  [../]
  [./current_z]
    type = PointValue
    point = '0 0 0'
    variable = j_z
  [../]
[]

[Outputs]
  exodus = true
  csv = true
[]
[Debug]
  show_var_residual_norms = true
  #show_actions = true
[]
