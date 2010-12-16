#include "fuzzyenginethread.h"
#include <QTextStream>
#include <QRegExp>
#include <QStringList>

FuzzyEngineThread::FuzzyEngineThread(QObject *parent) :
    QThread(parent)
{
    arr = 0;
}

FuzzyEngineThread::FuzzyEngineThread(uint x, uint y, QObject *parent) :
    QThread(parent)
{
    arr = 0;
    this->buffSize(x, y);
}

unsigned FuzzyEngineThread::extractResult(QString one, QString two)
{
    QPair<QString, QString> p(one, two);
    if(this->_results.contains(p))
        return 0;
    unsigned r = this->_results[p];
//    this->_results.remove(p);
    return r;
}

void FuzzyEngineThread::countFuzzy(QString one, QString two)
{
    QPair<QString, QString> pbeg(one, two);
    if(this->_results.contains(pbeg))
    {
	emit fuzzyResult(this->_results[pbeg]);
	return;
    }
    if(arr == 0)
       this->initBuff();
    QTextStream given(&one);
    QTextStream inner(&two);
    unsigned gwCount, iwCount;
    QRegExp rexp(QString("\\s"));
    gwCount = one.count(rexp) + 1;
    iwCount = two.count(rexp) + 1;
    bool xyChanged = false;
    if(_x < gwCount)
        xyChanged = true;
    if(_y < iwCount)
        xyChanged = true;
    if(xyChanged)
        this->resetBuff(_x, _y, gwCount, iwCount);
    QStringList t=one.split(rexp), s=two.split(rexp);
    unsigned res = 0, cost = 0;
    for(unsigned i=1; i < iwCount; ++i)
    {
        for(unsigned g=1; g<gwCount; ++g)
        {
            if(s.at(i-1) == t.at(g-1))
                cost = 0;
            else
                cost = 1;
            if(arr[i-1][g] < arr[i][g-1] && arr[i-1][g]+1 < arr[i-1][g-1]+cost)
                arr[i][g] = arr[i-1][g] + 1;
            else if(arr[i][g-1] < arr[i-1][g] && arr[i][g-1]+1 < arr[i-1][g-1]+cost)
                arr[i][g] = arr[i][g-1]+1;
            else
                arr[i][g] = arr[i-1][g-1]+cost;
        }
    }
    res =  arr[iwCount-1][gwCount-1];
    float avg = iwCount + gwCount;
    float tmp;
    avg = avg / 2;
    tmp = (avg - res)/avg;
    res = tmp*100;
    emit fuzzyResult(res);
    QPair<QString, QString> p(one, two);
    this->_results.insert(p, res);
}

void FuzzyEngineThread::buffSize(uint x, uint y)
{
    _x = x;
    _y = y;
    arr = new unsigned* [x];
    for(int i =0; i<x; ++i)
    {
        arr[i] = new unsigned [y];
        for(int j=0; j<y; ++j)
        {
            arr[i][j] = 0;
        }
    }
    for(unsigned i=0; ; ++i) {
        if(i < x) {
            arr[i][0] = i;
        }
        if(i < y) {
            arr[0][i] = i;
        }
        if(i >= y && i >= x)
            break;
    }
}

void FuzzyEngineThread::resetBuff(uint x, uint y, uint newX, uint newY)
{
    for(int i =0; i<x; ++i)
        delete [] arr[i];
    delete [] arr;
    arr = 0;
    this->buffSize(newX, newY);
}

void FuzzyEngineThread::run()
{
    this->exec();
}

void FuzzyEngineThread::initBuff()
{
    emit requestBuffSize();
}
