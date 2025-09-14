#include <iostream>
#include <string>

std::string removeComments(const std::string& sourceCode) {
    std::string result;
    result.reserve(sourceCode.size());

    bool inSingleLineComment = false;
    bool inMultiLineComment = false;
    bool inString = false;
    bool inChar = false;
    bool escapeNext = false; // Флаг для экранирования следующего символа

    for (size_t i = 0; i < sourceCode.size(); ++i) {
        char currentChar = sourceCode[i];
        char nextChar = (i + 1 < sourceCode.size()) ? sourceCode[i + 1] : '\0';

        // Обработка экранирования
        if (escapeNext) {
            // Текущий символ экранирован - обрабатываем как обычный символ
            if (!inSingleLineComment && !inMultiLineComment) {
                result += currentChar;
            }
            escapeNext = false;
            continue;
        }

        // Проверка на escape-символ
        if (currentChar == '\\' && (inString || inChar)) {
            escapeNext = true;
            if (!inSingleLineComment && !inMultiLineComment) {
                result += currentChar;
            }
            continue;
        }

        // Обработка строковых литералов
        if (!inSingleLineComment && !inMultiLineComment) {
            if (currentChar == '"' && !inChar && !escapeNext) {
                inString = !inString;
                result += currentChar;
                continue;
            }

            // Обработка символьных литералов
            if (currentChar == '\'' && !inString && !escapeNext) {
                inChar = !inChar;
                result += currentChar;
                continue;
            }

            if (inString || inChar) {
                result += currentChar;
                continue;
            }
        }

        // Обнаружение начала однострочного комментария
        if (!inMultiLineComment && !inString && !inChar &&
            currentChar == '/' && nextChar == '/') {
            // Проверяем, что это действительно комментарий
            bool isComment = true;

            if (i > 0) {
                char beforeChar = sourceCode[i - 1];
                // Если перед "//" есть символ, который может быть частью другого токена
                if (std::isalnum(beforeChar) || beforeChar == '_' || beforeChar == ':' ||
                    beforeChar == '/' || beforeChar == '.' || beforeChar == '\\') {
                    isComment = false;
                }
            }

            if (isComment) {
                inSingleLineComment = true;
                i++; // Пропускаем следующий символ '/'
                continue;
            }
        }

        // Обнаружение начала многострочного комментария
        if (!inSingleLineComment && !inString && !inChar &&
            currentChar == '/' && nextChar == '*') {
            inMultiLineComment = true;
            i++; // Пропускаем следующий символ '*'
            continue;
        }

        // Обнаружение конца многострочного комментария
        if (inMultiLineComment && currentChar == '*' && nextChar == '/') {
            inMultiLineComment = false;
            i++; // Пропускаем следующий символ '/'
            continue;
        }

        // Конец однострочного комментария (конец строки)
        if (inSingleLineComment && currentChar == '\n') {
            inSingleLineComment = false;
            result += currentChar; // Сохраняем перевод строки
            continue;
        }

        // Добавляем символ, если не в комментарии
        if (!inSingleLineComment && !inMultiLineComment) {
            result += currentChar;
        }
    }

    return result;
}


// Функция для демонстрации работы
void demonstrateCommentRemoval() {
    // Пример кода с комментариями
    std::string testCode =
        "#include <iostream>\n"
        "// Однострочный комментарий\n"
        "using namespace std;\n\n"
        "/* Многострочный комментарий\n"
        "   на нескольких строках */\n\n"
        "int main() {\n"
        "    cout << \"Hello, World!\" << endl; // Комментарий после кода\n"
        "    \n"
        "    string text = \"Это /* не комментарий */ в строке\";\n"
        "    char ch = '\\''; // Символ кавычки\n"
        "    char ch2 = '\\\\'; // Обратный слеш\n"
        "    \n"
        "    /* Комментарий в середине */ int x = 5; /* И еще один */\n"
        "    \n"
        "    // Комментарий с URL: http://example.com\n"
        "    int y = x + 1; // Прибавляем единицу\n"
        "    \n"
        "    return 0;\n"
        "}\n";

    std::cout << "Исходный код с комментариями:\n";
    std::cout << "========================================\n";
    std::cout << testCode << std::endl;

    std::string cleanedCode = removeComments(testCode);

    std::cout << "Код без комментариев:\n";
    std::cout << "========================================\n";
    std::cout << cleanedCode << std::endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    // Демонстрация работы функции
    demonstrateCommentRemoval();

    return 0;
}