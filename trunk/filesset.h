#ifndef FILESSET_H
#define FILESSET_H

#include <QAbstractListModel>
#include <QVariant>
#include <QStringList>

class FilesSet : public QAbstractListModel
{
Q_OBJECT
public:
    explicit FilesSet(QObject *parent = 0);

    virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    virtual int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    virtual void updateOnCommand(const QModelIndex& index);
    virtual QModelIndex deleteItem(const QModelIndex& index);
    inline virtual const QStringList& filesList() { return _filesList; };


signals:

public slots:

protected:

    QStringList _filesList;

};


#endif // FILESSET_H
