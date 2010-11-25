#include "filesset.h"

FilesSet::FilesSet(QObject *parent) :
    QAbstractListModel(parent)
{
}

int FilesSet::rowCount(const QModelIndex &parent) const {
    return _filesList.size();
}

QVariant FilesSet::data(const QModelIndex & index, int role) const {
    if(_filesList.size() > index.row())
        return QVariant(_filesList.at(index.row()));
    else
        return QVariant("NULL");
}

bool FilesSet::setData(const QModelIndex & index, const QVariant & value, int role) {
    QStringList::iterator ii =_filesList.insert(_filesList.begin(), qvariant_cast<QString>(value));
    bool suc(ii != _filesList.end());
    if(suc)
	emit dataChanged(this->index(0, 0, QModelIndex()), this->index(_filesList.size(), 0, QModelIndex()));
    return suc;
}

void FilesSet::updateOnCommand(const QModelIndex& index) {
    if(index != QModelIndex())
	emit dataChanged(index, index);
}

QModelIndex FilesSet::deleteItem(const QModelIndex& index) {
    QString d = qvariant_cast<QString>(index.data());
    QStringList::iterator ret;
    unsigned counter = 0;
    for(QStringList::iterator ii = _filesList.begin(); ii != _filesList.end(); ++ii) {
	if(*ii == d) {
	    ret = _filesList.erase(ii);
	    break;
	}
	counter++;
    }
    emit dataChanged(index, index);
    if(ret == _filesList.end())
	return QModelIndex();
    else
	return this->index(counter, 0);
}
