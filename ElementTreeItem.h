#ifndef ELEMENTTREEITEM_H
#define ELEMENTTREEITEM_H

#include "UIA/Element.h"
#include <QTreeWidgetItem>


class ElementTreeItem : public QTreeWidgetItem
{
public:
  ElementTreeItem(QTreeWidget* parent, Element* element);
  ElementTreeItem(ElementTreeItem* parent, Element* element);
  ~ElementTreeItem();

  Element* getElement() const;

private:
  void initialize(Element* element);

  Element* element;
};

#endif // ELEMENTTREEITEM_H
