#include "config.h"
#include "decode.h"
#include "encryption.h"
#include <iostream>
#include <QFile>
#include <QByteArray>

Config::Config()
{

}
ConfigData Config::loadConfig(bool& b)
{
    QFile inputFile(_configFileName);
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        b = false;
        return ConfigData();
    }
    QByteArray bytes = inputFile.readAll();
    inputFile.close();
    Decode decode(bytes);
    char key[] = "1234567812345678";
    QByteArray& cv = decode.decodeData((unsigned char *)key);
    QStringList l = QString(cv).split(_splitChar);
    ConfigData configData;
    configData.currentIndex = l[0].toInt();
    for(int i = 1;i < l.count(); ++i)
    {
        configData.openedFile.append(l[i]);
    }
    b = true;
    return configData;
}

bool Config::SaveConfig(ConfigData configData)
{
    QString s = QString("%1").arg(configData.currentIndex);
    for(int i = 0;i < configData.openedFile.count();++i)
    {
        s += _splitChar + configData.openedFile[i];
    }
    QByteArray bytes(s.toStdString().c_str());
    Encryption e(bytes);
    char key[] = "1234567812345678";
    QByteArray& vc = e.desData((unsigned char *)key);
    QFile outputFile(_configFileName);
    if(!outputFile.open(QIODevice::WriteOnly))
    {
        return false;
    }
    outputFile.write(vc);
    outputFile.close();
    return true;
}
