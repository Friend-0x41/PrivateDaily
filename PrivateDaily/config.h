#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QStringList>
#include "configdata.h"

class QListWidget;

class Config
{
public:
    Config();

    ConfigData loadConfig(bool& b);

    bool SaveConfig(ConfigData data);

private:
    const QString _configFileName = "./config.ee";
    const char _splitChar = '~';
};

#endif // CONFIG_H
