#ifndef INIFILE_H
#define INIFILE_H

#include <QObject>
#include <QVariantList>

class IniFile : public QObject
{
Q_OBJECT
public:

    inline static IniFile* instance() { if(!_iniFile) _iniFile=new IniFile(); return _iniFile; }

    bool saveIniFile();
    bool readIniFile();


    QString m_iniFileDir;
    /// last used path
    QString m_lastPath;
    /// records set directory
    QString m_dir;
    /// attributes configuration - list contains dysjunctions of conjunctions lists
    QVariantList m_configuration;
    QString m_langugeCodesFile;
    QString m_translatorsFile;
    QString m_disciplinesFile;
    QString m_regex;
    unsigned m_fval;

    QMap<unsigned, unsigned> _report;

signals:

public slots:

    void onConflict(unsigned sim);

private:

    static IniFile* _iniFile;

    explicit IniFile(QObject *parent = 0);




};

#endif // INIFILE_H
