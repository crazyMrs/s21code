import numpy as np


class CalculatorViewModel:
    def __init__(self, model):
        self.model = model
        self.history = []
        self.history_file = 'history.txt'
        self.load_history()

    def calculate(self, expression: str, x: float = None) -> float:
        if 'x' in expression:
            if x is None:
                raise ValueError("Variable 'x' in the expression, "
                                 + "but no value for 'x' was provided.")
            expression = expression.replace('x', str(x))
        result = self.model.calculate(expression)
        self.history.append((expression, result))
        self.save_history()
        return result

    def evaluate_expression(self, expression: str, x: float) -> float:
        """Вычисляет выражение с заданным значением x."""
        if 'x' in expression:
            expression = expression.replace('x', str(x))
        return self.model.calculate(expression)

    def generate_plot_data(self, expression: str, x_min: float,
                           x_max: float, num_points: int) -> tuple:
        """Генерирует данные для построения графика функции."""
        x_values = np.linspace(x_min, x_max, num_points)
        y_values = [self.evaluate_expression(expression, x) for x in x_values]
        return x_values, y_values

    def get_history(self):
        return self.history

    def clear_history(self):
        self.history.clear()
        self.save_history()

    def load_history(self):
        try:
            with open(self.history_file, 'r', encoding='utf-8') as file:
                for line in file:
                    if line.strip():
                        expression, result = line.strip().split(' = ')
                        self.history.append((expression, float(result)))
        except FileNotFoundError:
            print(f"History file '{self.history_file}' not found")

    def save_history(self):
        with open(self.history_file, 'w', encoding='utf-8') as file:
            for expression, result in self.history:
                file.write(f"{expression} = {result}\n")
