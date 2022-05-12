#include "configmanager.h"

QSettings *ConfigManager::m_settings = new QSettings("config/config.ini", QSettings::IniFormat);

QString ConfigManager::hostname()
{
    return m_settings->value("Configuration/server_ip", "localhost").toString();
}

int ConfigManager::remotePort()
{
    return m_settings->value("Configuration/remote_port", "80").toInt();
}

int ConfigManager::localPort()
{
    return m_settings->value("Configuration/local_port", "8080").toInt();
}

bool ConfigManager::showDebug()
{
    return m_settings->value("Configuration/show_debug", "false").toBool();
}
