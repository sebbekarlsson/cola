from __init__ import binexec


def test_print_cola():
    assert binexec('print.cola') == '1'


def test_variable_definition_cola():
    assert binexec('variable_definition.cola') == '2\na'


def test_binop_cola():
    assert binexec('binop.cola') == '1000\n110\n10\n90\n95'


def test_component_cola():
    assert binexec('component.cola') == '100'
