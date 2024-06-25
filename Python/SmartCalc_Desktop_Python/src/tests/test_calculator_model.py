import unittest
import math
from math import isnan
from model.model import CalculatorModel


class TestCalculatorModel(unittest.TestCase):
    def setUp(self):
        self.model = CalculatorModel()

    def test_addition(self):
        result = self.model.calculate('2 + 3')
        self.assertEqual(result, 5)

    def test_subtraction(self):
        result = self.model.calculate('5 - 2')
        self.assertEqual(result, 3)

    def test_multiplication(self):
        result = self.model.calculate('4 * 3')
        self.assertEqual(result, 12)

    def test_division(self):
        result = self.model.calculate('10 / 2')
        self.assertEqual(result, 5)

    def test_power(self):
        result = self.model.calculate('2 ^ 3')
        self.assertEqual(result, 8)

    def test_modulo(self):
        result = self.model.calculate('10 mod 3')
        self.assertEqual(result, 1)

    # Унарные операции
    def test_unary_plus(self):
        result = self.model.calculate('+5')
        self.assertEqual(result, 5)

    def test_unary_minus(self):
        result = self.model.calculate('-5')
        self.assertEqual(result, -5)

    # Тригонометрические функции
    def test_cosine(self):
        result = self.model.calculate('cos(0)')
        self.assertAlmostEqual(result, 1.0, places=6)

    def test_sine(self):
        result = self.model.calculate('sin(0)')
        self.assertAlmostEqual(result, 0.0, places=6)

    def test_tangent(self):
        result = self.model.calculate('tan(0)')
        self.assertAlmostEqual(result, 0.0, places=6)

    def test_arc_cosine(self):
        result = self.model.calculate('acos(1)')
        self.assertAlmostEqual(result, 0.0, places=6)

    def test_arc_sine(self):
        result = self.model.calculate('asin(0)')
        self.assertAlmostEqual(result, 0.0, places=6)

    def test_arc_tangent(self):
        result = self.model.calculate('atan(0)')
        self.assertAlmostEqual(result, 0.0, places=6)

    # Логарифмы
    def test_sqrt(self):
        result = self.model.calculate('sqrt(4)')
        self.assertEqual(result, 2.0)

    def test_ln(self):
        result = self.model.calculate('ln(1)')
        self.assertAlmostEqual(result, 0.0, places=6)

    def test_log(self):
        result = self.model.calculate('log(10)')
        self.assertAlmostEqual(result, 1.0, places=6)

    # Обработка различных форматов входных данных
    def test_decimal_input(self):
        result = self.model.calculate('3.5 + 2.5')
        self.assertEqual(result, 6.0)

    def test_whitespace_input(self):
        result = self.model.calculate('  5  +  3  ')
        self.assertEqual(result, 8.0)

    def test_mixed_operations(self):
        result = self.model.calculate('2 * (3 + 4) / 5')
        self.assertAlmostEqual(result, 2.8, places=6)

    # Краевые случаи
    def test_large_numbers(self):
        result = self.model.calculate('1000000 * 1000000')
        self.assertEqual(result, 1000000000000)

    def test_small_numbers(self):
        result = self.model.calculate('0.0001 / 0.001')
        self.assertEqual(result, 0.1)

    def test_division_by_zero(self):
        result = self.model.calculate('10 / 0')
        self.assertEqual(result, 0.0, "Result to be 0.0 when dividing by zero")

    def test_invalid_expression(self):
        result = self.model.calculate('2 +')
        self.assertEqual(result, 2.0)

    def test_invalid_function(self):
        result = self.model.calculate('cosine(0)')
        self.assertTrue(isnan(result))

    def test_missing_parenthesis(self):
        result = self.model.calculate('2 * (3 + 4')
        self.assertTrue(isnan(result))

    def test_infix_notation(self):
        result = self.model.calculate('(2 + 3) * 4')
        self.assertEqual(result, 20)

    # Дополнительные тесты для операций с плавающей точкой
    def test_float_operations(self):
        result = self.model.calculate('0.1 + 0.2')
        self.assertAlmostEqual(result, 0.3, places=6)

    def test_trigonometric_with_float(self):
        result = self.model.calculate('sin(0.5)')
        self.assertAlmostEqual(result, math.sin(0.5), places=6)

    def test_logarithm_with_float(self):
        result = self.model.calculate('log(1000.0)')
        self.assertAlmostEqual(result, 3.0, places=6)

    # Дополнительные тесты на экстремальные значения
    def test_extreme_large_numbers(self):
        result = self.model.calculate('1e1000 + 1e1000')
        self.assertEqual(result, 0.0)

    def test_extreme_small_numbers(self):
        result = self.model.calculate('1e-1000 / 1e1000')
        self.assertEqual(result, 0.0)

    def test_extreme_exponentiation(self):
        result = self.model.calculate('10 ^ 1000')
        self.assertEqual(result, float('inf'))

    def test_negative_exponentiation(self):
        result = self.model.calculate('10 ^ (-1000)')
        self.assertEqual(result, 0.0)

    def test_zero_power_zero(self):
        result = self.model.calculate('0 ^ 0')
        self.assertEqual(result, 1.0)

    def test_epsilon(self):
        result = self.model.calculate('e')
        self.assertTrue(isnan(result))

    def test_double_bracket(self):
        result = self.model.calculate('()')
        self.assertTrue(isnan(result))


if __name__ == '__main__':
    unittest.main()
