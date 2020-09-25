#pragma once

#include <QQueue>

template <class T>
class QQQueue : public QQueue<T>
{
public:
    QQQueue(const int maxCount=0);
    void enqueue(const T &t)
    {
        QQueue<T>::enqueue(t);
        if (cmMaxCount)
            while (size() > cmMaxCount)
                (void)QQueue<T>::dequeue();
    }

private:
    const int cmMaxCount;
};

