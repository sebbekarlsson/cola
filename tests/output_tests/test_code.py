from __init__ import binexec


def test_print_cola():
    assert binexec('print.cola') == '1'


def test_variable_definition_cola():
    assert binexec('variable_definition.cola') == '2\na'


def test_binop_cola():
    assert binexec('binop.cola') == '1000\n110\n10\n90\n95'


def test_component_cola():
    assert binexec('component.cola') == '100'


def test_component_use_cola():
    assert binexec('component_use.cola') == '100'


def test_component_yields_cola():
    assert binexec('component_yields.cola') == '3.14'


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
