from ctypes import CDLL
from ctypes import c_char_p
import pytest

test_args_type_inpt = [
        ["", "", "", ""],
        ["abc", "1", "1", "1"],
        ["1", "abc", "1", "1"],
        ["1", "1", "abc", "1"],
        ["1", "1", "1", "abc"],
        ["abc", "abc", "abc", "abc"],
        ["", "abc", "abc", "abc"],
        ["1", "1", "1", "1"]]
test_args_type_output = [0, 0, 0, 0, 0, 0, 0, 1]


test_args_range_input = [
        ["1", "1", "-1", "1000"],
        ["1", "1", "-1", "-1"],
        ["1", "-1", "1000", "1000"],
        ["1", "-1", "1000", "1000"],
        ["-1", "-1", "1000", "1000"],
        ["1", "1", "1001", "1000"],
        ["1", "1", "1000", "1001"]]

test_args_range_output = [0, 0, 0, 0, 0, 0, 0]


def convert_to_bytes(array: list[list[str]]) -> list[list[bytes]]:
    return [[x.encode() for x in vector] for vector in array]


@pytest.fixture
def args_lib():
    yield CDLL("./args.so")


# run function with strings
def test_args_type(args_lib):
    args_lib.argtypes = [c_char_p]
    inpt = convert_to_bytes(test_args_type_inpt)
    for n, (i, o) in enumerate(zip(inpt, test_args_type_output)):
        assert args_lib.args_valid(*i) == o


def test_args_range(args_lib):
    args_lib.argtypes = [c_char_p]
    inpt = convert_to_bytes(test_args_range_input)
    for n, (i, o) in enumerate(zip(inpt, test_args_range_output)):
        assert args_lib.args_valid(*i) == o
