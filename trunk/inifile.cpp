#include "inifile.h"
#include <QFile>
#include <QTextStream>

IniFile* IniFile::_iniFile = 0;

IniFile::IniFile(QObject *parent) :
    QObject(parent),
    m_iniFileDir("base.ini")
{
    for(unsigned i =0; i < 101; ++i)
	_report.insert(i, 0);
}

bool IniFile::readIniFile() {
    QFile file(m_iniFileDir);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text) == false)
	return false;
    QTextStream fstream(&file);
    QString temp = fstream.readLine();
    QJson::Parser parser;
    bool ok = false;
    QVariantMap mm = parser.parse(temp.toLocal8Bit(), &ok).toMap();
    if(!ok)
        return false;
    QJson::QObjectHelper::qvariant2qobject(mm, this);
    file.close();
    return true;
}

bool IniFile::saveIniFile() {
    QFile file(m_iniFileDir);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream fstream(&file);
    QVariantMap mm = QJson::QObjectHelper::qobject2qvariant(this);
    QJson::Serializer srl;
    fstream << srl.serialize(mm) << endl;
    file.close();
    return true;
}

void IniFile::onConflict(unsigned sim)
{
    _report[sim]++;
}
