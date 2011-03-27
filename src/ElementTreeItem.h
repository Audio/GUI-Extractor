#ifndef ELEMENTTREEITEM_H
#define ELEMENTTREEITEM_H

#include "ElementHolder.h"
#include <QtGui/QTreeWidgetItem>


class ElementTreeItem : public ElementHolder, public QTreeWidgetItem
{
public:
  ElementTreeItem(QTreeWidget* parent, Element* element);
  ElementTreeItem(ElementTreeItem* parent, Element* element);

protected:
  void setDescription();
};

#endif // ELEMENTTREEITEM_H
