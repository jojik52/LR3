#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"

using namespace std;

struct KeyB_fixture
{
    modAlphaCipher *p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(KeyTest)
{
    TEST(ValidKey)
    {
        string input = "ААААА";
        string output = modAlphaCipher("БВГ").encrypt(input);
        CHECK_EQUAL("БВГБВ", output);
    }
    TEST(LongKey)
    {
        string input = "ААААА";
        string output = modAlphaCipher("БВГДЕЖЗИК").encrypt(input);
        CHECK_EQUAL("БВГДЕ", output);
    }
    TEST(LowCaseKey)
    {
        string input = "ААААА";
        try {
            string output = modAlphaCipher("бвг").encrypt(input);
            CHECK_EQUAL("БВГБВ", output);
        } catch (const CipherError& e) {
            CHECK(false);
        }
    }
    TEST(DigitsInKey)
    {
        CHECK_THROW(modAlphaCipher cp("Б1"), CipherError);
    }
    TEST(PunctuationInKey)
    {
        CHECK_THROW(modAlphaCipher cp("Б,В"), CipherError);
    }
    TEST(WhitespaceInKey)
    {
        CHECK_THROW(modAlphaCipher cp("Б В"), CipherError);
    }
    TEST(EmptyKey)
    {
        CHECK_THROW(modAlphaCipher cp(""), CipherError);
    }
    TEST(WeakKey)
    {   
        CHECK_THROW(modAlphaCipher cp("ААА"), CipherError);
    }
}

SUITE(EncryptTest){
    TEST_FIXTURE(KeyB_fixture, UpCaseString){
        string input = "СКОРОБУДЕТНОВЫЙГОД";
        string output = p->encrypt(input);
        CHECK_EQUAL("ТЛПСПВФЕЁУОПГЬКДПЕ", output);
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString)
    {
        string input = "скоро будет новый год";
        string output = p->encrypt(input);
        CHECK_EQUAL("ТЛПСПВФЕЁУОПГЬКДПЕ", output);
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitespaceAndPunctuation)
    {
        string input = "СКОРО БУДЕТ НОВЫЙ ГОД!!!";
        CHECK_THROW(p->encrypt(input), CipherError);
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers)
    {
        string input = "С Новым 2025 годом";
        CHECK_THROW(p->encrypt(input), CipherError);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString)
    {
        CHECK_THROW(p->encrypt(""), CipherError);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString)
    {
        CHECK_THROW(p->encrypt("1234+8765=9999"), CipherError);
    }
    TEST(MaxShiftKey)
    {
        string input = "СКОРОБУДЕТНОВЫЙГОД";
        string output = modAlphaCipher("Я").encrypt(input);
        CHECK_EQUAL("РЙНПНАТГДСМНБЪИВНГ", output); 
    }
}

SUITE(DecryptText){
    TEST_FIXTURE(KeyB_fixture, UpCaseString){
        string input = "ТЛПСПВФЕЁУОПГЬКДПЕ";
        string output = p->decrypt(input);
        CHECK_EQUAL("СКОРОБУДЕТНОВЫЙГОД", output);
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString)
    {
        CHECK_THROW(p->decrypt("тлпспвфеёуопгькдпе"), CipherError);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString)
    {
        CHECK_THROW(p->decrypt("ТЛПСП ГВЖЕЦ ОНДПЗ ЙГУТ"), CipherError);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString)
    {
        CHECK_THROW(p->decrypt("ТЛПСПГВЖЕЦОНДПЗЙГУТ2025"), CipherError);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString)
    {
        CHECK_THROW(p->decrypt("ТЛПСП,ГВЖЕЦ"), CipherError);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString)
    {
        CHECK_THROW(p->decrypt(""), CipherError);
    }
    TEST(MaxShiftKey)
    {
        string input = "РЙНПНАТГДСМНБЪИВНГ";
        string output = modAlphaCipher("Я").decrypt(input);
        CHECK_EQUAL("СКОРОБУДЕТНОВЫЙГОД", output);
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
