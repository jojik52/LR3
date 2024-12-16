#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

class modAlphaCipher
{
private:
    const wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; // Алфавит
    map<wchar_t, int> alphaNum;                                    // Соответствие букв и индексов
    vector<int> key;                                               // Ключ шифрования

    vector<int> convert(const string &s);       // Преобразование строки в вектор индексов
    string convert(const vector<int> &v);       // Преобразование вектора индексов в строку
    string getValidKey(const string &s);        // Проверка и получение валидного ключа
    string getValidOpenText(const string &s);   // Проверка и получение валидного открытого текста
    string getValidCipherText(const string &s); // Проверка и получение валидного зашифрованного текста

public:
    modAlphaCipher() = delete;                   // Удаляем конструктор по умолчанию
    explicit modAlphaCipher(const string &skey); // Конструктор с ключом
    string encrypt(const string &open_text);     // Шифрование текста
    string decrypt(const string &cipher_text);   // Дешифрование текста
};

class CipherError : public invalid_argument
{
public:
    explicit CipherError(const string &what_arg) : invalid_argument(what_arg) {}
    explicit CipherError(const char *what_arg) : invalid_argument(what_arg) {}
};
