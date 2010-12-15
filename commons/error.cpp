#include "error.h"

Error::Error(QObject *parent) :
    QObject(parent)
{
}

void Error::addAttribute(const QString& name, const QVariant& value)
{
    _errorAttribs.insert(name, value);
}
