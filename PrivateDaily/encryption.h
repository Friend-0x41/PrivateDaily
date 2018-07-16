#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QByteArray>

class Encryption
{
public:

    Encryption(const QByteArray& src);

    QByteArray& desData(unsigned char* key);

private :

    void process(unsigned char* key);

private:

    QByteArray _src = nullptr;

    QByteArray _des;
};

#endif // ENCRYPTION_H
