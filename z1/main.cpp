#include <iostream>
#include <cctype>
#include <locale>
#include "modAlphaCipher.h"
using namespace std;

// проверка, чтобы строка состояла только из прописных русских букв
bool isValid(const wstring& s)
{
    for(auto c:s)
        if (!iswalpha(c) || !iswupper(c))
            return false;
    return true;
}

int main(int argc, char **argv)
{
    // Устанавливаем локаль для работы с русскими символами
    setlocale(LC_ALL, "");
    wstring key;
    wstring text;
    unsigned op;
    
    wcout << L"Шифр готов. Введите ключ: ";
    wcin >> key;
    
    if (!isValid(key)) {
        wcerr << L"Ключ недействителен\n";
        return 1;
    }
    
    wcout << L"Ключ загружен\n";
    modAlphaCipher cipher(key);
    
    do {
        wcout << L"Шифр готов. Выберите операцию (0-выход, 1-зашифровать, 2-расшифровать): ";
        wcin >> op;
        
        if (op > 2) {
            wcout << L"Неверная операция\n";
        } else if (op > 0) {
            wcout << L"Шифр готов. Введите текст: ";
            wcin >> text;
            
            if (isValid(text)) {
                if (op == 1) {
                    wcout << L"Зашифрованный текст: " << cipher.encrypt(text) << endl;
                } else {
                    wcout << L"Расшифрованный текст: " << cipher.decrypt(text) << endl;
                }
            } else {
                wcout << L"Операция отменена: неверный текст\n";
            }
        }
    } while (op != 0);
    
    return 0;
}