import yaml


def generate_ansible_tasks(todo_file):
    tasks = []

    # Установка пакетов
    if 'install_packages' in todo_file['server']:
        server_packages = todo_file['server']['install_packages']
        for pkg in server_packages:
            tasks.append({'name': 'Install ' + pkg, 'apt': 'name={pkg} state=present'.format(pkg=pkg)})

    # Копирование файлов
    if 'exploit_files' in todo_file['server']:
        exploit_files = todo_file['server']['exploit_files']
        for file in exploit_files:
            tasks.append(
                {'name': 'Copy ' + file, 'copy': 'src={file} dest=/home/ubuntu/{file} mode=0644'.format(file=file)})

    # Выполнение файлов на удаленном сервере
    if 'bad_guys' in todo_file:
        bad_guys = todo_file['bad_guys']
        tasks.append({'name': 'Run exploit.py on remote server with bad_guys argument',
                      'command': 'python3 /home/ubuntu/exploit.py -e {bg}'.format(bg=','.join(bad_guys))})
        tasks.append({'name': 'Run consumer.py on remote server',
                      'command': 'python3 /home/ubuntu/consumer.py'})

        print(tasks)
    return tasks


def main():
    with open('../materials/todo.yml', 'r') as file:
        todo_file = yaml.safe_load(file)
    
    tasks = generate_ansible_tasks(todo_file)
    
    deploy_yaml = yaml.dump({'tasks': tasks}, default_flow_style=False)
    
    with open('deploy.yml', 'w') as file:
        file.write(deploy_yaml)


if __name__ == "__main__":
    main()
