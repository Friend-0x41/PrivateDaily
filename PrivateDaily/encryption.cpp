#include "encryption.h"
#include "aes.h"
#include <cstring>

Encryption::Encryption(const QByteArray& src)
    :_src{src}
{

}

QByteArray& Encryption::desData(unsigned char* key)
{
    process(key);
    return _des;
}

void Encryption::process(unsigned char* key)
{
    _des.clear();
    int d = _src.count() / 16 + 1;
    int length = d * 16;
    char* src = new char[length];
    memset(src,0,length);
    memcpy(src,_src.data(),length);
    Aes aes(key);
    void* result = aes.Cipher(src,length);
    _des.resize(length);
    for(int i = 0;i < length;++i)
    {
        _des[i] = ((char*)result)[i];
    }
    delete src;
}
