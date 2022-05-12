#include <QSettings>

class ConfigManager
{
  public:
    static QString hostname();

    static int remotePort();

    static int localPort();

    static bool showDebug();

  private:
    static QSettings *m_settings;
};
