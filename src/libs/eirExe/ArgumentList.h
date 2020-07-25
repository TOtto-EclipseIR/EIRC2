#pragma once

#include <QList>
#include <QString>


class ArgumentList
{
public:
    class Item
    {
    public:
        typedef QList<Item> List;

    public:
        Item(const QString &s) ;
        void set(const QString &s);
        QString toString() const;
        QString operator ()() const;

    private:
        QString mString;
    };

public:
    ArgumentList();
    void enqueue(const Item &item);
    Item dequeue();
    Item peek() const;
    int size() const;
    bool isEmpty() const;
    bool notEmpty() const;

private:
    Item::List mList;
};

