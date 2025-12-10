#include "modAlphaCipher.h"
#include <stdexcept>
using namespace std;

modAlphaCipher::modAlphaCipher(const wstring& skey)
{
    // Заполняем ассоциативный массив alphaNum
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    
    key = convert(skey);
}

wstring modAlphaCipher::encrypt(const wstring& open_text)
{
    vector<int> work = convert(open_text);
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

wstring modAlphaCipher::decrypt(const wstring& cipher_text)
{
    vector<int> work = convert(cipher_text);
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

vector<int> modAlphaCipher::convert(const wstring& s)
{
    vector<int> result;
    for (auto c : s) {
        if (alphaNum.find(c) == alphaNum.end()) {
            throw invalid_argument("Invalid character in text");
        }
        result.push_back(alphaNum[c]);
    }
    return result;
}

wstring modAlphaCipher::convert(const vector<int>& v)
{
    wstring result;
    for (auto i : v) {
        if (i < 0 || i >= static_cast<int>(numAlpha.size())) {
            throw out_of_range("Invalid character index");
        }
        result.push_back(numAlpha[i]);
    }
    return result;
}