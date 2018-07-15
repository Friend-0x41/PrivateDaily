#include "config.h"
#include "decode.h"
#include "encryption.h"
#include <iostream>
#include <fstream>

Config::Config()
{

}
ConfigData Config::loadConfig(bool& b)
{
    std::ifstream is;
    is.open(_configFileName.toStdString(),std::ios_base::binary | std::ios_base::in);
    if(!is.is_open())
    {
        b = false;
        return ConfigData();
    }
    is.seekg(0,std::ios::end);
    int length = is.tellg();
    is.seekg(0,std::ios::beg);
    char* data = new char[length];
    is.read(data,length);
    is.close();
    Decode decode(data,length + 1);
    char key[] = "1234567812345678";
    const std::vector<char>& cv = decode.decodeData((unsigned char *)key);
    for(int i = 0;i < length;++i)
    {
        data[i] = cv[i];
    }
    data[length] = 0;
    QStringList l = QString(data).split(_splitChar);
    ConfigData configData;
    configData.currentIndex = l[0].toInt();
    for(int i = 1;i < l.count(); ++i)
    {
        configData.openedFile.append(l[i]);
    }
    b = true;
    delete data;
    return configData;
}

bool Config::SaveConfig(ConfigData configData)
{
    QString s = QString("%1").arg(configData.currentIndex);
    for(int i = 0;i < configData.openedFile.count();++i)
    {
        s += _splitChar + configData.openedFile[i];
    }
    int length = strlen(s.toStdString().c_str());
    Encryption e(s.toStdString().c_str(),length);
    char key[] = "1234567812345678";
    const std::vector<char>& vc = e.desData((unsigned char *)key);
    char* data = new char[vc.size()];
    for(int i = 0;i < vc.size();++i)
    {
        data[i] = vc[i];
    }
    std::ofstream os;
    os.open(_configFileName.toStdString(),std::ios_base::binary | std::ios_base::out);
    os.write(data,vc.size());
    //os.write(s.toStdString().c_str(),length);
    delete data;
    os.close();
}
