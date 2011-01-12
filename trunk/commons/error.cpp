#include "error.h"

Error::Error(QObject *parent) :
    QObject(parent)
{
    _error = false;
}

Error::Error(const Error& another):
    QObject(another.parent())
{
    _error = another.isError();
    _errorMessage = another._errorMessage;
    foreach(QString k, another._errorAttribs.keys())
    {
	_errorAttribs.insert(k, another._errorAttribs.value(k));
    }
}

void Error::addAttribute(const QString& name, const QVariant& value)
{
    if(_errorAttribs.contains(name) == true)
	_errorAttribs[name] = value;
    else
	_errorAttribs.insert(name, value);
}

/**
  * Operator do zachowania kompatybilnosci wstecznej -
  * porownanie klasy error ktora przenosi blad ma zwracac taki sam
  * wynik jak porownanie rezultatu dzialania metody o wartosci false
  */
bool Error::operator == (const bool& another) const
{
    return _error != another;
}

Error& Error::operator = (const Error& another)
{
    if(this == &another)
	return *this;
    this->setParent(another.parent());
    _error = another.isError();
    _errorMessage = another._errorMessage;
    foreach(QString k, another._errorAttribs.keys())
    {
	_errorAttribs.insert(k, another._errorAttribs.value(k));
    }
    return *this;
}
