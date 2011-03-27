#ifndef TOPWINDOWSITEM_H
#define TOPWINDOWSITEM_H

#include "ElementHolder.h"
#include <QtGui/QTreeWidgetItem>


class TopWindowsItem : public ElementHolder, public QTreeWidgetItem
{
public:
  TopWindowsItem(QTreeWidget* parent, Element* topWindow);
};

#endif // TOPWINDOWSITEM_H
