#include "Decode.h"
#include "aes.h"
#include <cstring>

Decode::Decode(const char* src, int length)
    :_src{src}, _length{length}
{

}

const std::vector<char>& Decode::decodeData(unsigned char* key)
{
    process(key);
    return _des;
}

void Decode::process(unsigned char* key)
{
    _des.clear();
    Aes aes(key);
    char* result = new char[_length];
    memcpy(result,_src,_length);
    aes.InvCipher(result,_length);
    for(int i = 0;i < _length;++i)
    {
        _des.push_back(result[i]);
    }
    delete result;
}
