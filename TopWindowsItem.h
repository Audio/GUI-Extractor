#ifndef TOPWINDOWSITEM_H
#define TOPWINDOWSITEM_H

#include <QListWidgetItem>
#include "UIA/Element.h"


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
