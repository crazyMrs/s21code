import logging
from logging.handlers import TimedRotatingFileHandler
from datetime import datetime


class Logger:
    def __init__(self, rotation_period):
        self.logger = logging.getLogger('SmartCalcLogger')
        self.logger.setLevel(logging.DEBUG)
        log_str = '%(asctime)s -%(levelname)s - %(message)s'
        formatter = logging.Formatter(log_str)

        str_time = 'logs/logs_%d-%m-%y-%H-%M-%S.log'
        log_filename = datetime.now().strftime(str_time)
        log_handler = TimedRotatingFileHandler(log_filename,
                                               when=rotation_period,
                                               interval=1,
                                               backupCount=7)
        log_handler.setFormatter(formatter)
        self.logger.addHandler(log_handler)

    def log(self, level, message):
        if level == 'info':
            self.logger.info(message)
        elif level == 'warning':
            self.logger.warning(message)
        elif level == 'error':
            self.logger.error(message)
        elif level == 'critical':
            self.logger.critical(message)
