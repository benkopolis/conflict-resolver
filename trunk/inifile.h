#ifndef INIFILE_H
#define INIFILE_H

#include <QObject>
#include <QVariantList>
#include <serializer.h>
#include <parser.h>
#include <QVariant>
#include <qobjecthelper.h>
#include <QVariantMap>
#include "engine/fuzzyenginethread.h"

class IniFile : public QObject
{
Q_OBJECT

Q_PROPERTY(QString _iniFileDir READ iniFileDir WRITE setIniFileDir)
Q_PROPERTY(QString _lastPath READ lastPath WRITE setLastPath)
Q_PROPERTY(QString _regex READ regex WRITE setRegex)
Q_PROPERTY(unsigned _fval READ fval WRITE setFval)
Q_PROPERTY(unsigned _fbufferX READ fbufferX WRITE setFBufferX)
Q_PROPERTY(unsigned _fbufferY READ fbufferY WRITE setFBufferY)


public:

    inline static IniFile* instance() { if(!_iniFile) _iniFile=new IniFile(); return _iniFile; }

    bool saveIniFile();
    bool readIniFile();

    inline void setRegex(const QString& regex) { if(regex.isEmpty()) return; m_regex = regex; };
    inline void setLastPath(const QString& lastPath) { if(lastPath.isEmpty()) return; m_lastPath = lastPath; };
    inline void setIniFileDir(const QString& iniFileDir) { if(iniFileDir.isEmpty()) return; m_iniFileDir = iniFileDir; };
    inline void setFval(const unsigned fval) { m_fval = fval > 100 ? 75 : (fval < 75 ? 75 : fval); };
    inline QString iniFileDir() const { return m_iniFileDir; };
    inline QString lastPath()  const { return m_lastPath; };
    inline QString regex() const { return m_regex; };
    inline unsigned fval() const { return m_fval; };
    inline void setFBufferX(const unsigned buffX) { m_fbufferX = buffX; }
    inline unsigned fbufferX() const { return m_fbufferX; }
    inline void setFBufferY(const unsigned buffY) { m_fbufferY = buffY; }
    inline unsigned fbufferY() const { return m_fbufferY; }
    inline void setFuzzyEngine(FuzzyEngineThread* e) { _engine = e; }
    inline FuzzyEngineThread* fuzzyEngine() { return _engine; }

private:

    FuzzyEngineThread* _engine;

    QString m_iniFileDir;
    /// last used path
    QString m_lastPath;
    QString m_regex;
    unsigned m_fval;
    unsigned m_fbufferX;
    unsigned m_fbufferY;

    QMap<unsigned, unsigned> _report;

signals:

public slots:

    void onConflict(unsigned sim);

private:

    static IniFile* _iniFile;

    explicit IniFile(QObject *parent = 0);
};

#endif // INIFILE_H
