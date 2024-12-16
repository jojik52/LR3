#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include <iostream>
#include <locale>

using namespace std;

struct KeyB_fixture
{
    ModCipher *p;
    KeyB_fixture()
    {
        p = new ModCipher(10);
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(KeyTest)
{
    TEST_FIXTURE(KeyB_fixture, StringLengthLessKey)
    {
        wstring open_text = L"Hello!!!";
        CHECK_THROW(p->encrypt(open_text), CipherError);
    }
    TEST(NegativeKey)
    {
        CHECK_THROW(ModCipher(-5), CipherError);
    }
}

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, ASCIISymbolsTest)
    {
        wstring open_text = L"Hello world!!! - Привет мир!!! #2025";
        wstring secret_text = p->encrypt(open_text);
        CHECK(secret_text == L"Hdв e!е#l!т2l! 0o м2 -и5w р oП! rр! lи! ");
    }
    TEST_FIXTURE(KeyB_fixture, EmptyText)
    {
        wstring open_text = L"";
        CHECK_THROW(p->encrypt(open_text), CipherError);
    }
    TEST_FIXTURE(KeyB_fixture, UnsupportedCharacters)
    {
        wstring open_text = L"Hello world!!! \x01\x02\x03 - Привет мир!!! #2025";
        CHECK_THROW(p->encrypt(open_text), CipherError);
    }
}

SUITE(DecryptTest)
{
    TEST_FIXTURE(KeyB_fixture, ASCIISymbolsTest)
    {
        wstring secret_text = L"Hdв e!е#l!т2l! 0o м2 -и5w р oП! rр! lи! ";
        wstring open_text = p->decrypt(secret_text);
        CHECK(open_text == L"Hello world!!! - Привет мир!!! #2025");
    }
    TEST_FIXTURE(KeyB_fixture, EmptyText)
    {
        wstring secret_text = L"";
        CHECK_THROW(p->decrypt(secret_text), CipherError);
    }
    TEST_FIXTURE(KeyB_fixture, UnsupportedCharacters)
    {
        wstring secret_text = L"Hdв e!е#l!т2l! \x01\x02\x03 м2 -и5w р oП! rр!";
        CHECK_THROW(p->decrypt(secret_text), CipherError);
    }
    
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    return UnitTest::RunAllTests();
}
