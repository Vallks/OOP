#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class PrintJob
{
    std::string user;
    int priority;
    int pages; 
    time_t timestamp;
    int jobId;

public:
    static int nextJobId;

    PrintJob(const std::string& user, int priority, int pages = 1) : user(user), priority(priority), pages(pages)
    {
        timestamp = time(0);
        jobId = nextJobId++;
    }

    std::string getUser() const { return user; }
    int getPriority() const { return priority; }
    int getPages() const { return pages; } 
    int getJobId() const { return jobId; }
    time_t getTimestamp() const { return timestamp; }

    bool operator<(const PrintJob& other) const
    {
        return priority > other.priority;
    }
};

int PrintJob::nextJobId = 1;

class PrintStat
{
    PrintJob job;
    time_t completionTime;
    bool success;

public:
    PrintStat(const PrintJob& job, bool success = true) : job(job), success(success)
    {
        completionTime = time(0);
    }

    const PrintJob& getJob() const { return job; }
    bool isSuccess() const { return success; }
    time_t getCompletionTime() const { return completionTime; } 
    double getProcessingTimeSeconds() const
    {
        return difftime(completionTime, job.getTimestamp());
    }
};

class Printer {
    std::priority_queue<PrintJob> printQueue;
    std::queue<PrintStat> statistics;
    bool isRunning;

public:
    Printer() : isRunning(false) {} 

    void addJob(const PrintJob& job)
    {
        printQueue.push(job);
        std::cout << "Добавлено задание #" << job.getJobId()
            << " от пользователя '" << job.getUser()
            << "' с приоритетом " << job.getPriority()
            << " (" << job.getPages() << " стр.)\n"; 
    }

    void processJobs() {
        while (isRunning && !printQueue.empty())
        {
            PrintJob job = printQueue.top();
            printQueue.pop();

            std::cout << "\nПечатается задание #" << job.getJobId()
                << " от '" << job.getUser()
                << "' (" << job.getPages() << " стр.)\n"; 

            statistics.push(PrintStat(job));

            std::cout << "Задание #" << job.getJobId()
                << " от '" << job.getUser()
                << "' завершено\n";
        }
    }

    void start()
    {
        isRunning = true;
        processJobs();
    }

    void stop()
    {
        isRunning = false;
    }

    void showQueue() const {
        if (printQueue.empty())
        {
            std::cout << "\nОчередь печати пуста.\n";
            return;
        }

        std::cout << "\nТекущая очередь печати:\n";
        std::cout << "ID\tПользователь\tПриоритет\tСтраниц\tВремя\n"; 
        std::cout << "---------------------------------------------\n";

        auto tempQueue = printQueue;
        while (!tempQueue.empty())
        {
            auto job = tempQueue.top();
            std::cout << job.getJobId() << "\t"
                << job.getUser() << "\t\t"
                << job.getPriority() << "\t\t"
                << job.getPages() << "\t\t" 
                << job.getTimestamp() << "\n";
            tempQueue.pop();
        }
    }

    void showStatistics() const {
        if (statistics.empty()) {
            std::cout << "\nСтатистика печати отсутствует.\n";
            return;
        }

        std::cout << "\nСтатистика печати:\n";
        std::cout << "ID\tПользователь\tПриоритет\tСтраниц\tНачало\tЗавершение\tВремя(сек)\n"; 
        std::cout << "---------------------------------------------------------------------\n";

        auto tempStats = statistics;
        while (!tempStats.empty())
        {
            auto stat = tempStats.front();
            auto job = stat.getJob();

            std::cout << job.getJobId() << "\t"
                << job.getUser() << "\t\t"
                << job.getPriority() << "\t\t"
                << job.getPages() << "\t\t" // Добавлен вывод количества страниц
                << job.getTimestamp() << "\t"
                << stat.getCompletionTime() << "\t" // Исправлено: getCompletionTime()
                << stat.getProcessingTimeSeconds() << "\n";

            tempStats.pop();
        }
    }

    size_t getQueueSize() const
    {
        return printQueue.size();
    }

    size_t getStatsSize() const
    {
        return statistics.size();
    }

    void clearQueue()
    {
        while (!printQueue.empty())
        {
            printQueue.pop();
        }
    }
};

void generateRandomJobs(Printer& printer, int count)
{
    std::vector<std::string> users = { "Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов", "Попов", "Васильев", "Павлов", "Семенов" };

    srand(time(0));

    for (int i = 0; i < count; ++i)
    {
        std::string user = users[rand() % users.size()];
        int priority = rand() % 5 + 1;
        int pages = rand() % 10 + 1;

        printer.addJob(PrintJob(user, priority, pages));
    }
}

void showMenu() {
    std::cout << "\n=== Меню управления принтером ===\n";
    std::cout << "1. Добавить задание печати\n";
    std::cout << "2. Показать очередь печати\n";
    std::cout << "3. Показать статистику\n";
    std::cout << "4. Обработать очередь\n";
    std::cout << "5. Сгенерировать случайные задания\n";
    std::cout << "6. Очистить очередь\n";
    std::cout << "7. Очистить экран\n";
    std::cout << "8. Выход\n";
    std::cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Ru");

    Printer printer; 
    int choice;

    std::cout << "Система управления печатью запущена\n";

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::string user;
            int priority, pages;

            std::cout << "Введите имя пользователя: ";
            std::getline(std::cin, user);
            std::cout << "Введите приоритет (1-5, где 1 - высший): ";
            std::cin >> priority;
            std::cout << "Введите количество страниц: ";
            std::cin >> pages;

            if (priority < 1) priority = 1;
            if (priority > 5) priority = 5;
            if (pages < 1) pages = 1;

            printer.addJob(PrintJob(user, priority, pages));
            break;
        }
        case 2:
            printer.showQueue();
            break;
        case 3:
            printer.showStatistics();
            break;
        case 4:
            printer.start();
            break;
        case 5: {
            int count;
            std::cout << "Сколько заданий сгенерировать? ";
            std::cin >> count;
            if (count > 0) {
                generateRandomJobs(printer, count);
            }
            break;
        }
        case 6:
            printer.clearQueue();
            std::cout << "Очередь очищена\n";
            break;
        case 7:
            system("cls");
            break;
        case 8:
            std::cout << "Завершение работы...\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }

        std::cout << "\nТекущий размер очереди: " << printer.getQueueSize()
            << ", выполнено заданий: " << printer.getStatsSize() << "\n";

    } while (choice != 8);

    return 0;
}