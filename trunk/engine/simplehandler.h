#ifndef SIMPLEHANDLER_H
#define SIMPLEHANDLER_H

#include <QAbstractMessageHandler>

class SimpleHandler : public QAbstractMessageHandler
{
Q_OBJECT
public:
    explicit SimpleHandler(QObject *parent = 0);

    void message (QtMsgType type, const QString & description, const QUrl & identifier = QUrl(), const QSourceLocation & sourceLocation = QSourceLocation());

signals:

public slots:

};

#endif // SIMPLEHANDLER_H
