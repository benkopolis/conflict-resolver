#include <QPainter>
#include <QTextStream>
#include <QFontMetrics>
#include <QScrollBar>
#include <QDebug>
#include "mainwindow.h"
#include "contentmodel.h"
#include "filessetdelegate.h"

QColor const FilesSetDelegate::_sourceColor(138, 255, 138);
QColor const FilesSetDelegate::_targetColor(255, 150, 150);
QColor const FilesSetDelegate::_selectionColor(127, 127, 150);

FilesSetDelegate::FilesSetDelegate(QObject *parent) :
    QStyledItemDelegate(parent),
    _fm(QFont(QString("Courier New")))
{
    _view = 0;
    _vOffset = 0;
    _hOffset = 0;
}

void FilesSetDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
    QString d = qvariant_cast<QString>(index.data());
//    QTextStream out(stdout);
//    out << "Row number: " << index.row() << " of this: " << d << endl;
    painter->save();
    if(_selected == index){
	painter->setBrush(QBrush(_selectionColor));
	painter->drawRect(0, index.row()*15, 7*d.length(), 15);
    }
    MainWindow* mw = qobject_cast<MainWindow* >(this->parent());
    QListView* tmp = mw->files();
    _hOffset = tmp->horizontalScrollBar()->value();
    _vOffset = tmp->verticalScrollBar()->value();
    painter->setFont(QFont(QString("Courier New")));
    painter->drawText(0 - _hOffset, index.row()*15 - _vOffset, 7*d.length(), 15, Qt::TextWordWrap, d);
//	qDebug() << "ho: " << _hOffset << " vo: " << _vOffset << endl;
    painter->restore();
}

QSize FilesSetDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index ) const {
    QRect r = _fm.boundingRect(qvariant_cast<QString>(index.data()));
    return QSize(r.width(), r.height());
}
