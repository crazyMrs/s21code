import os
from PyQt5.QtWidgets import QMainWindow, QTextEdit


class HelpWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Справка")
        self.setGeometry(100, 100, 600, 400)

        help_text = self.load_help_text()
        self.help_field = QTextEdit(self)
        self.help_field.setReadOnly(True)
        self.help_field.setPlainText(help_text)

        self.setCentralWidget(self.help_field)

    def load_help_text(self):
        help_file = os.path.join(os.path.dirname(__file__), 'help.txt')
        with open(help_file, 'r', encoding='utf-8') as file:
            return file.read()
