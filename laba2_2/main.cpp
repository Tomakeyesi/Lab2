#include <iostream>
#include <string>
#include <locale>
#include "routeCipher.h"

using namespace std;

void testRouteCipher()
{
    locale::global(locale("ru_RU.utf8"));
    wcout.imbue(locale());
    wcerr.imbue(locale());

    // Тест 1: Корректные данные
    wcout << L"Тест 1: Корректные данные" << endl;
    try {
        routeCipher cipher1(4);
        wstring text1 = L"ПРИВЕТ МИР";
        wcout << L"Текст: \"" << text1 << L"\"" << endl;
        wcout << L"Количество столбцов: " << 4 << endl;
        
        wstring encrypted1 = cipher1.encrypt(text1);
        wcout << L"Зашифровано: " << encrypted1 << endl;
        
        wstring decrypted1 = cipher1.decrypt(encrypted1);
        wcout << L"Расшифровано: " << decrypted1 << endl;
        
        wcout << L"УСПЕХ" << endl;
    } catch (const route_cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
    }
    wcout << L"-------------------" << endl;

    // Тест 2: Пустой текст
    wcout << L"Тест 2: Пустой текст" << endl;
    try {
        routeCipher cipher2(3);
        wstring text2 = L"";
        wcout << L"Текст: \"" << text2 << L"\"" << endl;
        wcout << L"Количество столбцов: " << 3 << endl;
        
        wstring encrypted2 = cipher2.encrypt(text2);
        wcout << L"Зашифровано: " << encrypted2 << endl;
    } catch (const route_cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
    }
    wcout << L"-------------------" << endl;

    // Тест 3: Текст без букв
    wcout << L"Тест 3: Текст без букв" << endl;
    try {
        routeCipher cipher3(3);
        wstring text3 = L"123456 !@#$";
        wcout << L"Текст: \"" << text3 << L"\"" << endl;
        wcout << L"Количество столбцов: " << 3 << endl;
        
        wstring encrypted3 = cipher3.encrypt(text3);
        wcout << L"Зашифровано: " << encrypted3 << endl;
    } catch (const route_cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
    }
    wcout << L"-------------------" << endl;

    // Тест 4: Неверное количество столбцов
    wcout << L"Тест 4: Неверное количество столбцов" << endl;
    try {
        wcout << L"Количество столбцов: " << 0 << endl;
        routeCipher cipher4(0);
        wcout << L"Шифр создан успешно" << endl;
    } catch (const route_cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
    }
    wcout << L"-------------------" << endl;

    // Тест 5: Испорченный зашифрованный текст
    wcout << L"Тест 5: Испорченный зашифрованный текст" << endl;
    try {
        routeCipher cipher5(5);
        wstring text5 = L"КОМПЬЮТЕР";
        wcout << L"Текст: \"" << text5 << L"\"" << endl;
        wcout << L"Количество столбцов: " << 5 << endl;
        
        wstring encrypted5 = cipher5.encrypt(text5);
        wcout << L"Зашифровано: " << encrypted5 << endl;
        
        encrypted5[0] = L'1'; // Портим текст
        wcout << L"Испорченный текст: " << encrypted5 << endl;
        
        wstring decrypted5 = cipher5.decrypt(encrypted5);
        wcout << L"Расшифровано: " << decrypted5 << endl;
        
        wcout << L"УСПЕХ" << endl;
    } catch (const route_cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
    }
    wcout << L"-------------------" << endl;

    // Тест 6: Строчные буквы в тексте
    wcout << L"Тест 6: Строчные буквы в тексте" << endl;
    try {
        routeCipher cipher6(4);
        wstring text6 = L"Программирование";
        wcout << L"Текст: \"" << text6 << L"\"" << endl;
        wcout << L"Количество столбцов: " << 4 << endl;
        
        wstring encrypted6 = cipher6.encrypt(text6);
        wcout << L"Зашифровано: " << encrypted6 << endl;
        
        wstring decrypted6 = cipher6.decrypt(encrypted6);
        wcout << L"Расшифровано: " << decrypted6 << endl;
        
        wcout << L"УСПЕХ" << endl;
    } catch (const route_cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
    }
    wcout << L"-------------------" << endl;
}

int main()
{
    // Настройка локали
    locale::global(locale("ru_RU.utf8"));
    wcout.imbue(locale());
    wcerr.imbue(locale());
    
    wcout << L"=========================================" << endl;
    wcout << L"ТЕСТИРОВАНИЕ МЕТОДА МАРШРУТНОЙ ПЕРЕСТАНОВКИ" << endl;
    wcout << L"=========================================" << endl << endl;
    
    testRouteCipher();
    
    wcout << endl << L"=========================================" << endl;
    wcout << L"ИНТЕРАКТИВНЫЙ РЕЖИМ" << endl;
    wcout << L"=========================================" << endl;
    
    try {
        int columns;
        int mode;
        wstring text;

        wcout << L"Введите кол-во столбцов: ";
        wcin >> columns;
        wcin.ignore();

        wcout << L"Введите текст: ";
        getline(wcin, text);

        wcout << L"Выберите режим (1 - шифровать, 2 - расшифровать): ";
        wcin >> mode;

        routeCipher cipher(columns);

        if (mode == 1) {
            wcout << endl << L"Результат шифрования:" << endl;
            wcout << L"Текст: \"" << text << L"\"" << endl;
            wcout << L"Количество столбцов: " << columns << endl;
            
            wstring encrypted = cipher.encrypt(text);
            wcout << L"Зашифрованный текст: " << encrypted << endl;
        } else if (mode == 2) {
            wcout << endl << L"Результат расшифрования:" << endl;
            wcout << L"Текст: \"" << text << L"\"" << endl;
            wcout << L"Количество столбцов: " << columns << endl;
            
            wstring decrypted = cipher.decrypt(text);
            wcout << L"Расшифрованный текст: " << decrypted << endl;
        } else {
            wcout << L"Неверный режим" << endl;
        }
        
    } catch (const route_cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
    } catch (const exception& e) {
        wcerr << L"Неизвестная ошибка: " << e.what() << endl;
    }

    return 0;
}