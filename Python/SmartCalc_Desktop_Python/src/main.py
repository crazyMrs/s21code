import sys
from PyQt5.QtWidgets import QApplication
from view.main_window import MainWindow
from model.model import CalculatorModel
from view_model.calculator_viewmodel import CalculatorViewModel
from config_manager import ConfigManager
from logger import Logger


def setup_logging(rotation_period_param):
    logger_param = Logger(rotation_period_param)
    return logger_param


if __name__ == "__main__":
    logger = setup_logging('D')
    logger.log('info', 'Application starting')

    try:
        config_manager = ConfigManager('config/config.ini', logger)
        background_color = config_manager.get_background_color()
        font_size = config_manager.get_font_size()
        rotation_period = config_manager.get_rotation_period()

        logger.log('info', 'Configuration successfully loaded')

        app = QApplication(sys.argv)
        model = CalculatorModel()
        viewmodel = CalculatorViewModel(model)
        window = MainWindow(viewmodel)

        window.setStyleSheet(f"""background-color: {background_color};
                             font-size: {font_size}px;""")

        window.show()
        sys.exit(app.exec_())

    except FileNotFoundError as e:
        logger.log('critical', f'Config file not found: {e}')
        sys.exit(1)
    except ValueError as e:
        logger.log('critical', f'Invalid config value: {e}')
        sys.exit(1)
