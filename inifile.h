#ifndef INIFILE_H
#define INIFILE_H

#include <QObject>
#include <QVariantList>
#include <serializer.h>
#include <parser.h>
#include <QVariant>
#include <qobjecthelper.h>
#include <QVariantMap>

class IniFile : public QObject
{
Q_OBJECT

Q_PROPERTY(QString _iniFileDir READ iniFileDir WRITE setIniFileDir)
Q_PROPERTY(QString _lastPath READ lastPath WRITE setLastPath)
Q_PROPERTY(QString _regex READ regex WRITE setRegex)
Q_PROPERTY(unsigned _fval READ fval WRITE setFval)

public:

    inline static IniFile* instance() { if(!_iniFile) _iniFile=new IniFile(); return _iniFile; }

    bool saveIniFile();
    bool readIniFile();

    inline void setRegex(const QString& regex) { if(regex.isEmpty()) return; m_regex = regex; };
    inline void setLastPath(const QString& lastPath) { if(lastPath.isEmpty()) return; m_lastPath = lastPath; };
    inline void setIniFileDir(const QString& iniFileDir) { if(iniFileDir.isEmpty()) return; m_iniFileDir = iniFileDir; };
    inline void setFval(const unsigned fval) { m_fval = fval > 100 ? 75 : (fval < 75 ? 75 : fval); };
    inline QString iniFileDir() { return m_iniFileDir; };
    inline QString lastPath() { return m_lastPath; };
    inline QString regex() { return m_regex; };
    inline unsigned fval() { return m_fval; };

private:

    QString m_iniFileDir;
    /// last used path
    QString m_lastPath;
    QString m_regex;
    unsigned m_fval;
    unsigned m_fbufferLen;

    QMap<unsigned, unsigned> _report;

signals:

public slots:

    void onConflict(unsigned sim);

private:

    static IniFile* _iniFile;

    explicit IniFile(QObject *parent = 0);
};

#endif // INIFILE_H
