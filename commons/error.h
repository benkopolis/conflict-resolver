#ifndef ERROR_H
#define ERROR_H

#include <QObject>
#include <QVariantMap>
#include <serializer.h>
#include <qobjecthelper.h>

class Error : public QObject
{
Q_OBJECT
Q_PROPERTY(QVariantMap error_attributes READ errorAttribs WRITE setErrorAttribs)
Q_PROPERTY(QString error_message READ errorMessage WRITE setErrorMessage)
public:
    explicit Error(QObject *parent = 0);

    inline void setErrorMessage(const QString& msg) { _errorMessage = msg; }
    inline void setErrorAttribs(const QVariantMap& map) { _errorAttribs = map; }
    inline QString errorMessage() const { return _errorMessage; }
    inline QVariantMap errorAttribs() const { return _errorAttribs; }

signals:

public slots:

    void addAttribute(const QString& name, const QVariant& value);

protected:

    QString _errorMessage;
    QVariantMap _errorAttribs;

};


#endif // ERROR_H
