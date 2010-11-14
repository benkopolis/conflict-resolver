#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <QObject>

class ErrorManager : public QObject
{
Q_OBJECT
public:
    explicit ErrorManager(QObject *parent = 0);

signals:

public slots:

};

#endif // ERRORMANAGER_H
