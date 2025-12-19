#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <algorithm>
#include <cwctype>

std::locale loc("ru_RU.UTF-8");

// Конструктор с валидацией ключа
modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    // Инициализация алфавита
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    
    // Валидация и установка ключа
    key = convert(getValidKey(skey));
}

// Валидация ключа
std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty key");
    
    std::wstring tmp(s);
    for (auto& c : tmp) {
        if (!isalpha(c, loc)) {
            // Преобразуем wstring в string для сообщения об ошибке
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            throw cipher_error("Invalid key character");
        }
        if (islower(c, loc)) {
            c = toupper(c, loc);
        }
    }
    return tmp;
}

// Валидация открытого текста
std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s)
{
    std::wstring tmp;
    for (auto c : s) {
        if (isalpha(c, loc)) {
            if (islower(c, loc))
                tmp.push_back(toupper(c, loc));
            else
                tmp.push_back(c);
        }
        // Игнорируем пробелы и другие символы
    }
    
    if (tmp.empty())
        throw cipher_error("Empty open text after removing non-alphabetic characters");
    
    return tmp;
}

// Валидация зашифрованного текста
std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    
    for (auto c : s) {
        if (!isupper(c, loc)) {
            throw cipher_error("Invalid cipher text - must contain only uppercase Russian letters");
        }
    }
    return s;
}

// Шифрование
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work);
}

// Расшифрование
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work);
}

// Преобразование строки в вектор чисел
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (wchar_t c : s) {
        if (c == L' ') {
            continue;
        }
        if (alphaNum.find(c) != alphaNum.end()) {
            result.push_back(alphaNum[c]);
        } else {
            // В этом месте не должно быть невалидных символов
            result.push_back(0);
        }
    }
    return result;
}

// Преобразование вектора чисел в строку
std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (int i : v) {
        if (i >= 0 && i < (int)numAlpha.size()) {
            result += numAlpha[i];
        } else {
            result += L'?';
        }
    }
    return result;
}