#include "ArgumentList.h"

#include "ArgumentList.h"

ArgumentList::ArgumentList()
{

}

void ArgumentList::enqueue(const ArgumentList::Item &item)
{
    mList.append(item);
}

ArgumentList::Item ArgumentList::dequeue()
{
    return mList.takeFirst();
}

ArgumentList::Item ArgumentList::peek() const
{
    return mList.first();
}

int ArgumentList::size() const
{
    return mList.size();
}

bool ArgumentList::isEmpty() const
{
    return ! size();
}

bool ArgumentList::notEmpty() const
{
    return !! size();
}

void ArgumentList::Item::set(const QString &s)
{
    mString = s;
}

QString ArgumentList::Item::toString() const
{
    return mString;
}

QString ArgumentList::Item::operator ()() const
{
    return toString();
}
