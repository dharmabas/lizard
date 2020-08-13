[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 30
  ny = 30
  xmin = -0.5
  xmax = 0.5
  ymin = -0.5
  ymax = 0.5
  elem_type = QUAD4
[]

[Variables]
  [./potential_E_int]
    order = FIRST
    family = LAGRANGE
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
[]

[AuxKernels]
  [./x_current]
    type = CurrentAux
    variable = j_x
    electrical_conductivity = 'electrical_conductivity'
    potential_E_int = 'potential_E_int'
    component = 0
  [../]
  [./y_current]
    type = CurrentAux
    variable = j_y
    electrical_conductivity = 'electrical_conductivity'
    potential_E_int = 'potential_E_int'
    component = 1
  [../]
  [./z_current]
    type = CurrentAux
    variable = j_z
    electrical_conductivity = 'electrical_conductivity'
    potential_E_int = 'potential_E_int'
    component = 2
  [../]
  []

[Kernels]
  [./potential]
    type = Electrostatics
    variable = potential_E_int
    permittivity = 1
  [../]
  [./xcurrent]
    type = OhmsLaw
    variable = potential_E_int
    component = 0
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity'
  [../]
  [./ycurrent]
    type = OhmsLaw
    variable = potential_E_int
    component = 1
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity'
  [../]
  [./zcurrent]
    type = OhmsLaw
    variable = potential_E_int
    component = 2
    potential_E_int = 'potential_E_int'
    electrical_conductivity = 'electrical_conductivity'
  [../]
[]

[Materials]
  [./electrical_conductivity]
    type = GenericConstantMaterial
    prop_names = 'electrical_conductivity'
    prop_values = '0.023'
  [../]
[]

[BCs]
  [./left_potential]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'left'
    value = 0
  [../]
  [./right_potential]
    type = DirichletBC
    variable = potential_E_int
    boundary = 'right'
    value = 1
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
[]

[Postprocessors]
  [./potential_origin]
    type = PointValue
    point = '0 0 0'
    variable = potential_E_int
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
