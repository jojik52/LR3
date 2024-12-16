#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <iostream>
#include <sstream>

using namespace std;

class ModCipher
{
private:
    int key;
    wstring ABC = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                  L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                  L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  L"abcdefghijklmnopqrstuvwxyz"
                  L"0123456789 !?.,-#\n\r\t";

public:
    ModCipher() = delete;
    ModCipher(int key);
    wstring encrypt(wstring &open_text);
    wstring decrypt(wstring &secret_text);
    inline void validateText(wstring &text);
    inline void validateText(wstring &open_text, wstring &secret_text);
    inline void validateKey(int &key, wstring &text);
};

class CipherError : public invalid_argument
{
public:
    explicit CipherError(const string &what_arg) : invalid_argument(what_arg) {}
    explicit CipherError(const char *what_arg) : invalid_argument(what_arg) {}
};
