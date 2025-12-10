#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class RouteCipher {
private:
    int columns;
    
    // Функция для корректного разделения UTF-8 строки на символы
    std::vector<std::string> splitUTF8(const std::string& str) const;

public:
    // Запрещаем конструктор по умолчанию
    RouteCipher() = delete;
    
    // Конструктор с установкой ключа
    RouteCipher(int key);
    
    // Метод шифрования
    std::string encrypt(const std::string& text) const;
    
    // Метод дешифрования
    std::string decrypt(const std::string& text) const;
    
    // Геттер для ключа
    int getKey() const;
    
    // Функция для демонстрации процесса шифрования
    void demonstrateEncryption(const std::string& text) const;
};