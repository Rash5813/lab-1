#include <iostream>
#include <string>
#include <limits>
#include <locale>
#include "routecipher.h"

// Функция для проверки ввода числа
int getValidNumber(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите целое число." << std::endl;
        } else if (value <= 0) {
            std::cout << "Ошибка! Число должно быть положительным." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return value;
}

// Функция для ввода текста
std::string getTextInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

// Функция для отображения главного меню
void displayMainMenu() {
    std::cout << "\n=== ШИФР ТАБЛИЧНОЙ МАРШРУТНОЙ ПЕРЕСТАНОВКИ ===" << std::endl;
    std::cout << "1. Зашифровать текст" << std::endl;
    std::cout << "2. Расшифровать текст" << std::endl;
    std::cout << "3. Изменить ключ (количество столбцов)" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите операцию: ";
}

int main() {
    // Установка локали для корректной работы с русскими символами
    setlocale(LC_ALL, "");
    
    std::cout << "=========================================" << std::endl;
    std::cout << "   ШИФР ТАБЛИЧНОЙ МАРШРУТНОЙ ПЕРЕСТАНОВКИ" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // Инициализация шифра
    int initialKey;
    try {
        initialKey = getValidNumber("Введите начальный ключ (количество столбцов): ");
    } catch (const std::exception& e) {
        std::cout << "Ошибка инициализации: " << e.what() << std::endl;
        return 1;
    }
    
    RouteCipher cipher(initialKey);
    
    std::cout << "\nШифр успешно инициализирован!" << std::endl;
    std::cout << "Текущий ключ: " << cipher.getKey() << " " << std::endl;
    std::cout << "Используйте меню для работы с программой." << std::endl;
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMainMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: {
                std::string text = getTextInput("Введите текст для шифрования: ");
                
                if (text.empty()) {
                    std::cout << "Ошибка! Текст не может быть пустым." << std::endl;
                    break;
                }
                
                try {
                    std::string encrypted = cipher.encrypt(text);
                    std::cout << "\n--- Результат шифрования ---" << std::endl;
                    std::cout << "Исходный текст: " << text << std::endl;
                    std::cout << "Зашифрованный текст: " << encrypted << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка при шифровании: " << e.what() << std::endl;
                }
                break;
            }
                
            case 2: {
                std::string text = getTextInput("Введите текст для расшифрования: ");
                
                if (text.empty()) {
                    std::cout << "Ошибка! Текст не может быть пустым." << std::endl;
                    break;
                }
                
                try {
                    std::string decrypted = cipher.decrypt(text);
                    std::cout << "\n--- Результат расшифрования ---" << std::endl;
                    std::cout << "Зашифрованный текст: " << text << std::endl;
                    std::cout << "Расшифрованный текст: " << decrypted << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка при расшифровании: " << e.what() << std::endl;
                }
                break;
            }
                
            case 3: {
                int newKey = getValidNumber("Введите новый ключ (количество столбцов): ");
                try {
                    cipher = RouteCipher(newKey);
                    std::cout << "Ключ успешно изменен на: " << newKey << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка при установке ключа: " << e.what() << std::endl;
                }
                break;
            }
                
            case 0:
                running = false;
                std::cout << "\nВыход из программы. До свидания!" << std::endl;
                break;
                
            default:
                std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
                break;
        }
        
        if (running && choice != 0) {
            std::cout << "\nНажмите Enter для продолжения...";
            std::cin.get();
        }
    }
    
    return 0;
}