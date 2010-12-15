#ifndef FUZZYENGINETHREAD_H
#define FUZZYENGINETHREAD_H

#include <QThread>

class FuzzyEngineThread : public QThread
{
Q_OBJECT
public:
    explicit FuzzyEngineThread(QObject *parent = 0);
    explicit FuzzyEngineThread(uint x, uint y, QObject *parent = 0);

    inline uint getX() const { return _x; }
    inline uint getY() const { return _y; }

signals:

    void fuzzyResult(uint simval);
    void requestBuffSize();

public slots:

    void countFuzzy(QString one, QString two);
    void buffSize(uint x, uint y);
    void resetBuff(uint x, uint y, uint newX, uint newY);

protected:

    virtual void run();
    void initBuff();

   unsigned **arr;
   uint _x;
   uint _y;

};

#endif // FUZZYENGINETHREAD_H
