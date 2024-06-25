import sys
from PyQt5.QtWidgets import \
    QMessageBox, QApplication, QMainWindow, \
    QVBoxLayout, QWidget, QLineEdit, QPushButton, \
    QTextEdit, QLabel, QAction, QMenuBar, \
    QHBoxLayout, QListWidget
from PyQt5.QtGui import QDoubleValidator
from matplotlib.backends.backend_qt5agg import \
    FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
from view_model.calculator_viewmodel import CalculatorViewModel
from model.model import CalculatorModel
from help import HelpWindow
from logger import Logger


class GraphWindow(QWidget):
    def __init__(self, x_values, y_values,
                 expression, y_min, y_max, parent=None):
        super().__init__(parent)
        self.x_values = x_values
        self.y_values = y_values
        self.expression = expression
        self.y_min = y_min
        self.y_max = y_max
        self.setWindowTitle(f"Graph of {self.expression}")
        self.setGeometry(100, 100, 600, 400)

        self.layout = QVBoxLayout(self)
        self.canvas = FigureCanvas(Figure())
        self.layout.addWidget(self.canvas)

        self.plot_graph()

    def plot_graph(self):
        ax = self.canvas.figure.add_subplot(111)
        ax.plot(self.x_values, self.y_values)
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_ylim(self.y_min, self.y_max)
        ax.set_title(f'Graph of {self.expression}')
        ax.grid(True)

        ax.axhline(0, color='black', linewidth=1.0)
        ax.axvline(0, color='black', linewidth=1.0)

        self.canvas.draw()


class MainWindow(QMainWindow):
    def __init__(self, viewmodel):
        super().__init__()
        self.viewmodel = viewmodel
        self.logger = Logger(rotation_period='midnight')

        self.input_field = None
        self.x_label = None
        self.x_field = None

        self.x_min_label = None
        self.x_min_field = None
        self.x_max_label = None
        self.x_max_field = None
        self.y_min_label = None
        self.y_min_field = None
        self.y_max_label = None
        self.y_max_field = None

        self.calculate_button = None
        self.help_button = None
        self.clear_history_button = None
        self.load_expression_button = None
        self.show_graph_button = None
        self.history_field = None
        self.history_list = None
        self.help_window = None
        self.graph_window = None

        self.setWindowTitle("SmartCalc v3.0")
        self.setGeometry(700, 100, 600, 400)

        self.init_ui()
        self.init_menu()

        self.closeEvent = self.save_history_on_close

    def save_history_on_close(self, event):
        self.viewmodel.save_history()
        event.accept()

    def init_ui(self):
        """Инициализия основных компонентов пользовательского интерфейса."""
        self.setup_input_fields()
        self.setup_range_fields()
        self.setup_buttons()
        self.setup_history_field()
        self.setup_layout()

        self.calculate_button.clicked.connect(self.calculate)
        self.help_button.clicked.connect(self.show_help)
        self.clear_history_button.clicked.connect(self.clear_history)
        self.load_expression_button.clicked.connect(self.load_expression)
        self.show_graph_button.clicked.connect(self.show_graph)

    def setup_input_fields(self):
        """Настройка полей ввода для калькулятора."""
        self.input_field = QLineEdit(self)
        self.x_label = QLabel("Input x:", self)
        self.x_field = QLineEdit(self)

        validator = QDoubleValidator()
        validator.setNotation(QDoubleValidator.StandardNotation)
        self.x_field.setValidator(validator)

    def setup_buttons(self):
        """Настройка кнопок для различных действий."""
        self.calculate_button = QPushButton("Calculate", self)
        self.calculate_button.setStyleSheet("background-color: orange;")

        self.help_button = QPushButton("Help", self)
        self.help_button.setStyleSheet("background-color: lightblue;")

        self.clear_history_button = QPushButton("Clear History", self)
        self.load_expression_button = QPushButton("Load Expression", self)

        self.show_graph_button = QPushButton("Show Graph", self)
        self.show_graph_button.setStyleSheet("background-color: lightgreen;")

    def setup_history_field(self):
        """Настройка полей для отображения истории расчетов."""
        self.history_field = QTextEdit(self)
        self.history_field.setReadOnly(True)
        self.history_list = QListWidget(self)
        self.update_history_list()

    def setup_range_fields(self):
        """Настройка полей ввода для диапазонов."""
        self.x_min_label = QLabel("X min:", self)
        self.x_min_field = QLineEdit(self)
        self.x_max_label = QLabel("X max:", self)
        self.x_max_field = QLineEdit(self)

        self.y_min_label = QLabel("Y min:", self)
        self.y_min_field = QLineEdit(self)
        self.y_max_label = QLabel("Y max:", self)
        self.y_max_field = QLineEdit(self)

        self.x_min_field.setText("-20")
        self.x_max_field.setText("20")
        self.y_min_field.setText("-20")
        self.y_max_field.setText("20")

        self.x_min_field.setValidator(QDoubleValidator(-1000000, 1000000, 10))
        self.x_max_field.setValidator(QDoubleValidator(-1000000, 1000000, 10))
        self.y_min_field.setValidator(QDoubleValidator(-1000000, 1000000, 10))
        self.y_max_field.setValidator(QDoubleValidator(-1000000, 1000000, 10))

    def setup_layout(self):
        """Расположение компонентов интерфейса в основном макете."""
        button_layout = QHBoxLayout()
        button_layout.addWidget(self.calculate_button)
        button_layout.addWidget(self.help_button)
        button_layout.addWidget(self.clear_history_button)
        button_layout.addWidget(self.load_expression_button)
        button_layout.addWidget(self.show_graph_button)

        range_layout = QHBoxLayout()
        range_layout.addWidget(self.x_min_label)
        range_layout.addWidget(self.x_min_field)
        range_layout.addWidget(self.x_max_label)
        range_layout.addWidget(self.x_max_field)
        range_layout.addWidget(self.y_min_label)
        range_layout.addWidget(self.y_min_field)
        range_layout.addWidget(self.y_max_label)
        range_layout.addWidget(self.y_max_field)

        layout = QVBoxLayout()
        layout.addWidget(self.input_field)
        layout.addWidget(self.x_label)
        layout.addWidget(self.x_field)
        layout.addLayout(button_layout)
        layout.addLayout(range_layout)
        layout.addWidget(self.history_field)
        layout.addWidget(self.history_list)

        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)

    def init_menu(self):
        """Инициализация строки меню."""
        menubar = QMenuBar(self)
        self.setMenuBar(menubar)

        help_menu = menubar.addMenu('Help')
        help_action = QAction('Show Help', self)
        help_action.triggered.connect(self.show_help)
        help_menu.addAction(help_action)

    def show_help(self):
        """Показать окно справки."""
        self.help_window = HelpWindow()
        self.help_window.show()

    def calculate(self):
        """Вычисление выражения, введенное пользователем."""
        expression = self.input_field.text().strip()

        if not expression:
            QMessageBox.critical(self, "Error", "Please enter an expression")
            return

        if len(expression) > 255:
            error_message = "Enter an expression less 255 symbols"
            QMessageBox.critical(self, "Error", error_message)

        x_text = self.x_field.text()

        try:
            x = float(x_text) if x_text else None
            result = self.viewmodel.calculate(expression, x)
            self.history_field.append(f"{expression} = {result}")
            self.update_history_list()

        except ValueError as e:
            QMessageBox.critical(self, "Error", str(e))

    def show_graph(self):
        """Показать график выражения."""
        expression = self.input_field.text().strip()
        if expression:
            x_min = float(self.x_min_field.text())
            x_max = float(self.x_max_field.text())
            y_min = float(self.y_min_field.text())
            y_max = float(self.y_max_field.text())

            num_points = 1000

            x_values, y_values = self.viewmodel.generate_plot_data(
                expression, x_min, x_max, num_points)

            self.graph_window = GraphWindow(x_values, y_values,
                                            expression, y_min, y_max)
            self.graph_window.show()
        else:
            QMessageBox.critical(self, "Error", "Please select an expression")

    def clear_history(self):
        """Очищение истории вычислений."""
        self.viewmodel.clear_history()
        self.history_field.clear()
        self.update_history_list()

    def load_expression(self):
        """Загрузка выражения из истории в поле ввода."""
        self.update_history_list()
        selected_item = self.history_list.currentItem()
        if selected_item is not None:
            expression = selected_item.text().split(' = ')[0]
            self.input_field.setText(expression)
        else:
            self.logger.log('warning', 'No expression selected in history')

    def update_history_list(self):
        """Обновить список отображения истории расчетов."""
        for expression, result in self.viewmodel.get_history():
            self.history_list.addItem(f"{expression} = {result}")
        if self.history_list.count() == 0:
            self.logger.log('warning', 'History list is empty')


if __name__ == "__main__":
    app = QApplication(sys.argv)
    model = CalculatorModel()
    viewmodel_instance = CalculatorViewModel(model)
    window = MainWindow(viewmodel_instance)
    window.show()
    sys.exit(app.exec_())
