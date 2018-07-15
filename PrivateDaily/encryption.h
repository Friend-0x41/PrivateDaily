#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <vector>

class Encryption
{
public:

    Encryption(const char* src,int length);

    const std::vector<char>& desData(unsigned char* key);

private :

    void process(unsigned char* key);

private:

    const char* _src = nullptr;

    int _length = 0;

    std::vector<char> _des;
};

#endif // ENCRYPTION_H
