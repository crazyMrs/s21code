import requests
import argparse
import os
import logging
from bs4 import BeautifulSoup

# клиент будет загружать файлы и запрашивать список файлов на сервере

def upload_file(file_path: str):
    url = 'http://127.0.0.1:8888/'
    files = {'file': open(file_path, 'rb')}
    response = requests.post(url, files=files)

    if response.status_code == 200:
        logging.info("File successfully uploaded")
    else:
        logging.ERROR(f"Failed to upload file. Status code: {response.status_code}")


def list_files():
    url = 'http://127.0.0.1:8888/'
    response = requests.get(url)
    if response.status_code == 200:
        
        soup = BeautifulSoup(response.text, 'html.parser')
        files = [li.text for li in soup.find_all('li')]
        print('Files on server:')
        for file in files:
            print(file)
    else:
        logging.ERROR(f'Failed to retrieve files. Status code: {response.status_code}')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest='command')

    upload_parser = subparsers.add_parser('upload', help='Upload a file')
    upload_parser.add_argument('file_path', type=str, help='Path to the file to upload')

    list_parser = subparsers.add_parser('list', help='List files on server')

    args = parser.parse_args()

    if args.command == 'upload':
        if os.path.exists(args.file_path):
            upload_file(args.file_path)
        else:
            logging.ERROR(f'File {args.file_path} does not exist')
    elif args.command == 'list':
        list_files()
    else:
        parser.print_help()