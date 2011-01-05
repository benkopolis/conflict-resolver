#include "tmxfile.h"

TMXFile::TMXFile(QObject *parent) :
    GlossaryFile(parent)
{
}


bool TMXFile::processWithTabs(QFile & file)
{
    QDomElement root = _doc.documentElement();
    if(root.tagName() != "tmx")
	return false;
    if(root.hasChildNodes() == false)
	return false;
    if(root.elementsByTagName("header").size() != 1)
	return false;
    if(root.elementsByTagName("body").size() != 1)
	return false;
    QString _version = root.attribute("version", "1.4");
    if(this->validateDocument(root.attribute("version", "1.4")))
    _header = root.firstChildElement("header");
    _body = root.firstChildElement("body");
    if(processHeader() == false)
	return false;
    if(processBody(_body) == false)
	return false;
    return true;
}

bool TMXFile::validateDocument(QString version)
{
    if(QString::compare(version, "1.4") == 0)
    {

    }
    else if (QString::compare(version, "1.3") == 0)
    {

    }
    else if (QString::compare(version, "1.2") == 0)
    {

    }
    else if (QString::compare(version, "1.1") == 0)
    {
    }
    else
        return false;
    return true;
}

TMHeader TMXFile::header() const
{
    return _tmxHeader;
}

bool TMXFile::processHeader()
{
    if(_header == QDomElement())
	return false;
    QString dt = _header.attribute("creationdate");
    QRegExp dtrex("^[0-9]{8,8}T[0-9]{6,6}Z$");
    if(dt.contains(dtrex) == false)
	return false;
    dt.remove(QRegExp("[A-Z]"));
    QDate date;
    QTime time;
    if(this->isDateTime(dt, &date, &time) == false);
	return false;
    QString hh("%");
    hh.append(dt);
    hh.append(QChar('\t'));

    return _tmxHeader.readHeader(hh);
}

bool TMXFile::processBody(QDomElement body)
{
    QDomElement tmp = body.firstChildElement("tu");
    QString date;
    QDate d;
    QTime t;
    do {
	TMXRecord* tmxr = new TMXRecord();
	tmxr->setSource(tmp.firstChildElement().firstChildElement().text());
	tmxr->setTarget(tmp.lastChildElement().firstChildElement().text());
	tmxr->setSourceCode(tmp.firstChildElement().attribute("xml:lang"));
	tmxr->setTargetCode(tmp.lastChildElement().attribute("xml:lang"));
        if(this->_langs.contains(tmxr->targetCode()))
            this->_langs[tmxr->targetCode()] += 1;
        else
            this->_langs.insert(tmxr->targetCode(), 1);
        date = tmp.attribute("creationdate");
        date.remove(QRegExp("[A-Z]"));
        if(isDateTime(date, &d, &t) == false)
            return false;
        tmxr->setDate(d); tmxr->setTime(t);
        tmxr->setAuthor(tmp.attribute("creationid"));
        tmxr->setAuthorId(tmp.attribute("usagecount"));
	tmp = tmp.nextSiblingElement("tu");
    } while (tmp != body.lastChildElement("tu"));
    return true;
}

