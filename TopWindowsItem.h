#ifndef TOPWINDOWSITEM_H
#define TOPWINDOWSITEM_H

#include "UIA/Element.h"
#include <QListWidgetItem>


class TopWindowsItem : public QListWidgetItem
{
public:
  TopWindowsItem(QListWidget* parent, Element* topWindow);
  ~TopWindowsItem();

  Element* getElement() const;

private:
  Element* element;
};

#endif // TOPWINDOWSITEM_H
