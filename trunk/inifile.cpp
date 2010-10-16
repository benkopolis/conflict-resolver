#include "inifile.h"
#include <QFile>
#include <QTextStream>

IniFile* IniFile::_iniFile = 0;

IniFile::IniFile(QObject *parent) :
    QObject(parent),
    m_iniFileDir("base.ini")
{
}

void IniFile::readIniFile() {
    QFile file(m_iniFileDir);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream fstream(&file);
    QString temp;
    while(fstream.atEnd() == false) {
	fstream >> temp;
	if(temp.compare(QString("REGEXP"), Qt::CaseInsensitive) == 0) {
	    fstream >> m_regex;
	} else if(temp.compare(QString("LASTPATH"), Qt::CaseInsensitive)) {
	    fstream >> temp;
	    m_lastPath.clear();
	    while(temp.compare(QString("ENDLASTPATH"), Qt::CaseInsensitive) != 0) {
		m_lastPath = m_lastPath.append(temp);
		fstream >> temp;
	    }
	} /// TODO
    }

}

void IniFile::saveIniFile() {
    QFile file(m_iniFileDir);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream fstream(&file);
    fstream << "REGEXP " << m_regex << endl;
    fstream << "LASTPATH " << m_lastPath << " ENDLASTPATH" << endl;
    /// TODO
}
