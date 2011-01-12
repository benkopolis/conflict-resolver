#include "tmxfile.h"
#include <QXmlSchema>
#include "tmsaver.h"

TMXFile::TMXFile(QObject *parent) :
    GlossaryFile(parent)
{
}


Error TMXFile::processWithTabs(QFile & file)
{
    Error err;
    err.addAttribute("file_name", file.fileName());
    _doc.setContent(&file);
    QDomElement root = _doc.documentElement();
    if(QString::compare(root.tagName(), "tmx", Qt::CaseInsensitive) != 0)
    {
	err.setErrorMessage("Glowny tag nie nazywa sie tmx.");
	err.addAttribute("root_tag_name", root.tagName());
	return err;
    }
    if(root.hasChildNodes() == false)
    {
	err.setErrorMessage("Glowny tag tmx nie posiada tagow podrzednych.");
	return err;
    }
    if(root.elementsByTagName("header").size() != 1)
    {
	err.setErrorMessage("Glowny tag nie tmx nie posiada tagu podrzednego header lub posiada ich za duzo.");
	err.addAttribute("header_count", root.elementsByTagName("header").size());
	return err;
    }
    if(root.elementsByTagName("body").size() != 1)
    {
	err.setErrorMessage("Glowny tag nie tmx nie posiada tagu podrzednego body lub posiada ich za duzo.");
	err.addAttribute("body_count", root.elementsByTagName("body").size());
	return err;
    }
    if((err = this->validateDocument(root.attribute("version", "1.4"), file)) == false)
	return err;
    _header = root.firstChildElement("header");
    _body = root.firstChildElement("body");
    if((err = processHeader(file)) == false)
	return err;
    if((err = processBody(_body, file)) == false)
	return err;
    return Error();
}

Error TMXFile::validateDocument(QString version, QFile &file)
{
    QXmlSchema schema;
    QFile f;
    Error err;
    err.addAttribute("file_name", file.fileName());
    err.addAttribute("tmx14", ":/dtd/tmx14.xsd");
    err.addAttribute("tmx13", ":/dtd/tmx13.xsd");
    err.addAttribute("tmx12", ":/dtd/tmx12.xsd");
    err.addAttribute("tmx11", ":/dtd/tmx11.xsd");
    if(QString::compare(version, "1.4") == 0)
	f.setFileName(":/dtd/tmx14.xsd");
    else if (QString::compare(version, "1.3") == 0)
	f.setFileName(":/dtd/tmx13.xsd");
    else if (QString::compare(version, "1.2") == 0)
	f.setFileName(":/dtd/tmx12.xsd");
    else if (QString::compare(version, "1.1") == 0)
	f.setFileName(":/dtd/tmx11.xsd");
    else
    {
	err.setErrorMessage("Niepoprawna wersja dokumentu tmx!");
	return err;
    }
    err.addAttribute("tmx_name", f.fileName());
    if(f.open(QIODevice::ReadOnly) == false)
    {
	err.setErrorMessage("Nie udalo sie otworzyc zasobu z definicja schematu tmx.");
	return err;
    }
    if(schema.load(&f ,QUrl::fromLocalFile(f.fileName())) == false)
    {
	err.setErrorMessage("Nie udalo sie wczytac schematu - niepoprawny schemat tmx.");
	return err;
    }
    QXmlSchemaValidator validator(schema);
    if(validator.validate(QUrl::fromLocalFile(file.fileName())) == false)
    {
	err.setErrorMessage("Niepoprawny dokument tmx - nie przeszedl walidacji za pomoca schematu.");
	return err;
    }
    return Error();
}

TMHeader TMXFile::header() const
{
    return _tmxHeader;
}

Error TMXFile::processHeader(QFile &file)
{
    Error err;
    err.addAttribute("file_name", file.fileName());
    if(_header == QDomElement())
    {
	err.setErrorMessage("Niepoprawny naglowek - nie zostal wczytany.");
	return err;
    }
    QString dt = _header.attribute("creationdate");
    QRegExp dtrex("^[0-9]{8,8}T[0-9]{6,6}Z$");
    if(dt.contains(dtrex) == false)
    {
	err.setErrorMessage("Niepoprawna data w naglowku.");
	return err;
    }
    dt.remove(QRegExp("[A-Z]"));
    QDate date;
    QTime time;
    if(this->isDateTime(dt, &date, &time) == false);
    {
	err.setErrorMessage("Niepoprawna data w naglowku.");
	return err;
    }
    QString hh("%");
    hh.append(dt);
    hh.append(QChar('\t'));

    return _tmxHeader.readHeader(hh);
}

Error TMXFile::processBody(QDomElement body, QFile &file)
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
	if(this->_langs.contains(tmxr->targetCode()) == false)
	    this->_langs.insert(tmxr->targetCode(), new QMultiHash<FuzzyStrings, ContentRecord* >());
        date = tmp.attribute("creationdate");
        date.remove(QRegExp("[A-Z]"));
        if(isDateTime(date, &d, &t) == false)
	{
	    delete tmxr;
	    continue;
	}
        tmxr->setDate(d); tmxr->setTime(t);
        tmxr->setAuthor(tmp.attribute("creationid"));
        tmxr->setAuthorId(tmp.attribute("usagecount"));
	_content->insert(tmxr->sourceF(), tmxr);
	this->_langs[tmxr->targetCode()]->insert(tmxr->sourceF(), tmxr);
	tmp = tmp.nextSiblingElement("tu");
    } while (tmp != body.lastChildElement("tu"));
    return Error();
}

/**
  *
  */
bool TMXFile::saveContent(QString file) {
    bool r=false;
    TMSaver tms;
    foreach(QString k, this->_langs.keys())
    {
	QString rf = file;
	rf.append(k);
	this->_rheader.setTargetCode(k);
	r = tms.saveContent(rf, this->_rheader, *(this->_langs.value(k)), this->_all);
	if(!r)
	    return false;
    }
    return r;
}

/**
  *
  */
bool TMXFile::saveReversedContent(QString file) {
    bool r=false;
    TMSaver tms;
    foreach(QString k, this->_langs.keys())
    {
	QString rf = file;
	rf.append(k);
	this->_rheader.setTargetCode(k);
	r = tms.saveReversedContent(rf, this->_rheader, *(this->_langs.value(k)), this->_all);
	if(!r)
	    return false;
    }
    return r;
}

