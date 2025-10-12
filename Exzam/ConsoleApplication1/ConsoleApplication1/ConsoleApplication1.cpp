#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <locale>

namespace fs = std::filesystem;

class FileSystemEntity {
protected:
    fs::path path;

public:
    FileSystemEntity(const std::string& path) : path(path) {}
    virtual ~FileSystemEntity() = default;

    virtual bool exists() const = 0;
    virtual uintmax_t size() const = 0;
    virtual void create() = 0;
    virtual void remove() = 0;
    virtual void rename(const std::string& newName) = 0;
    virtual bool isDirectory() const = 0;

    std::string getName() const { return path.filename().string(); }
    std::string getPath() const { return path.string(); }
    std::string getParentPath() const { return path.parent_path().string(); }

    virtual void printInfo() const {
        std::cout << "Имя: " << getName() << std::endl;
        std::cout << "Путь: " << getPath() << std::endl;
        std::cout << "Размер: " << size() << " байт" << std::endl;
    }
};

class File : public FileSystemEntity {
public:
    File(const std::string& path) : FileSystemEntity(path) {}

    bool exists() const override {
        return fs::exists(path) && fs::is_regular_file(path);
    }

    uintmax_t size() const override {
        return exists() ? fs::file_size(path) : 0;
    }

    void create() override {
        if (!exists()) {
            std::ofstream file(path);
            if (file.is_open()) {
                file.close();
                std::cout << "Файл создан: " << path << std::endl;
            }
        }
        else {
            std::cout << "Файл уже существует: " << path << std::endl;
        }
    }

    void remove() override {
        if (exists()) {
            fs::remove(path);
            std::cout << "Файл удален: " << path << std::endl;
        }
        else {
            std::cout << "Файл не существует: " << path << std::endl;
        }
    }

    void rename(const std::string& newName) override {
        if (exists()) {
            fs::path newPath = path.parent_path() / newName;
            if (fs::exists(newPath)) {
                std::cout << "Элемент с таким именем уже существует: " << newName << std::endl;
                return;
            }
            fs::rename(path, newPath);
            path = newPath;
            std::cout << "Файл переименован: " << newName << std::endl;
        }
        else {
            std::cout << "Файл не существует: " << path << std::endl;
        }
    }

    bool isDirectory() const override { return false; }

    void printInfo() const override {
        FileSystemEntity::printInfo();
        std::cout << "Тип: Файл" << std::endl;

        if (exists()) {
            auto ftime = fs::last_write_time(path);
            auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
            std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
            std::cout << "Изменен: " << std::ctime(&cftime);
        }
    }
};

class Directory : public FileSystemEntity {
public:
    Directory(const std::string& path) : FileSystemEntity(path) {}

    bool exists() const override {
        return fs::exists(path) && fs::is_directory(path);
    }

    uintmax_t size() const override {
        if (!exists()) return 0;

        uintmax_t totalSize = 0;
        try {
            for (const auto& entry : fs::recursive_directory_iterator(path)) {
                if (entry.is_regular_file()) {
                    totalSize += entry.file_size();
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Ошибка при вычислении размера: " << e.what() << std::endl;
        }
        return totalSize;
    }

    void create() override {
        if (!exists()) {
            fs::create_directories(path);
            std::cout << "Папка создана: " << path << std::endl;
        }
        else {
            std::cout << "Папка уже существует: " << path << std::endl;
        }
    }

    void remove() override {
        if (exists()) {
            fs::remove_all(path);
            std::cout << "Папка удалена: " << path << std::endl;
        }
        else {
            std::cout << "Папка не существует: " << path << std::endl;
        }
    }

    void rename(const std::string& newName) override {
        if (exists()) {
            fs::path newPath = path.parent_path() / newName;
            if (fs::exists(newPath)) {
                std::cout << "Элемент с таким именем уже существует: " << newName << std::endl;
                return;
            }
            fs::rename(path, newPath);
            path = newPath;
            std::cout << "Папка переименована: " << newName << std::endl;
        }
        else {
            std::cout << "Папка не существует: " << path << std::endl;
        }
    }

    bool isDirectory() const override { return true; }

    std::vector<std::string> getContents() const {
        std::vector<std::string> contents;
        if (exists()) {
            try {
                for (const auto& entry : fs::directory_iterator(path)) {
                    contents.push_back(entry.path().filename().string());
                }
            }
            catch (const fs::filesystem_error& e) {
                std::cout << "Ошибка доступа к папке: " << e.what() << std::endl;
            }
        }
        return contents;
    }

    void printInfo() const override {
        FileSystemEntity::printInfo();
        std::cout << "Тип: Папка" << std::endl;
        std::cout << "Количество элементов: " << getContents().size() << std::endl;
    }
};

class FileManager {
private:
    std::string currentPath;

    std::string buildPath(const std::string& name) const {
        fs::path fullPath = fs::path(currentPath) / name;
        return fullPath.string();
    }

    bool isAbsolutePath(const std::string& path) const {
        return fs::path(path).is_absolute();
    }

    bool startsWith(const std::string& str, const std::string& prefix) const {
        return str.compare(0, prefix.length(), prefix) == 0;
    }

    bool endsWith(const std::string& str, const std::string& suffix) const {
        if (suffix.length() > str.length()) return false;
        return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
    }

public:
    FileManager() : currentPath(fs::current_path().string()) {}

    void showContents() const {
        std::cout << "\nТекущая директория: " << currentPath << std::endl;
        std::cout << "Содержимое:" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        Directory dir(currentPath);
        if (!dir.exists()) {
            std::cout << "Директория не существует!" << std::endl;
            return;
        }

        auto contents = dir.getContents();

        if (contents.empty()) {
            std::cout << "Папка пуста" << std::endl;
        }
        else {
            for (const auto& item : contents) {
                std::string fullPath = buildPath(item);
                if (fs::is_directory(fullPath)) {
                    std::cout << "[ПАПКА]  " << item << std::endl;
                }
                else {
                    std::cout << "[ФАЙЛ]   " << item << " (" << fs::file_size(fullPath) << " байт)" << std::endl;
                }
            }
        }
    }

    void showDrives() const {
        std::cout << "\nДоступные диски:" << std::endl;
        std::cout << std::string(30, '-') << std::endl;

#ifdef _WIN32
        for (char drive = 'A'; drive <= 'Z'; ++drive) {
            std::string drivePath = std::string(1, drive) + ":\\";
            if (fs::exists(drivePath)) {
                try {
                    auto space = fs::space(drivePath);
                    std::cout << "Диск " << drive << ": " << drivePath
                        << " (Свободно: " << space.free / (1024 * 1024 * 1024) << " GB)" << std::endl;
                }
                catch (...) {
                    std::cout << "Диск " << drive << ": " << drivePath << std::endl;
                }
            }
        }
#else
        std::cout << "Корневая директория: /" << std::endl;
        try {
            for (const auto& entry : fs::directory_iterator("/")) {
                if (fs::is_directory(entry)) {
                    std::cout << "Папка: " << entry.path().string() << std::endl;
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Ошибка доступа: " << e.what() << std::endl;
        }
#endif
    }

    void createFolder(const std::string& folderName) {
        if (folderName.empty()) {
            std::cout << "Имя папки не может быть пустым!" << std::endl;
            return;
        }

        std::string fullPath = buildPath(folderName);
        Directory dir(fullPath);
        dir.create();
    }

    void createFile(const std::string& fileName) {
        if (fileName.empty()) {
            std::cout << "Имя файла не может быть пустым!" << std::endl;
            return;
        }

        std::string fullPath = buildPath(fileName);  
        File file(fullPath);
        file.create();
    }

    void deleteEntity(const std::string& entityName) {
        if (entityName.empty()) {
            std::cout << "Имя элемента не может быть пустым!" << std::endl;
            return;
        }

        std::string fullPath = buildPath(entityName);

        if (!fs::exists(fullPath)) {
            std::cout << "Элемент не существует: " << entityName << std::endl;
            return;
        }

        std::cout << "Вы уверены, что хотите удалить '" << entityName << "'? (y/n): ";
        char confirm;
        std::cin >> confirm;
        std::cin.ignore();

        if (confirm == 'y' || confirm == 'Y') {
            if (fs::is_directory(fullPath)) {
                Directory dir(fullPath);
                dir.remove();
            }
            else {
                File file(fullPath);
                file.remove();
            }
        }
        else {
            std::cout << "Удаление отменено" << std::endl;
        }
    }

    void renameEntity(const std::string& oldName, const std::string& newName) {
        if (oldName.empty() || newName.empty()) {
            std::cout << "Имена не могут быть пустыми!" << std::endl;
            return;
        }

        std::string oldPath = buildPath(oldName);
        std::string newPath = buildPath(newName);

        if (!fs::exists(oldPath)) {
            std::cout << "Исходный элемент не существует: " << oldName << std::endl;
            return;
        }

        if (fs::exists(newPath)) {
            std::cout << "Элемент с таким именем уже существует: " << newName << std::endl;
            return;
        }

        if (fs::is_directory(oldPath)) {
            Directory dir(oldPath);
            dir.rename(newName);
        }
        else {
            File file(oldPath);
            file.rename(newName);
        }
    }

    void copyEntity(const std::string& source, const std::string& destination) {
        if (source.empty() || destination.empty()) {
            std::cout << "Имена не могут быть пустыми!" << std::endl;
            return;
        }

        std::string sourcePath, destPath;

        if (isAbsolutePath(destination)) {
            sourcePath = buildPath(source);
            destPath = destination;
        }
        else {
            sourcePath = buildPath(source);
            destPath = buildPath(destination);
        }

        if (!fs::exists(sourcePath)) {
            std::cout << "Исходный элемент не существует: " << source << std::endl;
            return;
        }

        try {
            if (fs::is_directory(sourcePath)) {
                fs::copy(sourcePath, destPath, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
            }
            else {
                fs::copy_file(sourcePath, destPath, fs::copy_options::overwrite_existing);
            }
            std::cout << "Скопировано: " << source << " -> " << destPath << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Ошибка копирования: " << e.what() << std::endl;
        }
    }

    void moveEntity(const std::string& source, const std::string& destination) {
        if (source.empty() || destination.empty()) {
            std::cout << "Имена не могут быть пустыми!" << std::endl;
            return;
        }

        std::string sourcePath, destPath;

        if (isAbsolutePath(destination)) {
            sourcePath = buildPath(source);
            destPath = destination;
        }
        else {
            sourcePath = buildPath(source);
            destPath = buildPath(destination);
        }

        if (fs::exists(destPath) && fs::is_directory(destPath)) {
            destPath = (fs::path(destPath) / fs::path(sourcePath).filename()).string(); 
        }

        std::cout << "Перемещение: " << sourcePath << " -> " << destPath << std::endl;

        if (!fs::exists(sourcePath)) {
            std::cout << "Исходный элемент не существует: " << source << std::endl;
            return;
        }

        if (fs::exists(destPath)) {
            std::cout << "Целевой элемент уже существует: " << destPath << std::endl;
            return;
        }

        try {
            fs::create_directories(fs::path(destPath).parent_path());

            fs::rename(sourcePath, destPath);
            std::cout << "Успешно перемещено: " << source << " -> " << destPath << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Ошибка перемещения: " << e.what() << std::endl;

            std::cout << "Попытка альтернативного метода (копирование + удаление)..." << std::endl;
            try {
                if (fs::is_directory(sourcePath)) {
                    fs::copy(sourcePath, destPath, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                    fs::remove_all(sourcePath);
                }
                else {
                    fs::copy_file(sourcePath, destPath, fs::copy_options::overwrite_existing);
                    fs::remove(sourcePath);
                }
                std::cout << "Успешно перемещено альтернативным методом!" << std::endl;
            }
            catch (const fs::filesystem_error& e2) {
                std::cout << "Ошибка альтернативного перемещения: " << e2.what() << std::endl;
            }
        }
    }

    void calculateSize(const std::string& entityName) {
        if (entityName.empty()) {
            std::cout << "Имя элемента не может быть пустым!" << std::endl;
            return;
        }

        std::string fullPath = buildPath(entityName);

        if (!fs::exists(fullPath)) {
            std::cout << "Элемент не существует: " << entityName << std::endl;
            return;
        }

        if (fs::is_directory(fullPath)) {
            Directory dir(fullPath);
            uintmax_t size = dir.size();
            std::cout << "Размер папки '" << entityName << "': "
                << size << " байт (" << (size / (1024.0 * 1024.0)) << " MB)" << std::endl;
        }
        else {
            File file(fullPath);
            uintmax_t size = file.size();
            std::cout << "Размер файла '" << entityName << "': "
                << size << " байт (" << (size / 1024.0) << " KB)" << std::endl;
        }
    }

    void searchByMask(const std::string& mask, bool searchSubfolders = true) {
        if (mask.empty()) {
            std::cout << "Маска поиска не может быть пустой!" << std::endl;
            return;
        }

        std::cout << "\nПоиск по маске: " << mask << std::endl;
        std::cout << "В директории: " << currentPath << std::endl;
        std::cout << std::string(40, '-') << std::endl;

        size_t foundCount = searchInDirectory(currentPath, mask, searchSubfolders, 0);
        std::cout << "Найдено элементов: " << foundCount << std::endl;
    }

    void changeDirectory(const std::string& newPath) {
        if (newPath.empty()) {
            std::cout << "Путь не может быть пустым!" << std::endl;
            return;
        }

        fs::path targetPath = newPath;
        if (!targetPath.is_absolute()) {
            targetPath = fs::absolute(currentPath) / newPath;
        }

        if (fs::exists(targetPath) && fs::is_directory(targetPath)) {
            currentPath = fs::absolute(targetPath).string();
            std::cout << "Текущая директория изменена на: " << currentPath << std::endl;
        }
        else {
            std::cout << "Директория не существует: " << newPath << std::endl;
        }
    }

    std::string getCurrentPath() const {
        return currentPath;
    }

private:
    size_t searchInDirectory(const std::string& dirPath, const std::string& mask, bool searchSubfolders, size_t depth) const {
        size_t count = 0;

        try {
            for (const auto& entry : fs::directory_iterator(dirPath)) {
                std::string fileName = entry.path().filename().string();

                if (matchesMask(fileName, mask)) {
                    std::string indent(depth * 2, ' ');
                    if (entry.is_directory()) {
                        std::cout << indent << "[ПАПКА]  " << entry.path().string() << std::endl;
                    }
                    else {
                        std::cout << indent << "[ФАЙЛ]   " << entry.path().string()
                            << " (" << entry.file_size() << " байт)" << std::endl;
                    }
                    count++;
                }

                if (searchSubfolders && entry.is_directory()) {
                    count += searchInDirectory(entry.path().string(), mask, searchSubfolders, depth + 1);
                }
            }
        }
        catch (const fs::filesystem_error& ex) {
        }

        return count;
    }

    bool matchesMask(const std::string& fileName, const std::string& mask) const {
        if (mask == "*") return true;
        if (mask.find('*') == std::string::npos && mask.find('?') == std::string::npos) {
            return fileName == mask;
        }

        size_t pos = mask.find('*');
        if (pos != std::string::npos) {
            std::string prefix = mask.substr(0, pos);
            std::string suffix = mask.substr(pos + 1);

            if (prefix.empty() && suffix.empty()) return true;
            if (prefix.empty()) return endsWith(fileName, suffix);
            if (suffix.empty()) return startsWith(fileName, prefix);

            return startsWith(fileName, prefix) && endsWith(fileName, suffix);
        }

        return fileName.find(mask) != std::string::npos;
    }
};

void showMenu() {
    std::cout << "\n=== ФАЙЛОВЫЙ МЕНЕДЖЕР ===" << std::endl;
    std::cout << "1. Показать содержимое текущей директории" << std::endl;
    std::cout << "2. Показать доступные диски" << std::endl;
    std::cout << "3. Создать папку" << std::endl;
    std::cout << "4. Создать файл" << std::endl;
    std::cout << "5. Удалить файл/папку" << std::endl;
    std::cout << "6. Переименовать файл/папку" << std::endl;
    std::cout << "7. Копировать файл/папку" << std::endl;
    std::cout << "8. Переместить файл/папку" << std::endl;
    std::cout << "9. Вычислить размер" << std::endl;
    std::cout << "10. Поиск по маске" << std::endl;
    std::cout << "11. Сменить директорию" << std::endl;
    std::cout << "12. Показать текущий путь" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите опцию: ";
}

int main() {
    setlocale(LC_ALL, "RU");
    std::cout << "Файловый менеджер запущен" << std::endl;

    FileManager fm;
    int choice;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
        case 1: {
            fm.showContents();
            break;
        }
        case 2: {
            fm.showDrives();
            break;
        }
        case 3: {
            std::string folderName;
            std::cout << "Введите имя папки: ";
            std::getline(std::cin, folderName);
            fm.createFolder(folderName);
            break;
        }
        case 4: {
            std::string fileName;
            std::cout << "Введите имя файла: ";
            std::getline(std::cin, fileName);
            fm.createFile(fileName);
            break;
        }
        case 5: {
            std::string entityName;
            std::cout << "Введите имя файла/папки для удаления: ";
            std::getline(std::cin, entityName);
            fm.deleteEntity(entityName);
            break;
        }
        case 6: {
            std::string oldName, newName;
            std::cout << "Введите текущее имя: ";
            std::getline(std::cin, oldName);
            std::cout << "Введите новое имя: ";
            std::getline(std::cin, newName);
            fm.renameEntity(oldName, newName);
            break;
        }
        case 7: {
            std::string source, destination;
            std::cout << "Введите исходное имя: ";
            std::getline(std::cin, source);
            std::cout << "Введите целевое имя (или полный путь): ";
            std::getline(std::cin, destination);
            fm.copyEntity(source, destination);
            break;
        }
        case 8: {
            std::string source, destination;
            std::cout << "Введите исходное имя: ";
            std::getline(std::cin, source);
            std::cout << "Введите целевое имя (или полный путь): ";
            std::getline(std::cin, destination);
            fm.moveEntity(source, destination);
            break;
        }
        case 9: {
            std::string entityName;
            std::cout << "Введите имя файла/папки: ";
            std::getline(std::cin, entityName);
            fm.calculateSize(entityName);
            break;
        }
        case 10: {
            std::string mask;
            std::cout << "Введите маску для поиска (например, *.txt): ";
            std::getline(std::cin, mask);
            fm.searchByMask(mask);
            break;
        }
        case 11: {
            std::string newPath;
            std::cout << "Введите путь к новой директории: ";
            std::getline(std::cin, newPath);
            fm.changeDirectory(newPath);
            break;
        }
        case 12: {
            std::cout << "Текущий путь: " << fm.getCurrentPath() << std::endl;
            break;
        }
        case 0: {
            std::cout << "До свидания!" << std::endl;
            break;
        }
        default: {
            std::cout << "Неверная опция!" << std::endl;
            break;
        }
        }

    } while (choice != 0);

    return 0;
}