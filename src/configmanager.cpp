#include "configmanager.h"

QSettings *ConfigManager::m_settings = new QSettings("config/config.ini", QSettings::IniFormat);

QString ConfigManager::hostname()
{
    return m_settings->value("Configuration/server_address").toString();
}

int ConfigManager::remotePort()
{
    return m_settings->value("Configuration/remote_port").toInt();
}

int ConfigManager::localPort()
{
    return m_settings->value("Configuration/local_port").toInt();
}

bool ConfigManager::showDebug()
{
    return m_settings->value("Configuration/show_debug").toBool();
}
