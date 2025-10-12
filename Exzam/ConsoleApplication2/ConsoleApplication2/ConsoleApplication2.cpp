#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <memory>
#include <cmath>

struct Date {
    int day;
    int month;
    int year;

    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << day << "."
            << std::setw(2) << std::setfill('0') << month << "."
            << year;
        return oss.str();
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
};

class Transaction {
private:
    double amount;
    std::string category;
    Date date;
    std::string description;

public:
    Transaction(double amt, const std::string& cat, const Date& dt, const std::string& desc = "")
        : amount(amt), category(cat), date(dt), description(desc) {
    }

    double getAmount() const { return amount; }
    std::string getCategory() const { return category; }
    Date getDate() const { return date; }
    std::string getDescription() const { return description; }

    std::string toString() const {
        std::ostringstream oss;
        oss << "Дата: " << date.toString()
            << " | Категория: " << category
            << " | Сумма: " << std::fixed << std::setprecision(2) << amount;
        if (!description.empty()) {
            oss << " | Описание: " << description;
        }
        return oss.str();
    }
};

class FinancialAccount {
protected:
    std::string name;
    double balance;
    std::vector<Transaction> transactions;

public:
    FinancialAccount(const std::string& accName, double initialBalance = 0.0)
        : name(accName), balance(initialBalance) {
    }

    virtual ~FinancialAccount() = default;

    std::string getName() const { return name; }
    double getBalance() const { return balance; }
    const std::vector<Transaction>& getTransactions() const { return transactions; }

    void deposit(double amount, const std::string& description = "") {
        balance += amount;
        Date currentDate = getCurrentDate();
        transactions.emplace_back(amount, "Пополнение", currentDate, description);
        std::cout << "Пополнение " << name << " на " << amount << " руб.\n";
    }

    bool withdraw(double amount, const std::string& category, const std::string& description = "") {
        if (amount <= balance) {
            balance -= amount;
            Date currentDate = getCurrentDate();
            transactions.emplace_back(-amount, category, currentDate, description);
            std::cout << "Списание с " << name << " на " << amount << " руб. (Категория: " << category << ")\n";
            return true;
        }
        std::cout << "Ошибка: Недостаточно средств на " << name << "\n";
        return false;
    }

    virtual std::string getType() const = 0;

    static Date getCurrentDate() {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    }
};

class Wallet : public FinancialAccount {
public:
    Wallet(const std::string& walletName, double initialBalance = 0.0)
        : FinancialAccount(walletName, initialBalance) {
    }

    std::string getType() const override {
        return "Кошелек";
    }
};

class DebitCard : public FinancialAccount {
public:
    DebitCard(const std::string& cardName, double initialBalance = 0.0)
        : FinancialAccount(cardName, initialBalance) {
    }

    std::string getType() const override {
        return "Дебетовая карта";
    }
};

class PersonalFinanceManager {
private:
    std::vector<std::shared_ptr<FinancialAccount>> accounts;
    std::vector<std::string> categories;

public:
    PersonalFinanceManager() {
        categories = { "Еда", "Транспорт", "Жилье", "Развлечения", "Одежда",
                     "Здоровье", "Образование", "Подарки", "Прочее" };
    }

    void addAccount(std::shared_ptr<FinancialAccount> account) {
        accounts.push_back(account);
        std::cout << "Добавлен: " << account->getType() << " \"" << account->getName() << "\"\n";
    }

    void addCategory(const std::string& category) {
        if (std::find(categories.begin(), categories.end(), category) == categories.end()) {
            categories.push_back(category);
            std::cout << "Добавлена категория: " << category << "\n";
        }
    }

    void showAccounts() const {
        std::cout << "\n=== ВАШИ СЧЕТА ===\n";
        for (const auto& account : accounts) {
            std::cout << account->getType() << " \"" << account->getName() << "\"";
            std::cout << " | Баланс: " << std::fixed << std::setprecision(2) << account->getBalance() << " руб.\n";
        }
    }

    void showCategories() const {
        std::cout << "\n=== КАТЕГОРИИ ЗАТРАТ ===\n";
        for (size_t i = 0; i < categories.size(); ++i) {
            std::cout << i + 1 << ". " << categories[i] << "\n";
        }
    }

    std::string getCategoryByIndex(int index) const {
        if (index >= 0 && index < static_cast<int>(categories.size())) {
            return categories[index];
        }
        return "Прочее";
    }

    bool makeTransaction(int accountIndex, double amount, const std::string& category, const std::string& description = "") {
        if (accountIndex < 0 || accountIndex >= static_cast<int>(accounts.size())) {
            std::cout << "Ошибка: Неверный индекс счета\n";
            return false;
        }

        if (std::find(categories.begin(), categories.end(), category) == categories.end()) {
            std::cout << "Ошибка: Категория не найдена. Добавьте ее сначала.\n";
            return false;
        }

        return accounts[accountIndex]->withdraw(amount, category, description);
    }

    bool depositToAccount(int accountIndex, double amount, const std::string& description = "") {
        if (accountIndex < 0 || accountIndex >= static_cast<int>(accounts.size())) {
            std::cout << "Ошибка: Неверный индекс счета\n";
            return false;
        }

        accounts[accountIndex]->deposit(amount, description);
        return true;
    }

    void generateDailyReport(const Date& date) const {
        std::cout << "\n=== ОТЧЕТ ЗА ДЕНЬ " << date.toString() << " ===\n";

        std::map<std::string, double> categoryExpenses;
        double totalExpenses = 0;

        for (const auto& account : accounts) {
            for (const auto& transaction : account->getTransactions()) {
                if (transaction.getDate() == date && transaction.getAmount() < 0) {
                    std::string category = transaction.getCategory();
                    double amount = -transaction.getAmount(); 

                    categoryExpenses[category] += amount;
                    totalExpenses += amount;
                }
            }
        }

        if (categoryExpenses.empty()) {
            std::cout << "Затрат за этот день не найдено.\n";
            return;
        }

        for (const auto& [category, amount] : categoryExpenses) {
            double percentage = (totalExpenses > 0) ? (amount / totalExpenses * 100) : 0;
            std::cout << category << ": " << std::fixed << std::setprecision(2) << amount
                << " руб. (" << std::setprecision(1) << percentage << "%)\n";
        }

        std::cout << "Общие затраты: " << std::fixed << std::setprecision(2) << totalExpenses << " руб.\n";
    }

    void generateWeeklyReport(const Date& startDate) const {
        std::cout << "\n=== ОТЧЕТ ЗА НЕДЕЛЮ С " << startDate.toString() << " ===\n";

        std::map<std::string, double> categoryExpenses;
        double totalExpenses = 0;

        for (const auto& account : accounts) {
            for (const auto& transaction : account->getTransactions()) {
                Date transDate = transaction.getDate();
                if (isDateInWeek(transDate, startDate) && transaction.getAmount() < 0) {
                    std::string category = transaction.getCategory();
                    double amount = -transaction.getAmount(); 

                    categoryExpenses[category] += amount;
                    totalExpenses += amount;
                }
            }
        }

        if (categoryExpenses.empty()) {
            std::cout << "Затрат за эту неделю не найдено.\n";
            return;
        }

        for (const auto& [category, amount] : categoryExpenses) {
            double percentage = (totalExpenses > 0) ? (amount / totalExpenses * 100) : 0;
            std::cout << category << ": " << std::fixed << std::setprecision(2) << amount
                << " руб. (" << std::setprecision(1) << percentage << "%)\n";
        }

        std::cout << "Общие затраты за неделю: " << std::fixed << std::setprecision(2)
            << totalExpenses << " руб.\n";
    }

    void generateMonthlyReport(int month, int year) const {
        std::cout << "\n=== ОТЧЕТ ЗА МЕСЯЦ " << month << "." << year << " ===\n";

        std::map<std::string, double> categoryExpenses;
        double totalExpenses = 0;

        for (const auto& account : accounts) {
            for (const auto& transaction : account->getTransactions()) {
                Date transDate = transaction.getDate();
                if (transDate.month == month && transDate.year == year && transaction.getAmount() < 0) {
                    std::string category = transaction.getCategory();
                    double amount = -transaction.getAmount(); 

                    categoryExpenses[category] += amount;
                    totalExpenses += amount;
                }
            }
        }

        if (categoryExpenses.empty()) {
            std::cout << "Затрат за этот месяц не найдено.\n";
            return;
        }

        for (const auto& [category, amount] : categoryExpenses) {
            double percentage = (totalExpenses > 0) ? (amount / totalExpenses * 100) : 0;
            std::cout << category << ": " << std::fixed << std::setprecision(2) << amount
                << " руб. (" << std::setprecision(1) << percentage << "%)\n";
        }

        std::cout << "Общие затраты за месяц: " << std::fixed << std::setprecision(2)
            << totalExpenses << " руб.\n";
    }

    void generateTopExpensesReport(int periodType, const Date& date) const {
        std::vector<Transaction> periodTransactions;

        for (const auto& account : accounts) {
            for (const auto& transaction : account->getTransactions()) {
                if (transaction.getAmount() < 0) {
                    bool include = false;

                    if (periodType == 1) { 
                        include = isDateInWeek(transaction.getDate(), date);
                    }
                    else { 
                        include = (transaction.getDate().month == date.month &&
                            transaction.getDate().year == date.year);
                    }

                    if (include) {
                        periodTransactions.push_back(transaction);
                    }
                }
            }
        }

        std::sort(periodTransactions.begin(), periodTransactions.end(),
            [](const Transaction& a, const Transaction& b) {
                return std::abs(a.getAmount()) > std::abs(b.getAmount());
            });

        std::string periodName = (periodType == 1) ? "НЕДЕЛЮ" : "МЕСЯЦ";
        std::cout << "\n=== ТОП-3 ЗАТРАТ ЗА " << periodName << " ===\n";

        if (periodTransactions.empty()) {
            std::cout << "Затрат за указанный период не найдено.\n";
            return;
        }

        int count = 0;
        for (const auto& transaction : periodTransactions) {
            if (count >= 3) break;
            std::cout << count + 1 << ". " << transaction.toString() << "\n";
            count++;
        }
    }

    void generateTopCategoriesReport(int periodType, const Date& date) const {
        std::map<std::string, double> categoryTotals;

        for (const auto& account : accounts) {
            for (const auto& transaction : account->getTransactions()) {
                if (transaction.getAmount() < 0) {
                    bool include = false;

                    if (periodType == 1) { 
                        include = isDateInWeek(transaction.getDate(), date);
                    }
                    else { 
                        include = (transaction.getDate().month == date.month &&
                            transaction.getDate().year == date.year);
                    }

                    if (include) {
                        std::string category = transaction.getCategory();
                        double amount = -transaction.getAmount(); 
                        categoryTotals[category] += amount;
                    }
                }
            }
        }

        std::vector<std::pair<std::string, double>> sortedCategories(
            categoryTotals.begin(), categoryTotals.end());

        std::sort(sortedCategories.begin(), sortedCategories.end(),
            [](const auto& a, const auto& b) {
                return a.second > b.second;
            });

        std::string periodName = (periodType == 1) ? "НЕДЕЛЮ" : "МЕСЯЦ";
        std::cout << "\n=== ТОП-3 КАТЕГОРИЙ ЗА " << periodName << " ===\n";

        if (sortedCategories.empty()) {
            std::cout << "Затрат за указанный период не найдено.\n";
            return;
        }

        int count = 0;
        for (const auto& [category, amount] : sortedCategories) {
            if (count >= 3) break;
            std::cout << count + 1 << ". " << category << ": "
                << std::fixed << std::setprecision(2) << amount << " руб.\n";
            count++;
        }
    }

    void saveReportToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "ФИНАНСОВЫЙ ОТЧЕТ\n";
            file << "Сгенерировано: " << FinancialAccount::getCurrentDate().toString() << "\n\n";

            file << "СЧЕТА:\n";
            for (const auto& account : accounts) {
                file << account->getType() << " \"" << account->getName() << "\"";
                file << " | Баланс: " << std::fixed << std::setprecision(2) << account->getBalance() << " руб.\n";
            }

            file << "\nПОСЛЕДНИЕ ОПЕРАЦИИ:\n";
            for (const auto& account : accounts) {
                const auto& transactions = account->getTransactions();
                if (!transactions.empty()) {
                    file << account->getName() << ":\n";
                    for (const auto& transaction : transactions) {
                        file << "  " << transaction.toString() << "\n";
                    }
                }
            }

            file.close();
            std::cout << "Отчет сохранен в файл: " << filename << "\n";
        }
        else {
            std::cout << "Ошибка: Не удалось сохранить отчет в файл.\n";
        }
    }

private:
    bool isDateInWeek(const Date& checkDate, const Date& weekStart) const {
        return (checkDate.year == weekStart.year &&
            checkDate.month == weekStart.month &&
            checkDate.day >= weekStart.day &&
            checkDate.day < weekStart.day + 7);
    }
};

void displayMenu() {
    std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ ФИНАНСАМИ ===\n";
    std::cout << "1. Показать счета\n";
    std::cout << "2. Добавить счет\n";
    std::cout << "3. Пополнить счет\n";
    std::cout << "4. Расход\n";
    std::cout << "5. Показать категории\n";
    std::cout << "6. Добавить категорию\n";
    std::cout << "7. Отчет за день\n";
    std::cout << "8. Отчет за неделю\n";
    std::cout << "9. Отчет за месяц\n";
    std::cout << "10. ТОП-3 затрат\n";
    std::cout << "11. ТОП-3 категорий\n";
    std::cout << "12. Сохранить отчет в файл\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Ru");
    PersonalFinanceManager manager;

    manager.addAccount(std::make_shared<Wallet>("Наличные", 5000.0));
    manager.addAccount(std::make_shared<DebitCard>("Сбербанк", 15000.0));
    manager.addAccount(std::make_shared<DebitCard>("Тинькофф", 8000.0));

    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: {
            manager.showAccounts();
            break;
        }
        case 2: {
            std::string name, typeStr;
            double initialAmount; 

            std::cout << "Введите название счета: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Тип счета (wallet/debit): ";
            std::cin >> typeStr;

            std::cout << "Начальный баланс: ";
            std::cin >> initialAmount;

            if (typeStr == "wallet") {
                manager.addAccount(std::make_shared<Wallet>(name, initialAmount));
            }
            else if (typeStr == "debit") {
                manager.addAccount(std::make_shared<DebitCard>(name, initialAmount));
            }
            else {
                std::cout << "Неверный тип счета!\n";
            }
            break;
        }
        case 3: {
            manager.showAccounts();
            int accountIndex;
            double depositAmount; 
            std::string description;

            std::cout << "Выберите счет (номер): ";
            std::cin >> accountIndex;
            accountIndex--;

            std::cout << "Сумма пополнения: ";
            std::cin >> depositAmount;

            std::cout << "Описание: ";
            std::cin.ignore();
            std::getline(std::cin, description);

            manager.depositToAccount(accountIndex, depositAmount, description);
            break;
        }
        case 4: {
            manager.showAccounts();
            manager.showCategories();

            int accountIndex, categoryIndex;
            double expenseAmount; 
            std::string description;

            std::cout << "Выберите счет (номер): ";
            std::cin >> accountIndex;
            accountIndex--;

            std::cout << "Выберите категорию (номер): ";
            std::cin >> categoryIndex;
            categoryIndex--;

            std::cout << "Сумма затраты: ";
            std::cin >> expenseAmount;

            std::cout << "Описание: ";
            std::cin.ignore();
            std::getline(std::cin, description);

            std::string category = manager.getCategoryByIndex(categoryIndex);
            manager.makeTransaction(accountIndex, expenseAmount, category, description);
            break;
        }
        case 5: {
            manager.showCategories();
            break;
        }
        case 6: {
            std::string category;
            std::cout << "Введите название новой категории: ";
            std::cin.ignore();
            std::getline(std::cin, category);

            manager.addCategory(category);
            break;
        }
        case 7: {
            int day, month, year;
            std::cout << "Введите дату (день месяц год): ";
            std::cin >> day >> month >> year;

            Date date(day, month, year);
            manager.generateDailyReport(date);
            break;
        }
        case 8: {
            int day, month, year;
            std::cout << "Введите начало недели (день месяц год): ";
            std::cin >> day >> month >> year;

            Date startDate(day, month, year);
            manager.generateWeeklyReport(startDate);
            break;
        }
        case 9: {
            int month, year;
            std::cout << "Введите месяц и год: ";
            std::cin >> month >> year;

            manager.generateMonthlyReport(month, year);
            break;
        }
        case 10: {
            int periodType;
            std::cout << "Период (1 - неделя, 2 - месяц): ";
            std::cin >> periodType;

            int day, month, year;
            std::cout << "Введите дату (день месяц год): ";
            std::cin >> day >> month >> year;

            Date date(day, month, year);
            manager.generateTopExpensesReport(periodType, date);
            break;
        }
        case 11: {
            int periodType;
            std::cout << "Период (1 - неделя, 2 - месяц): ";
            std::cin >> periodType;

            int day, month, year;
            std::cout << "Введите дату (день месяц год): ";
            std::cin >> day >> month >> year;

            Date date(day, month, year);
            manager.generateTopCategoriesReport(periodType, date);
            break;
        }
        case 12: {
            manager.saveReportToFile("financial_report.txt");
            break;
        }
        case 0: {
            std::cout << "Выход из программы.\n";
            break;
        }
        default: {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
        }
    } while (choice != 0);

    return 0;
}