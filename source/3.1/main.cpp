#include <iostream>
#include <string>
#include "modAlphaCipher.h"

using namespace std;

void check(const string& text, const string& key, bool destructCipherText = false) {
    try {
        modAlphaCipher cipher(key);
        string cipherText = cipher.encrypt(text);

        if (destructCipherText) {
            cipherText += static_cast<char>(32); // Добавляем пробел, если destructCipherText == true
        }

        string decryptedText = cipher.decrypt(cipherText);
        cout << "Ключ = " << key << endl;
        cout << "Открытый текст: " << text << endl;
        cout << "Зашифрованный текст: " << cipherText << endl;
        cout << "Расшифрованный текст: " << decryptedText << endl;
    } catch (const CipherError &e) {
        cerr << "Ошибка: " << e.what() << endl;
    } catch (const std::exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

int main() {
    check("ЖОЖИК", "КЛЮЧ");
    cout << "испытание 1\n" << endl;
    check("ЖОЖИК", "Ключ");
    cout << "испытание 2\n" << endl;
    check("ЖОЖИК", "");
    cout << "испытание 3\n" << endl;
    check("ЖОЖИК", "Клю4ик");
    cout << "испытание 4\n" << endl;
    check("ЖО ЖИК", "КЛЮЧ");
    cout << "испытание 5\n" << endl;
    check("145", "КЛЮЧ");
    cout << "испытание 6\n" << endl;
    check("ЖОЖИК", "КЛЮЧ", true);
    cout << "испытание 7\n" << endl;

    return 0;
}
