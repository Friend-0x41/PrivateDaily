#ifndef DECODE_H
#define DECODE_H

#include <QByteArray>

class Decode
{
public:

    Decode(const QByteArray& src);

    QByteArray& decodeData(unsigned char* key);

private:

    void process(unsigned char* key);

private:

    QByteArray _src;

    QByteArray _des;
};

#endif // DECODE_H
