#include "inifile.h"
#include <QFile>
#include <QTextStream>

IniFile* IniFile::_iniFile = 0;

IniFile::IniFile(QObject *parent) :
    QObject(parent),
    m_iniFileDir("base.ini")
{
}

bool IniFile::readIniFile() {
    QFile file(m_iniFileDir);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text) == false)
	return false;
    QTextStream fstream(&file);
    QString temp;
    while(fstream.atEnd() == false) {
	fstream >> temp;
	if(temp.compare(QString("REGEXP"), Qt::CaseInsensitive) == 0)
		fstream >> m_regex;
	else if(temp.compare(QString("LASTPATH"), Qt::CaseInsensitive))
	{
	    fstream >> temp;
	    m_lastPath.clear();
	    while(temp.compare(QString("ENDLASTPATH"), Qt::CaseInsensitive) != 0 && fstream.atEnd() == false)
	    {
		m_lastPath = m_lastPath.append(temp);
		fstream >> temp;
	    }
	}
	else if(temp.compare("FVAL", Qt::CaseInsensitive))
	    fstream >> m_fval;
	/// TODO
    }
    return true;
}

bool IniFile::saveIniFile() {
    QFile file(m_iniFileDir);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream fstream(&file);
    fstream << "REGEXP " << m_regex << endl;
    fstream << "LASTPATH " << m_lastPath << " ENDLASTPATH" << endl;
    fstream << "FVAL " << m_fval << endl;
    /// TODO
}
