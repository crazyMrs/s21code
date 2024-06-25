import ctypes
import os


class CalculatorModel:
    def __init__(self):
        current_dir = os.path.dirname(os.path.abspath(__file__))
        lib_path = os.path.join(current_dir, 'libcalculator.so')
        self.lib = ctypes.CDLL(lib_path)
        self.lib.InputStr.argtypes = [ctypes.c_char_p]
        self.lib.InputStr.restype = ctypes.c_double

    def calculate(self, expression: str) -> float:
        return self.lib.InputStr(expression.encode('utf-8'))
