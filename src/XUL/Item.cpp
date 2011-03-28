#include "Item.h"


using namespace XUL;

Item::Item(const QString& name)
{
  this->name = name;
}

void Item::setAttribute(const QString& key, const QString& value)
{
  attributes.insert(key, value);
}
