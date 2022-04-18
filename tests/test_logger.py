from ctypes import CDLL
from ctypes import c_char_p, c_int, c_char
import pytest
import sys


# @pytest.fixture
# def logger_lib():
    # yield CDLL("./logger.so")

logger_lib = CDLL("./logger.so")
logger_lib.argtypes = [c_char, c_int]
output = logger_lib.log_line(1)
