from __init__ import binexec


def test_print_cola():
    assert binexec('print.cola') == '1'


def test_variable_definition_cola():
    assert binexec('variable_definition.cola') == '2\na'


def test_binop_cola():
    assert binexec('binop.cola') == '1000\n110\n10\n90\n95'


def test_floats_cola():
    assert binexec('floats.cola') == '5.000000'


def test_string_cola():
    assert binexec('string.cola') == 'hello world'


def test_strlen_cola():
    assert binexec('strlen.cola') == '5'


def string_plus_string_cola():
    assert binexec('string_plus_string.cola') == 'hello world!!!'


def test_component_cola():
    assert binexec('component.cola') == '100'


def test_component_use_cola():
    assert binexec('component_use.cola') == '100'


def test_component_yields_cola():
    assert binexec('component_yields.cola') == '3.140000'


def test_no_executions_outside_main_cola():
    assert binexec('no_executions_outside_main.cola') is None


def test_if_cola():
    assert binexec('if.cola') == '100'


def test_if_else_cola():
    assert binexec('if_else.cola') == '200\n256'


def test_if_assign_cola():
    assert binexec('assign.cola') == '2\n4'


def test_while_cola():
    assert binexec('while.cola') == '3\n2\n1'


def test_return_cola():
    assert binexec('return.cola') == '256'


def test_vecptr_cola():
    assert binexec('vecptr.cola') == 'h\ne\nl\nl\no'


def test_foreach_cola():
    assert binexec('foreach.cola') == 'h\ne\nl\nl\no'


def test_vector_int_cola():
    assert binexec('vector_int.cola') == '255\n0\n128\n255'


def test_strsplit_cola():
    assert binexec('strsplit.cola') == 'john\ndoe\n21'


def test_interpreter_instr_include_main_cola():
    assert binexec('interpreter_instr_include/main.cola') == 'hello\nworld'
