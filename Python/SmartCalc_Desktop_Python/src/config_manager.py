import configparser
import os


class ConfigManager:
    def __init__(self, config_file_path, logger):
        self.config_file_path = config_file_path
        self.config = configparser.ConfigParser()
        self.logger = logger
        self.load_config()

    def load_config(self):
        try:
            if not os.path.exists(self.config_file_path):
                raise FileNotFoundError(f"""Config file
                                        '{self.config_file_path}'
                                        not found.""")

            self.config.read(self.config_file_path)
            message = f"Configuration loaded from '{self.config_file_path}'"
            self.logger.log('info', message)

        except Exception as e:
            error_message = f"""Failed to load configuration
            from '{self.config_file_path}': {e}"""
            self.logger.log('error', error_message)
            raise RuntimeError(error_message) from e

    def get_background_color(self):
        return self.config.get('Settings', 'background_color')

    def get_font_size(self):
        return int(self.config.get('Settings', 'font_size'))

    def get_rotation_period(self):
        return self.config.get('Logging', 'rotation_period')
