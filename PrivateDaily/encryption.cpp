#include "encryption.h"
#include "aes.h"
#include <cstring>

Encryption::Encryption(const char* src, int length)
    :_src{src},_length{length}
{

}

const std::vector<char>& Encryption::desData(unsigned char* key)
{
    process(key);
    return _des;
}

void Encryption::process(unsigned char* key)
{
    _des.clear();
    int d = _length / 16 + 1;
    int length = d * 16;
    char* src = new char[length];
    memset(src,0,length);
    memcpy(src,_src,_length);
    Aes aes(key);
    void* result = aes.Cipher(src,length);
    for(int i = 0;i < length;++i)
    {
        _des.push_back(((char*)result)[i]);
    }
    delete src;
}
