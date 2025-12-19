#include <iostream>
#include <locale>
#include <codecvt>
#include "modAlphaCipher.h"

using namespace std;

void check_ru(const wstring& text, const wstring& key, bool testError = false)
{
    try {
        modAlphaCipher cipher(key);
        wstring encrypted = cipher.encrypt(text);
        
        if (testError) {
            // Портим зашифрованный текст для тестирования исключений
            if (!encrypted.empty())
                encrypted[0] = towlower(encrypted[0]);
        }
        
        wstring decrypted = cipher.decrypt(encrypted);

        wcout << L"Ключ: " << key << endl;
        wcout << L"Текст: " << text << endl;
        wcout << L"Зашифровано: " << encrypted << endl;
        wcout << L"Расшифровано: " << decrypted << endl;

        // Сравнение без пробелов и с учетом регистра
        wstring text_clean, decrypted_clean;
        for (wchar_t c : text) {
            if (c != L' ') {
                text_clean += towupper(c);
            }
        }
        for (wchar_t c : decrypted) {
            if (c != L' ') {
                decrypted_clean += c;
            }
        }
        
        if (text_clean == decrypted_clean)
            wcout << L"УСПЕХ" << endl;
        else
            wcout << L"ОШИБКА" << endl;
        wcout << L"-------------------" << endl;
        
    } catch (const cipher_error& e) {
        wcout << L"Ключ: " << key << endl;
        wcout << L"Текст: " << text << endl;
        wcerr << L"Ошибка: " << e.what() << endl;
        wcout << L"-------------------" << endl;
    }
}

void check_ru_key_only(const wstring& key)
{
    wcout << L"Проверка ключа: " << key << endl;
    try {
        modAlphaCipher cipher(key);
        wcout << L"Ключ корректен" << endl;
    } catch (const cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
    }
    wcout << L"-------------------" << endl;
}

void check_ru_encrypt_only(const wstring& text, const wstring& key)
{
    wcout << L"Шифрование текста: " << text << L" с ключом: " << key << endl;
    try {
        modAlphaCipher cipher(key);
        wstring encrypted = cipher.encrypt(text);
        wcout << L"Зашифровано: " << encrypted << endl;
    } catch (const cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
    }
    wcout << L"-------------------" << endl;
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));
    std::wcerr.imbue(std::locale("ru_RU.UTF-8"));

    // Тесты с корректными данными
    wcout << L"=== ТЕСТЫ С КОРРЕКТНЫМИ ДАННЫМИ ===" << endl << endl;
    check_ru(L"ПОРКА", L"ЖАВОРОНОК");
    check_ru(L"ХАЙПОВЫЙ", L"КИБИТКА");
    check_ru(L"ПОСТ", L"Ю");
    check_ru(L"ПРИВЕТ МАМА", L"СКОМОРОХ");
    check_ru(L"Я КРУТОЙ ПАРНИША С СЕЛА", L"ШКИБИДИ");
    
    // Тесты с ошибками
    wcout << L"\n=== ТЕСТЫ С ОШИБКАМИ ===" << endl << endl;
    
    // Тест 1: Пустой ключ (исключение при создании объекта)
    wcout << L"1. Тест с пустым ключом:" << endl;
    check_ru(L"БАБАЙКА", L"");
    
    // Тест 2: Ключ с недопустимыми символами
    wcout << L"2. Тест с ключом, содержащим цифры:" << endl;
    check_ru(L"ПОРОСЯТА", L"КЛЮЧ123");
    
    // Тест 3: Пустой открытый текст (после удаления не-букв)
    wcout << L"3. Тест с пустым текстом:" << endl;
    check_ru(L"", L"КЛЮЧ");
    
    // Тест 4: Испорченный зашифрованный текст
    wcout << L"4. Тест с испорченным зашифрованным текстом:" << endl;
    check_ru(L"ПРИВЕТ", L"КЛЮЧИК", true);
    
    // Тест 5: Строчные буквы в тексте (должны корректно обрабатываться)
    wcout << L"5. Тест со строчными буквами в тексте:" << endl;
    check_ru(L"Привет мир", L"ТЕСТ");
    
    // Дополнительные тесты
    wcout << L"\n=== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ===" << endl << endl;
    
    // Тест с ключом из строчных букв (должен преобразовываться)
    wcout << L"6. Тест с ключом из строчных букв:" << endl;
    check_ru(L"ТЕСТ", L"ключ");
    
    // Тест с текстом, содержащим пробелы и знаки препинания
    wcout << L"7. Тест с текстом, содержащим пробелы и знаки препинания:" << endl;
    check_ru(L"Привет, мир! Как дела?", L"ПАРОЛЬ");
    
    // Тест с очень длинным ключом
    wcout << L"8. Тест с очень длинным ключом:" << endl;
    check_ru(L"КРАТКИЙТЕКСТ", L"ОЧЕНЬДЛИННЫЙКЛЮЧДЛЯПРОВЕРКИРАБОТЫАЛГОРИТМА");
    
    // Тест с однобуквенным текстом
    wcout << L"9. Тест с однобуквенным текстом:" << endl;
    check_ru(L"А", L"Б");
    
    return 0;
}