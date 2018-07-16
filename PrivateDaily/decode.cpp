#include "Decode.h"
#include "aes.h"
#include <cstring>

Decode::Decode(const QByteArray& src)
    :_src{src}
{

}

QByteArray& Decode::decodeData(unsigned char* key)
{
    process(key);
    return _des;
}

void Decode::process(unsigned char* key)
{
    _des.clear();
    Aes aes(key);
    char* result = _src.data();
    aes.InvCipher(result,_src.count());
    _des.resize(_src.count());
    for(int i = 0;i < _src.count();++i)
    {
        _des[i] = result[i];
    }
}
