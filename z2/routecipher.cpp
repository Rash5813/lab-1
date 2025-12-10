#include "routecipher.h"
#include <iostream>
#include <string>
#include <vector>

RouteCipher::RouteCipher(int key) {
    if (key <= 0) {
        throw std::invalid_argument("Key must be positive");
    }
    columns = key;
}

int RouteCipher::getKey() const {
    return columns;
}

std::vector<std::string> RouteCipher::splitUTF8(const std::string& str) const {
    std::vector<std::string> characters;
    for (size_t i = 0; i < str.length();) {
        int charWidth = 0;
        unsigned char c = str[i];
        
        if ((c & 0x80) == 0) { // 1-byte character (ASCII)
            charWidth = 1;
        } else if ((c & 0xE0) == 0xC0) { // 2-byte character
            charWidth = 2;
        } else if ((c & 0xF0) == 0xE0) { // 3-byte character
            charWidth = 3;
        } else if ((c & 0xF8) == 0xF0) { // 4-byte character
            charWidth = 4;
        } else {
            charWidth = 1; // Некорректный символ, но продолжаем
        }
        
        characters.push_back(str.substr(i, charWidth));
        i += charWidth;
    }
    return characters;
}

std::string RouteCipher::encrypt(const std::string& text) const {
    if (text.empty()) return "";
    
    auto chars = splitUTF8(text);
    int rows = (chars.size() + columns - 1) / columns;
    std::vector<std::vector<std::string>> table(rows, std::vector<std::string>(columns, " "));
    
    // Запись: слева направо, сверху вниз
    for (size_t i = 0; i < chars.size(); i++) {
        int row = i / columns;
        int col = i % columns;
        table[row][col] = chars[i];
    }
    
    // Чтение: сверху вниз, справа налево
    std::string result;
    for (int col = columns - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            if (table[row][col] != " ") {
                result += table[row][col];
            }
        }
    }
    
    return result;
}

std::string RouteCipher::decrypt(const std::string& text) const {
    if (text.empty()) return "";
    
    auto chars = splitUTF8(text);
    int rows = (chars.size() + columns - 1) / columns;
    std::vector<std::vector<std::string>> table(rows, std::vector<std::string>(columns, " "));
    
    // Запись: сверху вниз, справа налево
    int index = 0;
    for (int col = columns - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            if (index < chars.size()) {
                table[row][col] = chars[index++];
            }
        }
    }
    
    // Чтение: слева направо, сверху вниз
    std::string result;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            if (table[row][col] != " ") {
                result += table[row][col];
            }
        }
    }
    
    return result;
}

void RouteCipher::demonstrateEncryption(const std::string& text) const {
    std::cout << "\n=== Демонстрация процесса шифрования ===" << std::endl;
    std::cout << "Исходный текст: " << text << std::endl;
    std::cout << "Ключ (количество столбцов): " << columns << std::endl;
    
    auto chars = splitUTF8(text);
    int rows = (chars.size() + columns - 1) / columns;
    
    std::cout << "Количество строк: " << rows << std::endl;
    std::cout << "Таблица для записи:" << std::endl;
    
    // Создаем и отображаем таблицу
    std::vector<std::vector<std::string>> table(rows, std::vector<std::string>(columns, " "));
    
    // Заполняем таблицу
    for (size_t i = 0; i < chars.size(); i++) {
        int row = i / columns;
        int col = i % columns;
        table[row][col] = chars[i];
    }
    
    // Отображаем таблицу
    for (int i = 0; i < rows; i++) {
        std::cout << "|";
        for (int j = 0; j < columns; j++) {
            std::cout << " " << table[i][j] << " |";
        }
        std::cout << std::endl;
    }
    
    std::cout << "Чтение таблицы (сверху вниз, справа налево):" << std::endl;
    std::string encrypted;
    for (int col = columns - 1; col >= 0; col--) {
        std::cout << "Столбец " << col + 1 << ": ";
        for (int row = 0; row < rows; row++) {
            if (table[row][col] != " ") {
                std::cout << table[row][col] << " ";
                encrypted += table[row][col];
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "Результат шифрования: " << encrypted << std::endl;
}