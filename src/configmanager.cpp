#include "configmanager.h"
#include <QDebug>

QSettings *ConfigManager::m_settings = new QSettings("config.ini", QSettings::IniFormat);

QString ConfigManager::hostname()
{
    QString l_hostname = m_settings->value("Configuration/server_ip", "localhost").toString();
    QString l_remote_port = m_settings->value("Configuration/remote_port", "80").toString();
    return QString("ws://%1:%2").arg(l_hostname, l_remote_port);
}

int ConfigManager::localPort()
{
    return m_settings->value("Configuration/local_port", "8080").toInt();
}

bool ConfigManager::showDebug()
{
    return m_settings->value("Configuration/show_debug", "false").toBool();
}
