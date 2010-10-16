#include <QPainter>
#include <QScrollBar>
#include "contentdelegate.h"
#include "conflictresolverwindow.h"


ContentDelegate::ContentDelegate(QObject *parent) :
    FilesSetDelegate(parent),
    _font(QString("Courier New")),
    _fontMetrics(_font)
{
    _vOffset = 0;
    _hOffset = 0;
}

QSize ContentDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const {
    ConflictResolverWindow* _crw = qobject_cast<ConflictResolverWindow* >(this->parent());
    _fontMetrics =  _crw->fontMetrics();
    QString tmp = qvariant_cast<QString>(index.data());
    QRect temp = _fontMetrics.boundingRect(tmp);
    return QSize(temp.width() + tmp.length()*2 + _crw->conflictsView()->verticalScrollBar()->size().width(), temp.height());
}

void ContentDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
    ConflictResolverWindow* _crw = qobject_cast<ConflictResolverWindow* >(this->parent());
    QString tmp = qvariant_cast<QString>(index.data());
    _fontMetrics =  _crw->fontMetrics();
    QRect temp = _fontMetrics.boundingRect(tmp);
    _vOffset = _crw->conflictsView()->verticalScrollBar()->value();
    _hOffset = _crw->conflictsView()->horizontalScrollBar()->value();
    _font = _crw->font();
    painter->save();
    painter->setFont(_font);
    if(index.row()/2 == _selected.row()/2 && _selected != QModelIndex())
	painter->setBrush(QBrush(_selectionColor));
    else if(index.row()%2 == 0)
	painter->setBrush(QBrush(_sourceColor));
    else if(index.row()%2 == 1)
	painter->setBrush(QBrush(_targetColor));
    QRect pom;
    pom.setY(temp.y() + _fontMetrics.height()*index.row() - _vOffset + _crw->conflictsView()->horizontalScrollBar()->size().height());
    pom.setX(temp.x() - _hOffset);
    pom.setWidth(_fontMetrics.width(tmp) + _crw->conflictsView()->verticalScrollBar()->size().width() + tmp.length()*2);
    pom.setHeight(_fontMetrics.height() );
    painter->drawRect(pom);
    painter->setPen(QPen(QColor(0,0,0)));
    painter->drawText(pom, 0, tmp);
    painter->restore();
}
