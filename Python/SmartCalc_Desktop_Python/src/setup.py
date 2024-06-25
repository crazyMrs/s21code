import platform
import subprocess

from setuptools import setup, find_packages
from setuptools.command.install import install as _install


def parse_requirements(filename):
    with open(filename, 'r', encoding='utf-8') as f:
        return [line.strip() for line in f if line.strip()
                and not line.startswith('#')]


APP_NAME = 'SmartCalc_v3'
APP = ['main.py']
DATA_FILES = []


def build_for_windows():
    subprocess.check_call(['pyinstaller', '--onefile', '--windowed',
                           '--icon=icon/icon.ico', 'main.py'])


def build_for_mac():
    subprocess.check_call(['pyinstaller', '--onefile', '--windowed',
                           '--icon=icon/icon.icns', 'main.py'])


def build_for_linux():
    subprocess.check_call(['pyinstaller', '--onefile',
                           '--icon=icon/icon.png', 'main.py'])


class InstallCommand(_install):
    def run(self):
        _install.run(self)

        system = platform.system()
        if system == 'Windows':
            build_for_windows()
        elif system == 'Darwin':
            build_for_mac()
        elif system == 'Linux':
            build_for_linux()
        else:
            raise RuntimeError(f"Unsupported operating system: {system}")


setup(
    name=APP_NAME,
    install_requires=parse_requirements('requirements.txt'),
    cmdclass={'install': InstallCommand},
    packages=find_packages(),
)
