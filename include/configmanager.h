#include <QSettings>

class ConfigManager
{
  public:
    static QString hostname();

    static int localPort();

    static bool showDebug();

  private:
    static QSettings *m_settings;
};
