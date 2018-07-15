#ifndef DECODE_H
#define DECODE_H

#include <vector>

class Decode
{
public:

    Decode(const char* src, int length);

    const std::vector<char>& decodeData(unsigned char* key);

private:

    void process(unsigned char* key);

private:

    const char* _src = nullptr;

    int _length = 0;

    std::vector<char> _des;
};

#endif // DECODE_H
