
using System;
using System.Diagnostics;
using System.Linq;

namespace ProcessController
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var controller = new Controller();
            try
            {
                controller.Execute();
            }
            catch
            {

            }

        }


    }

    public class Controller
    {
        // Словарь для сопоставления введенных в строку символов и названиями шагов
        // Можно дополнять различными словами. Например не только "1", а "Показать все процессы"  и т.д.
        private Dictionary<string, string> LinesAndStageKeys = new Dictionary<string, string>
        {
            {"1", StageNames.ShowProcesses},
            {"2", StageNames.ShutDownProcess},
            {"3", StageNames.Exit}
        };

        private string CurrentStage { get; set; }
        public Controller()
        {
            CurrentStage = StageNames.ShowProcesses;
        }

        public void Execute()
        {
            while (true)
            {
                switch (CurrentStage)
                {
                    case StageNames.ShowProcesses:
                        ExecuteShowProcesses();
                        break;
                    case StageNames.ShutDownProcess:
                        ExecuteShutDownProcess();
                        break;
                    case StageNames.Exit:
                        return;
                }
                ShowStageChoice();
                CurrentStage = GetNextStageKey();
            }
        }

        private void ExecuteShowProcesses()
        {
            // Формирование шапки
            Console.Clear();
            Console.WriteLine("| {0,10}   |   {1} | \n", "Process id", "Process name");

            try
            {
                // Получение списка процессов
                var processes = Process.GetProcesses().OrderBy(a=> a.ProcessName);
                // Вывод процессов в консоль
                foreach (var process in processes)
                {
                    Console.WriteLine("| {0,10}   |   {1}", process.Id, process.ProcessName);
                }
                Console.WriteLine();
            }
            catch (Exception ex) { }
        }
        
        private void ExecuteShutDownProcess()
        {
            var processId = 0;
            Console.WriteLine("Введите ID процесса: ");
            while(true)
            {
                var line = Console.ReadLine();
                if (int.TryParse(line, out int id) && id >= 0)
                {
                    processId = id;
                    break;
                }
                else
                {
                    Console.WriteLine("Введите положительное число от 0 до 2 147 483 647!");
                }
            }
            
            var processToKill = Process.GetProcessById(processId);
            try
            {
                processToKill.Kill();
                processToKill.WaitForExit();
                Console.WriteLine("Процесс успешно завершен.\n");
            }
            catch(Exception ex)
            {
                Console.WriteLine("Не удалось завершить процесс. Описание ошибки:");
                Console.WriteLine(ex.Message);
            }
        }

        private void ShowStageChoice()
        {
            Console.WriteLine("1. {0}", StageNames.ShowProcesses);
            Console.WriteLine("2. {0}", StageNames.ShutDownProcess);
            Console.WriteLine("3. {0}", StageNames.Exit);
        }

        private string GetNextStageKey()
        {
            var result = string.Empty;

            while (true)
            {
                try
                {
                    var line = Console.ReadLine();
                    if (LinesAndStageKeys.TryGetValue(line, out string value))
                    {
                        result = value;
                        break;
                    }
                    else
                    {
                        Console.WriteLine("Неверный формат запроса! Пожалуйста введите номер шага.");
                        continue;
                    }
                }
                catch
                {

                }
            }

            return result;
        }
    }

    public static class StageNames
    {
        public const string ShowProcesses = "Показать все процессы";

        public const string ShutDownProcess = "Завершить процесс по ID";

        public const string Exit = "Выход";
    }



}