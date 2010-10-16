#ifndef FILESSETDELEGATE_H
#define FILESSETDELEGATE_H

#include <QStyledItemDelegate>
#include <QListView>

class FilesSetDelegate : public QStyledItemDelegate
{
Q_OBJECT
public:
    explicit FilesSetDelegate(QObject *parent = 0);

    virtual void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

signals:

public slots:

    inline void setSelected(const QModelIndex& selected) {_selected = selected; };
    inline void onVerticalOffset(int offset) { _vOffset = offset; };
    inline void onHorizontalOffset(int offset) { _hOffset = offset; };

protected:

    QModelIndex _selected;

    QListView* _view;
    QFontMetrics _fm;
    mutable int _vOffset;
    mutable int _hOffset;

    static QColor const _sourceColor;
    static QColor const _targetColor;
    static QColor const _selectionColor;

};

#endif // FILESSETDELEGATE_H
