#include "contentrecord.h"
#include <QRgb>
#include <QDebug>

ContentRecord::ContentRecord(QObject *parent) :
    QObject(parent),
    _metrics(QString("Courier New"))
{
    _status = None;
}

ContentRecord::ContentRecord(QString source , QString target , unsigned lineNumber , QObject * parent ):
    QObject(parent),
    _source(source),
    _target(target),
    _lineNumber(lineNumber),
    _metrics(QString("Courier New"))
{
    _status = None;
}

QString ContentRecord::toListString() const {
    QString ret;
    ret.append(this->_source);
    ret.append(QString(" | "));
    ret.append(this->_target);
    return ret;
}

QString ContentRecord::toRecordString() const {
    QString ret;
    ret = ret.append(this->_source);
    ret = ret.append(QChar('\t'));
    ret = ret.append(this->_target);
    if(_comment.length() > 0) {
	ret = ret.append(QChar('\t'));
	ret = ret.append(_comment);
    }
    return ret;
}

QString ContentRecord::toReversedRecordString() const {
    QString ret;
    ret = ret.append(this->_target);
    ret = ret.append(QChar('\t'));
    ret = ret.append(this->_source);
    if(_comment.length() > 0) {
	ret = ret.append(QChar('\t'));
	ret = ret.append(_comment);
    }
    return ret;
}

void ContentRecord::countDrawDate(const QFontMetrics& metrics, const QRect& size, int offsetFromTop) {
    if(size == _last)
	return;
    _last = size;
    _metrics = metrics;
    _sourceRects.clear();
    _targetRects.clear();
    _sourceStrings.clear();
    _targetStrings.clear();
    _bounding.setX(0); _bounding.setY(0); _bounding.setWidth(0); _bounding.setHeight(0);
    QRect f = _metrics.boundingRect(_source);
    int charWidth = f.width() / _source.length();
    int charsInLine = size.width() / charWidth;
    qDebug() << "w: " << size.width() << endl;
    QRect p;
    p.setY(offsetFromTop - f.height());
    p.setWidth(size.width());
    p.setHeight(f.height());
    makeLists(_source, p, f.height(), charsInLine, _sourceStrings, _sourceRects);
    p.setY(p.y() + f.height() * (_sourceStrings.size() - 1));
    makeLists(_target, p, f.height(), charsInLine, _targetStrings, _targetRects);
}

void ContentRecord::makeLists(QString tmp, QRect p, int lineH, int charsInLine,
			      QStringList& _splitted, QList<QRect>& _coloringRects) {
    int sourceLines=0;
    QRect r;
    while(!tmp.isEmpty()) {
	p.setY(p.y() + lineH);
	p.setHeight(lineH);
	++sourceLines;
	if(tmp.length() > charsInLine) {
	    _splitted.push_back(tmp.mid(0, charsInLine));
	    r = p;
	    qDebug() << "ML: " << "x " << p.x() << "y " << p.y() << "w " << p.width() << "h " << p.height()<< endl;
	    _coloringRects.push_back(r);
	} else {
	    _splitted.push_back(tmp);
	    p.setWidth(_metrics.boundingRect(tmp).width());
	    r = p;
	    qDebug() << "ML: " << "x " << p.x() << "y " << p.y() << "w " << p.width() << "h " << p.height()<< endl;
	    _coloringRects.push_back(r);
	    break;
	}
	tmp = tmp.mid(charsInLine);
    }
}

QList<QRect> ContentRecord::sourceRects() const {
    return _sourceRects;
}

QStringList ContentRecord::sourceStrings() const {
    return _sourceStrings;
}

QList<QRect> ContentRecord::targetRects() const {
    return _targetRects;
}

QStringList ContentRecord::targetStrings() const {
    return _targetStrings;
}

QRect ContentRecord::boundingRect() const {
    return _bounding;
}






