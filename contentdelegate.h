#ifndef CONTENTDELEGATE_H
#define CONTENTDELEGATE_H

#include "filessetdelegate.h"


class ContentDelegate : public FilesSetDelegate
{
Q_OBJECT
public:
    explicit ContentDelegate(QObject *parent = 0);

    virtual void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

signals:

public slots:

private:
    mutable QFont _font;
    mutable QFontMetrics _fontMetrics;

};

#endif // CONTENTDELEGATE_H
